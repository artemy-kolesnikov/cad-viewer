/*
 * exception.h: Base class for exception
 *
 * This file is a part of the CAD Viewer project
 *
 * Copyright (C) 2012 Artemy Kolesnikov <artemy.kolesnikov@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef Util_Exception_H
#define Util_Exception_H

#include <exception>
#include <string>

namespace Util {

class Exception : public std::exception {
public:
    Exception(const std::string& what) : whatStr(what) {}
    ~Exception() throw() {}

    const char* what() { return whatStr.c_str(); }

private:
    std::string whatStr;
};

}

#endif // Util_Exception_H
