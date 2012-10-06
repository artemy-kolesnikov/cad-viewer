/*
 * inventorshape.h: Open Inventor shape presentation
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

#ifndef Gui_Viewer_Inventor_InventorShape_H
#define Gui_Viewer_Inventor_InventorShape_H

#include <boost/shared_ptr.hpp>

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSeparator.h>

#include "modeling/shape.h"
#include "util/soscopedptr.h"

class SoGroup;

namespace Gui {
namespace Viewer {
namespace Inventor {

class InventorShape {
public:
    typedef boost::shared_ptr<InventorShape> SharedPtr;

    InventorShape(Modeling::Shape::SharedPtr aShape);
    SoGroup* getGroup() const;

private:
    void computeShape();
    /*void computeEdges(SoGroup* edgeRoot, const TopoDS_Shape &shape);
    void computeVertices(SoGroup* vertexRoot, const TopoDS_Shape &shape);
    void computeFaces(SoGroup* faceRoot, const TopoDS_Shape &shape, double deflection);*/

private:
    Modeling::Shape::SharedPtr shape;
    Util::SoScopedPtr<SoGroup> group;
    Util::SoScopedPtr<SoSeparator> separator;
};

}
}
}

#endif // Gui_Viewer_Inventor_InventorShape_H
