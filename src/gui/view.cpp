/*
 * view.cpp: View class
 *
 * This file is a part of the CAD Viewer project
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

#include "view.h"

#include <QDebug>
#include <QHBoxLayout>

#include <algorithm>
#include <boost/make_shared.hpp>

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoTransform.h>

#include "gui/cadviewerapplication.h"
#include "gui/inventorviewer.h"

namespace Gui {

View::View(Model::SharedPtr model, QWidget* parent) :
        QWidget(parent), model(model) {
    createUI();

    connect(model.get(), SIGNAL(shapeAdded(::Model::Shape::SharedPtr)),
        this, SLOT(shapeAdded(::Model::Shape::SharedPtr)));
    connect(model.get(), SIGNAL(shapeRemoved(::Model::Shape::SharedPtr)),
        this, SLOT(shapeRemoved(::Model::Shape::SharedPtr)));
}

void View::createUI() {
    inventorViewer = boost::make_shared<InventorViewer>(this);

    connect(inventorViewer->getEventObject(), SIGNAL(pathSelected(SoPath*)),
        this, SLOT(pathSelected(SoPath*)));
    connect(inventorViewer->getEventObject(), SIGNAL(pathDeselected(SoPath*)),
        this, SLOT(pathDeselected(SoPath*)));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));;
    layout->addWidget(inventorViewer->getWidget());

    //setMouseTracking(true);
}

void View::viewFront() {
    float root = sqrtf(2.0) / 2.0;
    inventorViewer->setCameraOrientation(SbRotation(-root, 0, 0, -root));
    inventorViewer->viewAll();
}

void View::viewBack() {
    float root = sqrtf(2.0) / 2.0;
    inventorViewer->setCameraOrientation(SbRotation(0, root, root, 0));
    inventorViewer->viewAll();
}

void View::viewTop() {
    inventorViewer->setCameraOrientation(SbRotation(0, 0, 0, 1));
    inventorViewer->viewAll();
}

void View::viewBottom() {
    inventorViewer->setCameraOrientation(SbRotation(-1, 0, 0, 0));
    inventorViewer->viewAll();
}

void View::viewLeft() {
    inventorViewer->setCameraOrientation(SbRotation(-0.5, 0, 0, -0.5));
    inventorViewer->viewAll();
}

void View::viewRight() {
    inventorViewer->setCameraOrientation(SbRotation(0.5, 0, 0, 0.5));
    inventorViewer->viewAll();
}

void View::viewAll() {
    inventorViewer->viewAll();
}

void View::viewAxometric() {
    inventorViewer->setCameraOrientation(SbRotation
        (-0.353553f, -0.146447f, -0.353553f, -0.853553f));
    inventorViewer->viewAll();
}

void View::viewDatumPlane() {
}

void View::shapeAdded(::Model::Shape::SharedPtr shape) {
}

void View::shapeRemoved(::Model::Shape::SharedPtr shape) {
    Q_EMIT selectionChanged();
}

void View::pathSelected(SoPath* path) {
    int pathLength = path->getLength();
    assert(pathLength > 2);

    if (path->getNodeFromTail(0)->getTypeId() == SoTransform::getClassTypeId())
        return;

    SoNode* node = path->getNodeFromTail(pathLength - 2);

    if (SoGroup::getClassTypeId() == node->getTypeId()) {
        Q_EMIT selectionChanged();
    }
}

void View::pathDeselected(SoPath* path) {
    Q_EMIT selectionChanged();
}

}

