/*
 * opencascadeviewer.h: OpenCASCADE rendering
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

#ifndef Gui_Viewer_OCC_OpenCASCADEViewer_H
#define Gui_Viewer_OCC_OpenCASCADEViewer_H

#include "occconfig.h"

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

#include <boost/shared_ptr.hpp>

#include "gui/model.h"
#include "gui/viewer/viewer.h"

namespace Gui {
namespace Viewer {
namespace OCC {

class ViewerWidget;

class OpenCASCADEViewer : public Viewer {
    friend class ViewerWidget;
public:
    typedef boost::shared_ptr<OpenCASCADEViewer> SharedPtr;

    OpenCASCADEViewer(Gui::Model::SharedPtr model);

    virtual const QWidget* getWidget() const;
    virtual QWidget* getWidget();
    virtual void viewAll();

private:
    virtual void shapeAdded(Modeling::Shape::SharedPtr shape);
    virtual void shapeRemoved(Modeling::Shape::SharedPtr shape);

private:
    boost::shared_ptr<ViewerWidget> viewerWidget;
    Handle(V3d_Viewer) viewer;
	Handle(AIS_InteractiveContext) context;
};

}
}
}

#endif // Gui_Viewer_OCC_OpenCASCADEViewer_H
