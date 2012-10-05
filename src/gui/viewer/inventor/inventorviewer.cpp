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

#include "util/sbscopedptr.h"

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

private:
    static void eventCallback(void* data, SoEventCallback* callback);
    static void selectionCallback(void* data, SoPath* path);
    static void deselectionCallback(void* data, SoPath* path);

private:
    Util::SbScopedPtr<SoSelection> root;
};

InventorViewerImpl::InventorViewerImpl() :
        inherited(0, "", FALSE,
        SoQtFullViewer::BUILD_NONE, SoQtViewer::EDITOR) {
    setBackgroundColor(SbColor(0.39, 0.58, 0.93));
    setCamera(new SoOrthographicCamera());

    root = Util::SbScopedPtr<SoSelection>(new SoSelection());
    root->addSelectionCallback(&InventorViewerImpl::selectionCallback, this);
    root->addDeselectionCallback(&InventorViewerImpl::deselectionCallback, this);
    setSceneGraph(root.get());
}

void InventorViewerImpl::eventCallback(void* data, SoEventCallback* callback) {
}

void InventorViewerImpl::selectionCallback(void* data, SoPath* path) {
}

void InventorViewerImpl::deselectionCallback(void* data, SoPath* path) {
}

InventorViewer::InventorViewer(Gui::Model::SharedPtr model) :
    Viewer(model), impl(boost::make_shared<InventorViewerImpl>()) {
}

const QWidget* InventorViewer::getWidget() const {
    return impl->getWidget();
}

QWidget* InventorViewer::getWidget() {
    return impl->getWidget();
}

void InventorViewer::viewAll() {
    impl->viewAll();
}

void InventorViewer::shapeAdded(Modeling::Shape::SharedPtr shape) {
}

void InventorViewer::shapeRemoved(Modeling::Shape::SharedPtr shape) {
}

}
}
}
