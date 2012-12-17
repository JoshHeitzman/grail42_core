/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_A533B033358A43CB9FC53C9C607EC0AE
#define G42CORE_HG_A533B033358A43CB9FC53C9C607EC0AE

G42CORE_MC_PRAGMA_ONCE

G42CORE_TEST_BEGIN_NAMESPACES

namespace detail
{

// TODO BEGIN find outstream_append_* struct and typdefs a new home
// probably in an outstream namespace, so outstream need not be in the typenames.

struct outstream_append_nothing
{
    template <typename OutStream>
    inline static void append_to_stream(OutStream&)
    {
    }
};

template <typename T, T Value>
struct outstream_append_value
{
    template <typename OutStream>
    inline static void append_to_stream(OutStream& outStream)
    {
        outStream << Value;
    }
};

// Prefered over std::endl as it doesn't have any side effects (e.g. flushing the stream).
typedef outstream_append_value<char, '\n'> outstream_append_slashn;

// END TODO (see above)

template <typename LineEnding = outstream_append_slashn>
struct reporter_outstream_formatter_line_common_char
{
    struct prefix
    {
        template <typename OutStream>
        inline static void append_to_stream(OutStream& outStream)
        {
            outStream << "*** Tests ";
        }
    };
    struct postfix
    {
        template <typename OutStream>
        inline static void append_to_stream(OutStream& outStream)
        {
            outStream << " ***";
            LineEnding::append_to_stream(outStream);
        }
    };
};

template <typename Note = outstream_append_nothing, typename Base = reporter_outstream_formatter_line_common_char<> >
struct reporter_outstream_formatter_header_char : Base
{
    template <typename OutStream>
    inline static void append_to_stream(OutStream& outStream)
    {
        Base::prefix::append_to_stream(outStream);
        outStream << "started ";
        Note::append_to_stream(outStream);
        Base::postfix::append_to_stream(outStream);
    }
};

template <typename Base = reporter_outstream_formatter_line_common_char<> >
struct reporter_outstream_formatter_footer_char : Base
{
    template <typename OutStream>
    inline static void append_to_stream(OutStream& outStream, unsigned int passed, unsigned int failed, unsigned int skipped)
    {
        Base::prefix::append_to_stream(outStream);
        outStream << "complete: " << passed << " passed, " << failed << " failed, " << skipped << " skipped";
        Base::postfix::append_to_stream(outStream);
    }
};

template <
    typename Header = reporter_outstream_formatter_header_char<>, 
    typename Footer = reporter_outstream_formatter_footer_char<>,
    typename LineEnding = outstream_append_slashn>
struct reporter_outstream_formatter_char
{
    typedef Header header;
    typedef Footer footer;
    typedef LineEnding line_ending;
};

template <typename OutStream, typename Formatter = reporter_outstream_formatter_char<> >
struct reporter_outstream_policies
{
    typedef OutStream outstream;
    typedef typename Formatter::header header;
    typedef typename Formatter::footer footer;
    typedef typename Formatter::line_ending line_ending;
};

// Policy base design is used here in order to make it easy to use different type of streams (i.e.
// stdout, a file, a pipe, etc.), switch from ASCII to a different character set (i.e. UTF-8,
// UTF-16, etc.), change the line endings used, and modify or remove the header and/or footer.
template <typename Policies>
class reporter_outstream
{
G42CORE_MC_NOT_COPYABLE(reporter_outstream)
public:
    typedef typename Policies::outstream outstream;
    typedef typename Policies::header header;
    typedef typename Policies::footer footer;
    typedef typename Policies::line_ending line_ending;

    reporter_outstream(outstream& outStream):
        outstream_(outStream)
    {
    }

    reporter_outstream(reporter_outstream<Policies>&& rhs):
        outstream_(rhs.outstream_)
    {
    }

    void on_tests_starting()
    {
        header::append_to_stream(outstream_);
    }

    template <class T>
    void on_complete_message(const T& t)
    {
        outstream_ << t;
        line_ending::append_to_stream(outstream_);
    }

    template <class T>
    void message_part(const T& t)
    {
        outstream_ << t;
    }

    void on_tests_complete(unsigned int passed, unsigned int failed, unsigned int skipped = 0)
    {
        footer::append_to_stream(outstream_, passed, failed, skipped);
    }

private:
    outstream& outstream_;
};

} // namespace detail

G42CORE_TEST_END_NAMESPACES

#endif // G42CORE_HG_A533B033358A43CB9FC53C9C607EC0AE
