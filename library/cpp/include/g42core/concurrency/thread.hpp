/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_9C17FE3D4D104BF6A331E62CD2C6AECB
#define G42CORE_HG_9C17FE3D4D104BF6A331E62CD2C6AECB

G42CORE_MC_PRAGMA_ONCE

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)
#ifdef _GLIBCXX_HAS_GTHREADS
#include <thread>
#else
// Neither Android or NaCl actually support the std::thread class although the header is provided.
#define G42CORE_CONCURRENCY_THREAD_REQUIRED
#endif
#else
#ifndef BOOST_THREAD_THREAD_HPP
#define BOOST_THREAD_THROW_IF_PRECONDITION_NOT_SATISFIED
#include <boost\thread\thread.hpp>
#endif
#endif

#ifndef G42CORE_HG_574A1DB99FFF499C9564FFD8855DBD94
#include "namespace.hpp"
#endif

#ifdef G42CORE_CONCURRENCY_THREAD_REQUIRED
#include <pthread.h>
#include <exception>

G42CORE_CONCURRENCY_BEGIN_NAMESPACES

// This is only a partial implementation of std::thread that provides only what is needed for the 
// threading requirements of test library.  This implementation is not thread safe.
class thread
{
G42CORE_MC_NOT_COPYABLE(thread)
public:
    explicit thread(void *(*f)(void *), void* arg1):
        joined(false)
    {
        pthread_attr_t attr; // TODO resource management class for pthread_attr_t
        if(0 != pthread_attr_init(&attr))
        {
            throw std::exception();
        }
        if(0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE))
        {
            pthread_attr_destroy(&attr);
            throw std::exception();
        }
        if(0 != pthread_create(&id, &attr, f, arg1))
        {
            pthread_attr_destroy(&attr);
            throw std::exception();
        }
        pthread_attr_destroy(&attr);
    }
    ~thread()
    {
        if(!joined)
        {
            pthread_detach(id);
        }
    }
    bool joinable() { return !joined; }
    void join()
    {
        if(joined)
        {
            // Per http://en.cppreference.com/w/cpp/thread/thread/join :
            // Exceptions:  std::system_error if joinable() == false or an error occurs. 
            throw std::exception();
        }
        joined = true;
        if(0 != pthread_join(id, NULL))
        {
            throw std::exception();
        }
    }
private:
    pthread_t id;
    bool joined;
};
G42CORE_CONCURRENCY_END_NAMESPACES
#elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)
G42CORE_CONCURRENCY_BEGIN_NAMESPACES
using std::thread;
G42CORE_CONCURRENCY_END_NAMESPACES
#else
G42CORE_CONCURRENCY_BEGIN_NAMESPACES
using boost::thread;
G42CORE_CONCURRENCY_END_NAMESPACES
#endif

#endif // G42CORE_HG_9C17FE3D4D104BF6A331E62CD2C6AECB
