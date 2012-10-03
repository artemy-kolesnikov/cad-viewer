/*
 * mainwindow.cpp: Main window class
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

#include <QDir>
#include <QFileDialog>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QTreeView>

#include <cassert>
#include <boost/make_shared.hpp>

#include "gui/childwindow.h"
#include "gui/model.h"
#include "gui/view.h"

namespace Gui {

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent) {
    createUI();

    disableViewActions();

    currentChild = 0;
}

void MainWindow::openFiles(QStringList& files) {
    QString fileName;
    foreach(fileName, files) {
        newChildWindow();
        Model& model = currentModel();
        model.load(fileName);
    }
}

ChildWindow& MainWindow::currentChildWindow() const {
    assert(currentChild);
    return *currentChild;
}

Model& MainWindow::currentModel() const {
    /*const ChildWindow& window = currentChildWindow();
    Model* model = window.getView().getModel();
    assert(model);
    return *model;*/
}

View& MainWindow::currentView() const {
    /*const ChildWindow& window = currentChildWindow();
    return window.getView();*/
}

void MainWindow::about() {
    //QString msg(tr("SimpleCAD %1.%2").arg(VERSION_MAJOR).arg(VERSION_MINOR));
    //QMessageBox::information(this, tr("О программе"), msg);
}

void MainWindow::openModel() {
    /*QString currentDir = QDir::currentPath();

    QStringList files = QFileDialog::getOpenFileNames(
                         this,
                         tr("Выберите один или несколько файлов"),
                         currentDir,
                         "Model files (*.csfdb *.iges *.brep *.rle *.step *.stl)\n"
                         "Images (*.xwd *.bmp *.png *.jpeg *.jpg *.gif)\n"
                         "All files(*.*)");

    try {
        openFiles(files);
    } catch(Common::FileException& err) {
        QMessageBox::critical(this, tr("Ошибка"), err.what());
        return;
    }*/
}

ChildWindow* MainWindow::newChildWindow() {
    Model::SharedPtr model = boost::make_shared<Model>();

    ChildWindow* window = new ChildWindow(model, this);
    mdiArea->addSubWindow(window);

    windowModelMap.insert(window, model);

    window->show();
    window->setWindowState(Qt::WindowMaximized);
    window->setAttribute(Qt::WA_DeleteOnClose);

    return window;
}

void MainWindow::childWindowActivated(QMdiSubWindow* window) {
    if (!window)
        return;

    if (currentChild) {
        disconnect(currentChild, SIGNAL(selectionChanged()),
            this, SLOT(viewSelectionChanged()));
    }

    currentChild = qobject_cast<ChildWindow*>(window);

    //shapesTreeView->setModel(currentModel().getQModel());

    connect(currentChild, SIGNAL(selectionChanged()),
        this, SLOT(viewSelectionChanged()));
    connect(currentChild, SIGNAL(closed()),
        this, SLOT(childWindowClosed()));

    enableViewActions();
}

void MainWindow::childWindowClosed() {
    currentChild = 0;

    disableViewActions();
}

void MainWindow::viewSelectionChanged() {
}

void MainWindow::viewFront() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewFront();
}

void MainWindow::viewBack() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewBack();
}

void MainWindow::viewTop() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewTop();
}

void MainWindow::viewBottom() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewBottom();
}

void MainWindow::viewLeft() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewLeft();
}

void MainWindow::viewRight() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewRight();
}

void MainWindow::viewAll() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewAll();
}

void MainWindow::viewAxometric() {
    ChildWindow& window = currentChildWindow();
    window.getView().viewAxometric();
}

void MainWindow::selectNeutral() {
    //Model& model = currentModel();
    //if (model)
        //model->selectNeutral();
}

void MainWindow::selectVertex() {
    //const Model& model = currentModel();
    //if (model)
        //model->selectVertex();
}

void MainWindow::selectEdge() {
    //const Model& model = currentModel();
    //if (model)
        //model->selectEdge();
}

void MainWindow::selectFace() {
    //const Model& model = currentModel();
    //if (model)
        //model->selectFace();
}

void MainWindow::selectSolid() {
    //const Model& model = currentModel();
    //if (model)
        //model->selectSolid();
}

void MainWindow::disableViewActions() {
}

void MainWindow::enableViewActions() {
}

}

