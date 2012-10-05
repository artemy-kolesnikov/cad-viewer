/*
 * opencascadeviewer.cpp: OpenCASCADE rendering
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

#include "gui/viewer/opencascadeviewer.h"

#include <QPaintEvent>

#include <AIS_SequenceOfInteractive.hxx>
#include <Graphic3d_GraphicDevice.hxx>
#include <TCollection_ExtendedString.hxx>
#include <V3d_View.hxx>
#include <Xw_Window.hxx>

#include <QX11Info>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmu/StdCmap.h>
#include <X11/Xlib.h>
#include <Xw_Window.hxx>

#include <boost/make_shared.hpp>

namespace {

Handle(Graphic3d_GraphicDevice) defaultDevice;

int paintCallBack(Aspect_Drawable drawable, void* userData,
	    Aspect_GraphicCallbackStruct* data) {
    //Gui::Viewer::OpenCASCADEViewer* viewer = static_cast<Gui::Viewer::OpenCASCADEViewer*>(userData);
    //viewer->paintGl();

    return 0;
}

}

namespace Gui {
namespace Viewer {

class ViewerWidget : public QWidget {
public:
    typedef boost::shared_ptr<ViewerWidget> SharedPtr;

    ViewerWidget(const OpenCASCADEViewer& aViewer) :
            cascadeViewer(aViewer), firstPaint(true) {
	    XSynchronize(x11Info().display(), true);
    }

protected:
	void paintEvent(QPaintEvent*);

private:
    void init();

private:
    boost::shared_ptr<AIS_SequenceOfInteractive> shapes;
	Handle(V3d_View) view;
    const OpenCASCADEViewer& cascadeViewer;
    bool firstPaint;
};

void ViewerWidget::init() {
    shapes = boost::make_shared<AIS_SequenceOfInteractive>();

    view = cascadeViewer.context->CurrentViewer()->CreateView();

    int windowHandle = (int)winId();
    short hi, lo;
    lo = (short) windowHandle;
    hi = (short) (windowHandle >> 16);
    Handle(Xw_Window) hWnd = new Xw_Window(Handle(Graphic3d_GraphicDevice)::DownCast(
        cascadeViewer.context->CurrentViewer()->Device()),(int) hi,(int) lo, Xw_WQ_SAMEQUALITY);
    view->SetWindow(hWnd, 0, paintCallBack, this);

    if (!hWnd->IsMapped()) {
        hWnd->Map();
    }

    view->SetBackgroundColor(Quantity_NOC_BLACK);
    view->MustBeResized();
}

void ViewerWidget::paintEvent(QPaintEvent*) {
    if (firstPaint) {
        init();
        firstPaint = false;
    }

    if(!view.IsNull()) {
        view->Redraw();
    }
}

OpenCASCADEViewer::OpenCASCADEViewer(Gui::Model::SharedPtr model) : Viewer(model) {
    if(defaultDevice.IsNull()) {
        defaultDevice = new Graphic3d_GraphicDevice(getenv("DISPLAY"));
    }

    TCollection_ExtendedString v3DName("Visu3D");

    //XXX
    viewer = new V3d_Viewer(defaultDevice, v3DName.ToExtString(), "", 1000.0, V3d_XposYnegZpos,
            Quantity_NOC_GRAY30, V3d_ZBUFFER, V3d_GOURAUD, V3d_WAIT,
            Standard_True, Standard_True, V3d_TEX_NONE);

    viewer->Init();
    viewer->SetDefaultLights();
    viewer->SetLightOn();

    // XXX
    context = new AIS_InteractiveContext(viewer);

    viewerWidget = boost::make_shared<ViewerWidget>(*this);
}

const QWidget* OpenCASCADEViewer::getWidget() const {
    return viewerWidget.get();
}

QWidget* OpenCASCADEViewer::getWidget() {
    return viewerWidget.get();
}

void OpenCASCADEViewer::viewAll() {
}

void OpenCASCADEViewer::shapeAdded(Modeling::Shape::SharedPtr shape) {
    /*for (int i = 1; i <= dsShapes->Length(); ++i) {
        Handle(AIS_Shape) shape = new AIS_Shape(dsShapes->Value(i));
        context->SetDisplayMode(shape, 1, false);

        shapes->Append(shape);

        context->Display(shape, false);
    }

    context->UpdateCurrentViewer();*/
}

void OpenCASCADEViewer::shapeRemoved(Modeling::Shape::SharedPtr shape) {
}

}
}
