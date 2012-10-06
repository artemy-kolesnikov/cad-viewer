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
    viewer->viewFront();
    viewer->viewAll();
}

void View::viewBack() {
    viewer->viewBack();
    viewer->viewAll();
}

void View::viewTop() {
    viewer->viewTop();
    viewer->viewAll();
}

void View::viewBottom() {
    viewer->viewBottom();
    viewer->viewAll();
}

void View::viewLeft() {
    viewer->viewLeft();
    viewer->viewAll();
}

void View::viewRight() {
    viewer->viewRight();
    viewer->viewAll();
}

void View::viewAll() {
    viewer->viewAll();
}

void View::viewAxometric() {
    viewer->viewAxometric();
    viewer->viewAll();
}

void View::viewDatumPlane() {
}

}

