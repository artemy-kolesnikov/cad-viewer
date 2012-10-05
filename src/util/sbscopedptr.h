/*
 * sbscopedptr.h: Scoped pointer for Open Inventor nodes
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

#ifndef Util_SbScopedPtr_H
#define Util_SbScopedPtr_H

namespace Util {

template <typename T>
class SbScopedPtr {
public:
    typedef T* Pointer;
    typedef T& Reference;
    typedef const T& ConstReference;

    SbScopedPtr() : ptr(0) {}

    template <typename Tp>
    SbScopedPtr(Tp p) {
        ptr = p;
        ptr->ref();
    }

    SbScopedPtr(ConstReference other) {
        ptr = other.ptr();
        ptr->ref();
    }

    SbScopedPtr& operator = (const SbScopedPtr& other) {
        if (ptr) {
            ptr->unref();
        }

        ptr = other.ptr;
        ptr->ref();

        return *this;
    }

    template <typename Tp>
    void reset(Tp p) {
        if (ptr) {
            ptr->unref();
        }

        ptr = p;
        ptr->ref();
    }

    ~SbScopedPtr() {
        ptr->unref();
    }

    Pointer release() {
        ptr->unrefNoDelete();
        return ptr;
    }

    Pointer operator->() const {
        return ptr;
    }

    Pointer get() const {
        return ptr;
    }

    Reference operator*() const {
        return *ptr;
    }

private:
    Pointer ptr;
};

}

#endif // Util_SbScopedPtr_H
