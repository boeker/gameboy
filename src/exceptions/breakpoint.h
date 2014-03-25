#ifndef EXCEPTIONS_BREAKPOINT_H
#define EXCEPTIONS_BREAKPOINT_H

#include <exception>

namespace exceptions {
class Breakpoint : public std::exception {
};
}

#endif