/*
 * inventorviewer.h: Open Inventor rendering
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

#ifndef Gui_Viewer_Inventor_InventorViewer_H
#define Gui_Viewer_Inventor_InventorViewer_H

#include <boost/shared_ptr.hpp>

#include "gui/model.h"
#include "gui/viewer/viewer.h"

namespace Gui {
namespace Viewer {
namespace Inventor {

class InventorViewerImpl;

class InventorViewer : public Viewer {
public:
    typedef boost::shared_ptr<InventorViewer> SharedPtr;

    InventorViewer(Gui::Model::SharedPtr model);

    virtual const QWidget* getWidget() const;
    virtual QWidget* getWidget();
    virtual void viewAll();

private:
    virtual void shapeAdded(Modeling::Shape::SharedPtr shape);
    virtual void shapeRemoved(Modeling::Shape::SharedPtr shape);

private:
    boost::shared_ptr<InventorViewerImpl> impl;
};

}
}
}

#endif // Gui_Viewer_Inventor_InventorViewer_H
