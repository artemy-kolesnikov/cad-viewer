/*
 * messagestring.h: Class for message string forming
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

#ifndef Util_MessageString_H
#define Util_MessageString_H

#include <sstream>

namespace Util {

class MessageString {
public:
    template <typename T>
    MessageString& operator << (const T& value) {
        if (!sstr.str().empty()) {
            sstr << " ";
        }

        sstr << value;
        return *this;
    }

    operator const char* () const {
        return sstr.str().c_str();
    }

private:
    std::stringstream sstr;
};

}

#endif // Util_MessageString_H
