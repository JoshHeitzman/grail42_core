#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

import sys
import re
import subprocess
import os
import time
import tempfile

# NOTE this a prototype not indented for general consumption.

if 'grail42_msbuild_exe' in os.environ:
    # e.g. r'C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe'
    msbuildPath = os.environ['grail42_msbuild_exe']
else:
    # Assume msbuild is on the path
    msbuildPath = 'MSBuild.exe'

if 'NUMBER_OF_PROCESSORS' in os.environ:
    numProcs = int(os.environ['NUMBER_OF_PROCESSORS'])
else:
    numProcs = 4
    
target = sys.argv[-1]

# pri1 is very much a hacked up prototype to see how useful it is the to the author.  A real
# implementation would include annotations for priorities that would be used to select a subset
# of the build matrix.  An even better implementation would include a GUI that allows the priorities
# to be easily and does background build, deployments, and tests as local files change such as
# was specified by the requirements on this question posed on stackoverflow.com by the author:
# http://stackoverflow.com/questions/14009010/local-continuous-integration-system-for-c
pri1 = False
if len(sys.argv) == 3:
    if sys.argv[1] == 'pri1':
        pri1 = True
        
assert target[-4:].lower() == ".sln"

# NOTE the parsing done here isn't very robust, and it is likely to need hardening in the future.
class LineProcessor(object):
    projectLineStart = re.compile(r'^\s*Project\s*\(\s*"{')
    def __init__(self):
        self.process_line = self.parse_project
        self.plat_configs = list()
        self.project_path_guids = list()
        self.project_path_plat_configs = list()
    def parse_project(self, line):
        if self.projectLineStart.match(line) is not None:
            projectName, projectPath, projectGUID = line.split('=')[1].split(',')
            self.project_path_guids.append(
                (re.compile("^\s*"+projectGUID.strip().strip('"')+"\..+?\|.+?\.Build"), projectPath.strip().strip('"')))
        elif "Global" == line.strip():
            self.process_line = self.find_sln_plat_config            
    def find_sln_plat_config(self, line):
        if "SolutionConfigurationPlatforms" in line:
            self.process_line = self.parse_sln_plat_config
    def parse_sln_plat_config(self, line):
        if "EndGlobalSection" in line:
            self.process_line = self.find_proj_plat_config
            return
        configuration, platform = line.split('=')[0].strip().split('|')
        self.plat_configs.append((configuration, platform))
    def find_proj_plat_config(self, line): 
        if "ProjectConfigurationPlatforms" in line:
            self.process_line = self.parse_proj_plat_config
    def parse_proj_plat_config(self, line):
        if "EndGlobalSection" in line:
            self.process_line = lambda l: None
            return
        for projGUIDRe, projectPath in self.project_path_guids:
            if projGUIDRe.match(line):
                configuration, platform = line.split('=')[1].strip().split('|')
                self.project_path_plat_configs.append((projectPath, configuration, platform))

solution = open(target)
lineProcessor = LineProcessor()

for line in solution:
    lineProcessor.process_line(line)

solution.close()

#print lineProcessor.project_path_guids
#print lineProcessor.project_path_plat_configs

if pri1:
    new_project_path_plat_configs = []
    currentProjectPath = None
    alternate = True
    for projectPath, configuration, platform in lineProcessor.project_path_plat_configs:
        if currentProjectPath != projectPath:
            currentProjectPath = projectPath
            plat_configs = []
            if alternate:
                alternate = False
                plat_configs.append(('NaCl64', 'Debug'))
                plat_configs.append(('Win32', 'Release'))
            else:
                alternate = True
                plat_configs.append(('NaCl64', 'Release'))
                plat_configs.append(('Win32', 'Debug'))
        for plat, config in plat_configs:
            if plat == platform and config == configuration:
                new_project_path_plat_configs.append((projectPath, configuration, platform))
    lineProcessor.project_path_plat_configs = new_project_path_plat_configs

#print lineProcessor.project_path_plat_configs

class Reporter(object):
    def __init__(self, numProcs):
        self.numProcs = numProcs
        self.completedProcs = 0
        self.failedProcs = 0
    def proc_complete(self, proc):
        self.completedProcs += 1
        progress = ""
        if self.numProcs > 1:
            strCompletedProcs = str(self.completedProcs)
            strNumProcs = str(self.numProcs)
            padding = len(str(strNumProcs))-len(str(strCompletedProcs))
            progress = strCompletedProcs+' '*padding+" of "+strNumProcs
        if proc.returncode == 0:
            print progress, "Succeeded: ", proc.params
        else:
            self.failedProcs += 1
            print progress, "Failed: ", proc.params
            proc.stdOut.seek(0)
            print proc.stdOut.read()
            proc.stdErr.seek(0)
            print proc.stdErr.read()

reporter = Reporter(len(lineProcessor.project_path_plat_configs))

startTime = time.time()

class MSBuildSubprocess(subprocess.Popen):
    def __init__(self, projectPath, platform, configuration):
        self.params = (projectPath, platform, configuration)
        self.command = msbuildPath+' '+projectPath+' /property:Platform="'+platform+'" /property:Configuration="'+configuration+'"'
        self.stdOut = tempfile.TemporaryFile()
        self.stdErr = tempfile.TemporaryFile()
        subprocess.Popen.__init__(self, self.command, stdout=self.stdOut, stderr=self.stdErr)

completedProcs = []
procs = [None,]*numProcs
toProcess = lineProcessor.project_path_plat_configs[:]
while toProcess:
    for triple in toProcess[:]:
        projectPath, configuration, platform = triple
        unused = -1
        while unused < 0:
            for i, proc in enumerate(procs[:]):
                if proc is not None:
                    if proc.poll() is not None:
                        completedProcs.append(procs[i])
                        reporter.proc_complete(proc)
                        procs[i] = None
                    else:
                        continue
                unused = i
            time.sleep(0.1)
        skip = False
        # TODO rather than being hardcoded this should be determined via attribute
        if platform.lower() == 'android':            
            for proc in procs:
                # Don't run different android platform configs of the same project at the same
                # time as the ant builds are share some state and deployment occassionally fails
                # as well
                if proc is not None and proc.params[1] == platform and proc.params[0] == projectPath:
                    skip = True
                    break
        if not skip:
            procs[unused] = MSBuildSubprocess(projectPath, platform, configuration)
            toProcess.remove(triple)

while None in procs:
    procs.remove(None)

while procs:
    for proc in procs[:]:
        if proc.poll() is not None:
            completedProcs.append(proc)
            reporter.proc_complete(proc)
            procs.remove(proc)
    time.sleep(0.1)

endTime = time.time()

#for proc in completedProcs:
    #proc_complete(proc)

result = "All succeeded."
if reporter.failedProcs > 0:
    result = str(reporter.failedProcs)+" failed."
print
print result+"  Build completed in "+str(endTime-startTime)+" seconds."
