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

namespace Gui {

View::View(Model::SharedPtr model, QWidget* parent) :
        QWidget(parent), model(model) {
    createUI();
}

void View::createUI() {
    viewer = Viewer::Viewer::create(model);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));;
    layout->addWidget(viewer->getWidget());

    //setMouseTracking(true);
}

void View::viewFront() {
    //float root = sqrtf(2.0) / 2.0;
    //viewer->setCameraOrientation(SbRotation(-root, 0, 0, -root));
    viewer->viewAll();
}

void View::viewBack() {
    //float root = sqrtf(2.0) / 2.0;
    //viewer->setCameraOrientation(SbRotation(0, root, root, 0));
    viewer->viewAll();
}

void View::viewTop() {
    //viewer->setCameraOrientation(SbRotation(0, 0, 0, 1));
    viewer->viewAll();
}

void View::viewBottom() {
    //viewer->setCameraOrientation(SbRotation(-1, 0, 0, 0));
    viewer->viewAll();
}

void View::viewLeft() {
    //viewer->setCameraOrientation(SbRotation(-0.5, 0, 0, -0.5));
    viewer->viewAll();
}

void View::viewRight() {
    //viewer->setCameraOrientation(SbRotation(0.5, 0, 0, 0.5));
    viewer->viewAll();
}

void View::viewAll() {
    viewer->viewAll();
}

void View::viewAxometric() {
    //viewer->setCameraOrientation(SbRotation
        //(-0.353553f, -0.146447f, -0.353553f, -0.853553f));
    viewer->viewAll();
}

void View::viewDatumPlane() {
}

}

