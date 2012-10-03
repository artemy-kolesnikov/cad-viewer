/*
 * inventorviewer.h: Inventor viewer class
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

#ifndef Gui_InventorViewer_H
#define Gui_InventorViewer_H

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

#include <QWidget>

#include <boost/shared_ptr.hpp>

class SoNode;
class SoSelection;
class SoEventCallback;

namespace Gui {

class InventorViewer;

class ViewerEvents : public QObject {
    friend class InventorViewer;

    Q_OBJECT

private:
    ViewerEvents() {}

Q_SIGNALS:
    void pathSelected(SoPath* path);
    void pathDeselected(SoPath* path);
};

class InventorViewer : public SoQtExaminerViewer {
    typedef SoQtExaminerViewer inherited;
public:
    typedef boost::shared_ptr<InventorViewer> SharedPtr;

    InventorViewer(QWidget* parent = 0);
    ~InventorViewer();

    SoSelection* getRootNode() const;

    void setCameraOrientation(const SbRotation& rotation);

    const ViewerEvents* getEventObject() const;

private:
    virtual void setSceneGraph(SoNode* root);
    virtual SoNode* getSceneGraph();

    static void eventCallback(void* data, SoEventCallback* callback);
    static void selectionCallback(void* data, SoPath* path);
    static void deselectionCallback(void* data, SoPath* path);

    void eventHandler(SoEventCallback* callback);
    void selectionHandler(SoPath* path);
    void deselectionHandler(SoPath* path);

private:
    SoSelection* rootSelection;
    SoEventCallback* eventCallbacker;
    ViewerEvents viewerEvents;
};

}

#endif // Gui_InventorViewer_H
