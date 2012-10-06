/*
 * mainwindow_ui.cpp: UI creation functionality
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

#include "gui/mainwindow.h"

#include "gui/actionlist.h"

#include <QActionGroup>
#include <QCoreApplication>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenuBar>
#include <QSize>
#include <QToolBar>
#include <QTreeView>
#include <QVBoxLayout>

namespace Gui {

void MainWindow::createUI() {
    resize(QSize(800, 600));

    setWindowTitle(tr("CAD Viewer"));

    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);
    //mdiArea->setViewMode(QMdiArea::TabbedView);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
        this, SLOT(childWindowActivated(QMdiSubWindow*)));

    commandDock = new QDockWidget(tr("Command"), this);
    commandDock->setVisible(false);
    commandDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    commandDock->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, commandDock);

    createDockWidget();
    createMenu();
    createCommonActions();
    createViewActions();
}

void MainWindow::createDockWidget() {
    shapesDock = new QDockWidget(tr("Objects"), this);
    shapesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, shapesDock);

    QWidget* shapesWidget = new QWidget(shapesDock);
    QVBoxLayout* shapesLayout = new QVBoxLayout(shapesWidget);
    shapesDock->setWidget(shapesWidget);

    shapesTreeView = new QTreeView(shapesDock);
    shapesLayout->addWidget(shapesTreeView);
}

void MainWindow::createMenu() {
    mainMenuBar = new QMenuBar(this);
    setMenuBar(mainMenuBar);

    fileMenu = new QMenu(mainMenuBar);
    fileMenu->setTitle(tr("File"));
    mainMenuBar->addMenu(fileMenu);

    /*QMenu* selectionMenu = new QMenu(mainMenuBar);
    selectionMenu->setTitle(tr("Выбор"));
    actionMenu->addMenu(selectionMenu);

    QActionGroup* selectionGroup = new QActionGroup(this);

    acSelectNeutral = new QAction(tr("Нейтральный"), this);
    acSelectNeutral->setCheckable(true);
    selectionMenu->addAction(acSelectNeutral);
    connect(acSelectNeutral, SIGNAL(triggered()), this, SLOT(selectNeutral()));
    selectionGroup->addAction(acSelectNeutral);

    acSelectVertex = new QAction(tr("Вершина"), this);
    acSelectVertex->setCheckable(true);
    selectionMenu->addAction(acSelectVertex);
    connect(acSelectVertex, SIGNAL(triggered()), this, SLOT(selectVertex()));
    selectionGroup->addAction(acSelectVertex);

    acSelectEdge = new QAction(tr("Грань"), this);
    acSelectEdge->setCheckable(true);
    selectionMenu->addAction(acSelectEdge);
    connect(acSelectEdge, SIGNAL(triggered()), this, SLOT(selectEdge()));
    selectionGroup->addAction(acSelectEdge);

    acSelectFace = new QAction(tr("Поверхность"), this);
    acSelectFace->setCheckable(true);
    selectionMenu->addAction(acSelectFace);
    connect(acSelectFace, SIGNAL(triggered()), this, SLOT(selectFace()));
    selectionGroup->addAction(acSelectFace);

    acSelectSolid = new QAction(tr("Объект"), this);
    acSelectSolid->setCheckable(true);
    selectionMenu->addAction(acSelectSolid);
    connect(acSelectSolid, SIGNAL(triggered()), this, SLOT(selectSolid()));
    selectionGroup->addAction(acSelectSolid);*/

    viewMenu = new QMenu(mainMenuBar);
    viewMenu->setTitle(tr("View"));
    mainMenuBar->addMenu(viewMenu);

    helpMenu = new QMenu(mainMenuBar);
    helpMenu->setTitle(tr("Help"));
    mainMenuBar->addMenu(helpMenu);

    mainToolBar = new QToolBar(this);
    addToolBar(mainToolBar);
}

