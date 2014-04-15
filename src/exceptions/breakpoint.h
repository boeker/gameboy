// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef EXCEPTIONS_BREAKPOINT_H
#define EXCEPTIONS_BREAKPOINT_H

#include <exception>

namespace exceptions {
class Breakpoint : public std::exception {
};
}

#endif