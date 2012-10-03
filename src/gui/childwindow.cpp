/*
 * childwindow.cpp: Child window class
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

#include "gui/childwindow.h"
#include "gui/view.h"

namespace Gui {

ChildWindow::ChildWindow(Model::SharedPtr model, QWidget* parent) : QMdiSubWindow(parent),
        model(model), view(0) {
    Q_ASSERT(model);

    connect(model.get(), SIGNAL(fileNameChanged(QString&)),
        this, SLOT(modelFileNameChanged(QString&)));

    createUI();
}

void ChildWindow::createUI()
{
    view = new View(this);
    setWidget(view);

    view->setModel(model);

    connect(view, SIGNAL(selectionChanged()),
        this, SIGNAL(selectionChanged()));
}

void ChildWindow::modelFileNameChanged(QString& fileName) {
    setWindowTitle(fileName);
}

void ChildWindow::closeEvent(QCloseEvent* event) {
    Q_EMIT closed();
    QWidget::closeEvent(event);
}

}

