/*
 * actionlist.cpp: Class for action list managing
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

#include "gui/actionlist.h"

namespace Gui {

ActionList::ActionList(QObject* parent) : QObject(parent) {
}

ActionList::~ActionList() {
    qDeleteAll(actionList);
}

void ActionList::addAction(QAction* action) {
    action->setParent(this);
    actionList.push_back(action);
}

void ActionList::removeAction(QAction* action) {
    int index = actionList.indexOf(action);
    if (index != -1) {
        actionList.removeAll(action);
        action->deleteLater();
    }
}

void ActionList::setVisible(bool visible) {
    QAction* action;
    foreach(action, actionList)
        action->setVisible(visible);
}

bool ActionList::isVisible() const {
    if (actionList.size() == 0)
        return false;

    return actionList.at(0)->isVisible();
}

void ActionList::setEnabled(bool enabled) {
    QAction* action;
    foreach(action, actionList)
        action->setEnabled(enabled);
}

bool ActionList::isEnabled() const {
    if (actionList.size() == 0)
        return false;

    return actionList.at(0)->isEnabled();
}

}

