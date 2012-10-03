/*
 * shape.h: Class for storing shape data
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

#ifndef Model_Shape_H
#define Model_Shape_H

#include <boost/shared_ptr.hpp>

namespace Model {

namespace Impl {

class ShapeImpl;

}

class Shape {
public:
    typedef boost::shared_ptr<Shape> SharedPtr;

private:
    boost::shared_ptr<Impl::ShapeImpl> pImpl;
};

}

#endif // Model_Shape_H
