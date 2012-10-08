/*
 * inventorviewer.cpp: Open Inventor rendering
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

#include "gui/viewer/inventor/inventorviewer.h"

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoEventCallback.h>

#include <boost/make_shared.hpp>
#include <list>

#include "util/soscopedptr.h"

#include "gui/viewer/inventor/inventorshape.h"
#include "gui/viewer/inventor/sobackgroundgradient.h"
#include "gui/viewer/inventor/soaxes.h"

using Modeling::Shape;

namespace Gui {
namespace Viewer {
namespace Inventor {

class InventorViewerImpl : public SoQtExaminerViewer {
    typedef SoQtExaminerViewer inherited;
public:
    InventorViewerImpl();

    const SoSelection* getRootSelection() const {
        return root.get();
    }

    SoSelection* getRootSelection() {
        return root.get();
    }

    void addShape(Shape::SharedPtr shape);

    void setCameraOrientation(const SbRotation& rotation);

private:
    static void eventCallback(void* data, SoEventCallback* callback);
    static void selectionCallback(void* data, SoPath* path);
    static void deselectionCallback(void* data, SoPath* path);

private:
    Util::SoScopedPtr<SoSelection> root;

    std::list<InventorShape::SharedPtr> shapes;
};

InventorViewerImpl::InventorViewerImpl() :
        inherited(0, "", FALSE,
        SoQtFullViewer::BUILD_NONE, SoQtViewer::EDITOR) {
    //setBackgroundColor(SbColor(0.39, 0.58, 0.93));
    setCamera(new SoOrthographicCamera());

    root = Util::SoScopedPtr<SoSelection>(new SoSelection());
    root->addSelectionCallback(&InventorViewerImpl::selectionCallback, this);
    root->addDeselectionCallback(&InventorViewerImpl::deselectionCallback, this);
    setSceneGraph(root.get());

    SoBackgroundGradient* gradient = new SoBackgroundGradient();
    gradient->setColorGradient(SbColor(0.0f, 0.1f, 0.3f), SbColor(0.7f, 0.7f, 0.8f));
    root->addChild(gradient);

    SoAxes* axes = new SoAxes();
    root->addChild(axes);
}

void InventorViewerImpl::eventCallback(void* data, SoEventCallback* callback) {
}

void InventorViewerImpl::selectionCallback(void* data, SoPath* path) {
}

void InventorViewerImpl::deselectionCallback(void* data, SoPath* path) {
}

void InventorViewerImpl::addShape(Shape::SharedPtr shape) {
    InventorShape::SharedPtr inventorShape = boost::make_shared<InventorShape>(shape);

    root->addChild(inventorShape->getGroup());

    shapes.push_back(inventorShape);

    viewAll();
}

void InventorViewerImpl::setCameraOrientation(const SbRotation& rotation) {
    getCamera()->orientation.setValue(rotation);
}

bool InventorViewer::inited = false;

void InventorViewer::init() {
    if (!inited) {
        inited = true;

        SoAxes::initClass();
        SoBackgroundGradient::initClass();
    }
}

InventorViewer::InventorViewer(Gui::Model::SharedPtr model) :
        Viewer(model) {
    init();
    impl = boost::make_shared<InventorViewerImpl>();
}

const QWidget* InventorViewer::getWidget() const {
    return impl->getWidget();
}

QWidget* InventorViewer::getWidget() {
    return impl->getWidget();
}

void InventorViewer::viewFront() {
    float root = sqrtf(2.0) / 2.0;
    impl->setCameraOrientation(SbRotation(-root, 0, 0, -root));
}

void InventorViewer::viewBack() {
    float root = sqrtf(2.0) / 2.0;
    impl->setCameraOrientation(SbRotation(0, root, root, 0));
}

void InventorViewer::viewTop() {
    impl->setCameraOrientation(SbRotation(0, 0, 0, 1));
}

void InventorViewer::viewBottom() {
    impl->setCameraOrientation(SbRotation(-1, 0, 0, 0));
}

void InventorViewer::viewLeft() {
    impl->setCameraOrientation(SbRotation(-0.5, 0, 0, -0.5));
}

void InventorViewer::viewRight() {
    impl->setCameraOrientation(SbRotation(0.5, 0, 0, 0.5));
}

void InventorViewer::viewAxometric() {
    impl->setCameraOrientation(SbRotation
        (-0.353553f, -0.146447f, -0.353553f, -0.853553f));
}

void InventorViewer::viewAll() {
    impl->viewAll();
}

void InventorViewer::shapeAdded(Shape::SharedPtr shape) {
    impl->addShape(shape);
}

}
}
}
