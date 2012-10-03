/*
 * childwindow.h: Child window class
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

#ifndef CHILD_WINDOW_HEADER
#define CHILD_WINDOW_HEADER

#include <QCloseEvent>
#include <QMdiSubWindow>
#include <QString>

#include "gui/model.h"

namespace Gui {

class View;

class ChildWindow : public QMdiSubWindow {
    Q_OBJECT

public:
    ChildWindow(Model::SharedPtr model, QWidget* parent = 0);

    const View& getView() const {
        return *view;
    }

    View& getView() {
        return *view;
    }

    const Model& getModel() const {
        return *model.get();
    }

    Model& getModel() {
        return *model.get();
    }

Q_SIGNALS:
    void selectionChanged();
    void closed();

protected:
    virtual void closeEvent(QCloseEvent* event);

private Q_SLOTS:
    void modelFileNameChanged(QString& fileName);

private:
    void createUI();

    Model::SharedPtr model;
    View* view;
};

}

#endif // CHILD_WINDOW_HEADER
