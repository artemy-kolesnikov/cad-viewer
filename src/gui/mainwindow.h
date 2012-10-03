/*
 * mainwindow.h: Main window class
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

#ifndef MAIN_WINDOW_HEADER
#define MAIN_WINDOW_HEADER

#include <QMainWindow>
#include <QMap>
#include <QStringList>

#include "gui/model.h"

class QDockWidget;
class QMdiArea;
class QMdiSubWindow;
class QMenuBar;
class QToolBar;
class QTreeView;

namespace Gui {

class ChildWindow;
class View;
class ActionList;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);

    void openFiles(QStringList& files);

private Q_SLOTS:
    void about();
    void openModel();
    ChildWindow* newChildWindow();
    void childWindowActivated(QMdiSubWindow* window);
    void childWindowClosed();
    void viewSelectionChanged();

    void viewFront();
    void viewBack();
    void viewTop();
    void viewBottom();
    void viewLeft();
    void viewRight();
    void viewAll();
    void viewAxometric();

    void selectNeutral();
    void selectVertex();
    void selectEdge();
    void selectFace();
    void selectSolid();

private:
    void createUI();
    void createDockWidget();
    void createMenu();
    void createCommonActions();
    void createViewActions();

    void disableViewActions();
    void enableViewActions();

    ChildWindow& currentChildWindow() const;
    Model& currentModel() const;
    View& currentView() const;

    QMdiArea* mdiArea;

    // Model shapes list
    QDockWidget* shapesDock;
    // Model properties
    QDockWidget* propertiesDock;
    QMenuBar* mainMenuBar;
    QToolBar* mainToolBar;
    QTreeView* shapesTreeView;

    QMenu* fileMenu;
    QMenu* viewMenu;
    QMenu* helpMenu;

    QMap<QWidget*, Model::SharedPtr> windowModelMap;

    ChildWindow* currentChild;

    QDockWidget* commandDock;
    QWidget* commandWidget;

    ActionList* acListViewType;
};

}

#endif // MAIN_WINDOW_HEADER

