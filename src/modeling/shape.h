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

#ifndef Modeling_Shape_H
#define Modeling_Shape_H

#include <boost/shared_ptr.hpp>
#include <string>

#include <TopoDS_Shape.hxx>

namespace Modeling {

class Shape {
public:
    typedef boost::shared_ptr<Shape> SharedPtr;

    Shape(const TopoDS_Shape& aShape) : shape(aShape) {}

    TopoDS_Shape getShape() const {
        return shape;
    }

private:
    TopoDS_Shape shape;
};

}

#endif // Modeling_Shape_H
