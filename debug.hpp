#pragma once
#ifndef WTL_DEBUG_HPP_
#define WTL_DEBUG_HPP_

#include <cstdio>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <string>
#include <chrono>


#define CERR(...) std::cerr << "\033[1;30m" << __VA_ARGS__ << "\033[0m"

#ifndef NDEBUG
#  define DCERR(...) CERR(__VA_ARGS__)
#  define DPRINTF(...) std::fprintf(stderr, __VA_ARGS__)
#else
#  define DCERR(...)
#  define DPRINTF(...)
#endif // NDEBUG

#define FILE_LINE_PRETTY __FILE__<<':'<<__LINE__<<':'<<__PRETTY_FUNCTION__
#define FLPF CERR(FILE_LINE_PRETTY << std::endl)
#define HERE DCERR(FILE_LINE_PRETTY << std::endl)

#define DQUOTE(s) # s
#define CONCATENATE(x, y) x ## y


/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
namespace wtl {
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

inline const char* strerror(const std::string& msg="") {
    if (msg.empty()) {
        return std::strerror(errno);
    } else {
        static const std::string s(msg + ": " + std::strerror(errno));
        return s.c_str();
    }
}

// std::cerr << std::strerror(errno);
// overloaded to receive an additional message in std:string
inline void perror(const std::string& msg="") {
    std::perror(msg.empty() ? nullptr : std::string("\nERROR:\n"+msg).c_str());
}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// speed test

template <typename Time = std::chrono::milliseconds, typename Fn>
inline Time stopwatch (Fn&& fn) {
    typedef std::chrono::high_resolution_clock Clock;
    const auto start = Clock::now();
    fn();
    return std::chrono::duration_cast<Time>(Clock::now() - start);
}

template <class Fn>
void benchmark(Fn&& fn, const std::string& label="", size_t times=3) {
    for (; times>0; --times) {
        const auto t = stopwatch(fn);
        std::cerr << "#BENCHMARK "
                  << t.count() << " [ms] " << label << std::endl;
    }
}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
} // namespace wtl
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////


#endif // WTL_DEBUG_HPP_
