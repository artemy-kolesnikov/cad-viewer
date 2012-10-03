/*
 * actionlist.h: Class for action list managing
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

#ifndef ACTION_LIST_HEADER
#define ACTION_LIST_HEADER

#include <QObject>
#include <QList>
#include <QAction>

namespace Gui {

class ActionList : public QObject {
public:
    ActionList(QObject* parent = 0);
    ~ActionList();

    void addAction(QAction* action);
    void removeAction(QAction* action);

    void setVisible(bool visible);
    bool isVisible() const;

    void setEnabled(bool enabled);
    bool isEnabled() const;

private:
    QList<QAction*> actionList;
};

}

#endif // ACTION_LIST_HEADER

