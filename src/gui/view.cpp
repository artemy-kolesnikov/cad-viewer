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

#include "gui/cadviewerapplication.h"
#include "gui/inventorviewer.h"

#include <QDebug>
#include <QHBoxLayout>

#include <algorithm>

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoTransform.h>

namespace Gui {

View::View(QWidget* parent) : QWidget(parent),
        isShapeManip(false), manipSeted(false) {
    createUI();
}

void View::createUI() {
    inventorViewer = new InventorViewer(this);

    connect(inventorViewer->getEventObject(), SIGNAL(pathSelected(SoPath*)),
        this, SLOT(pathSelected(SoPath*)));
    connect(inventorViewer->getEventObject(), SIGNAL(pathDeselected(SoPath*)),
        this, SLOT(pathDeselected(SoPath*)));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));;
    layout->addWidget(inventorViewer->getWidget());

    //setMouseTracking(true);
}

void View::setModel(Model::SharedPtr model) {
    this->model = model;

    connect(model.get(), SIGNAL(shapeAdded(const Shape&)),
        this, SLOT(shapeAdded(const Shape&)));
    connect(model.get(), SIGNAL(shapeRemoved(const Shape&)),
        this, SLOT(shapeRemoved(const Shape&)));
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

void View::shapeAdded(const Shape& shape) {
}

void View::shapeRemoved(const Shape& shape) {
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

