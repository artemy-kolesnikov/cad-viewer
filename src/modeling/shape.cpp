/*
 * shape.cpp: Class for storing shape data
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

#include "modeling/shape.h"

#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>

namespace Modeling {

Shape::Shape(const TopoDS_Shape& aShape) : topoShape(aShape) {
    computeNumbers();
}

void Shape::computeNumbers() {
    TopTools_IndexedMapOfShape mapOfShape;

    TopExp::MapShapes(topoShape, TopAbs_VERTEX, mapOfShape);
    vertsNum = mapOfShape.Extent() + 1;

    TopExp::MapShapes(topoShape, TopAbs_FACE, mapOfShape);
    facesNum = mapOfShape.Extent() + 1;

    TopExp::MapShapes(topoShape, TopAbs_EDGE, mapOfShape);
    edgesNum = mapOfShape.Extent() + 1;
}

}