void MainWindow::createCommonActions() {
    acListViewType = new ActionList(this);

    QAction* acExit = new QAction(tr("Exit"), this);
    connect(acExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    QAction* acOpenModel = new QAction(QIcon(":/icons/open_document.png"), tr("Open..."), this);
    connect(acOpenModel, SIGNAL(triggered(bool)), this, SLOT(openModel()));

    QAction* acNewModel = new QAction(QIcon(":/icons/new_document.png"), tr("New"), this);
    connect(acNewModel, SIGNAL(triggered(bool)), this, SLOT(newChildWindow()));

    fileMenu->addAction(acNewModel);
    fileMenu->addAction(acOpenModel);
    fileMenu->addSeparator();
    fileMenu->addAction(acExit);

    mainToolBar->addAction(acNewModel);
    mainToolBar->addAction(acOpenModel);
    mainToolBar->addSeparator();

    QAction* acAbout = new QAction(tr("About..."), this);
    connect(acAbout, SIGNAL(triggered(bool)), this, SLOT(about()));
    helpMenu->addAction(acAbout);
}

void MainWindow::createViewActions() {
    QActionGroup* viewGroup = new QActionGroup(this);

    QAction* acViewFront = new QAction(QIcon(":/icons/view-front.png"), tr("Front"), this);
    acViewFront->setCheckable(true);
    viewMenu->addAction(acViewFront);
    connect(acViewFront, SIGNAL(triggered()), this, SLOT(viewFront()));
    viewGroup->addAction(acViewFront);
    mainToolBar->addAction(acViewFront);
    acListViewType->addAction(acViewFront);

    QAction* acViewBack = new QAction(QIcon(":/icons/view-back.png"), tr("Back"), this);
    acViewBack->setCheckable(true);
    viewMenu->addAction(acViewBack);
    connect(acViewBack, SIGNAL(triggered()), this, SLOT(viewBack()));
    viewGroup->addAction(acViewBack);
    mainToolBar->addAction(acViewBack);
    acListViewType->addAction(acViewBack);

    QAction* acViewTop = new QAction(QIcon(":/icons/view-top.png"), tr("Top"), this);
    acViewTop->setCheckable(true);
    viewMenu->addAction(acViewTop);
    connect(acViewTop, SIGNAL(triggered()), this, SLOT(viewTop()));
    viewGroup->addAction(acViewTop);
    mainToolBar->addAction(acViewTop);
    acListViewType->addAction(acViewTop);

    QAction* acViewBottom = new QAction(QIcon(":/icons/view-bottom.png"), tr("Bottom"), this);
    acViewBottom->setCheckable(true);
    viewMenu->addAction(acViewBottom);
    connect(acViewBottom, SIGNAL(triggered()), this, SLOT(viewBottom()));
    viewGroup->addAction(acViewBottom);
    mainToolBar->addAction(acViewBottom);
    acListViewType->addAction(acViewBottom);

    QAction* acViewLeft = new QAction(QIcon(":/icons/view-left.png"), tr("Left"), this);
    acViewLeft->setCheckable(true);
    viewMenu->addAction(acViewLeft);
    connect(acViewLeft, SIGNAL(triggered()), this, SLOT(viewLeft()));
    viewGroup->addAction(acViewLeft);
    mainToolBar->addAction(acViewLeft);
    acListViewType->addAction(acViewLeft);

    QAction* acViewRight = new QAction(QIcon(":/icons/view-right.png"), tr("Right"), this);
    acViewRight->setCheckable(true);
    viewMenu->addAction(acViewRight);
    connect(acViewRight, SIGNAL(triggered()), this, SLOT(viewRight()));
    viewGroup->addAction(acViewRight);
    mainToolBar->addAction(acViewRight);
    acListViewType->addAction(acViewRight);

    QAction* acAxometric = new QAction(QIcon(":/icons/view-axometric.png"), tr("Axonometric"), this);
    acAxometric->setCheckable(true);
    viewMenu->addAction(acAxometric);
    connect(acAxometric, SIGNAL(triggered()), this, SLOT(viewAxometric()));
    viewGroup->addAction(acAxometric);
    mainToolBar->addAction(acAxometric);
    acListViewType->addAction(acAxometric);

    QAction* acViewAll = new QAction(QIcon(":/icons/view-all.png"), tr("View all"), this);
    viewMenu->addAction(acViewAll);
    connect(acViewAll, SIGNAL(triggered()), this, SLOT(viewAll()));
    acListViewType->addAction(acViewAll);

    mainToolBar->addSeparator();
}

}
