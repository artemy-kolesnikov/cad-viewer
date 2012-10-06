/*
 * viewer.h: Base class for model rendering
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

#ifndef Gui_Viewer_Viewer_H
#define Gui_Viewer_Viewer_H

#include <QObject>
#include <QWidget>

#include <boost/shared_ptr.hpp>

#include "gui/model.h"
#include "modeling/shape.h"

namespace Gui {
namespace Viewer {

class Viewer : public QObject {
    Q_OBJECT
public:
    typedef boost::shared_ptr<Viewer> SharedPtr;

    Viewer(Gui::Model::SharedPtr aMoldel) : model(aMoldel) {
        connect(model.get(), SIGNAL(shapeAdded(Modeling::Shape::SharedPtr)),
            this, SLOT(shapeAdded(Modeling::Shape::SharedPtr)));
    }

    virtual ~Viewer() {}

    virtual const QWidget* getWidget() const = 0;
    virtual QWidget* getWidget() = 0;

    virtual void viewFront() = 0;
    virtual void viewBack() = 0;
    virtual void viewTop() = 0;
    virtual void viewBottom() = 0;
    virtual void viewLeft() = 0;
    virtual void viewRight() = 0;
    virtual void viewAxometric() = 0;
    virtual void viewAll() = 0;

    static Viewer::SharedPtr create(Gui::Model::SharedPtr model);

private Q_SLOTS:
    virtual void shapeAdded(Modeling::Shape::SharedPtr shape) = 0;

private:
    Gui::Model::SharedPtr model;
};

}
}

#endif // Gui_Viewer_Viewer_H
