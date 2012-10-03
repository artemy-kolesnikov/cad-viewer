/*
 * view.h: View class. Displays loaded model
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

#ifndef Gui_View_H
#define Gui_View_H

#include <QPaintEvent>
#include <QPoint>
#include <QWidget>

#include <boost/shared_ptr.hpp>

#include "gui/inventorviewer.h"
#include "gui/model.h"
#include "model/shape.h"

class SoPath;

namespace Gui {

class Model;

class View : public QWidget {
    Q_OBJECT
public:
    View(Model::SharedPtr model, QWidget* parent = 0);

Q_SIGNALS:
    void selectionChanged();

public Q_SLOTS:
    void viewFront();
    void viewBack();
    void viewTop();
    void viewBottom();
    void viewLeft();
    void viewRight();
    void viewAll();
    void viewAxometric();
    void viewDatumPlane();

private Q_SLOTS:
    void shapeAdded(::Model::Shape::SharedPtr shape);
    void shapeRemoved(::Model::Shape::SharedPtr shape);
    void pathSelected(SoPath* path);
    void pathDeselected(SoPath* path);

private:
    void createUI();

    Model::SharedPtr model;
    InventorViewer::SharedPtr inventorViewer;
};

}

#endif // Gui_View_H

