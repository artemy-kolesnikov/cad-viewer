/*
 * cadviewerapplication.h: View application class
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

#ifndef Gui_CadViewerApplication_H
#define Gui_CadViewerApplication_H

#include <QApplication>

namespace Gui {

class MainWindow;

class CadViewerApplication : public QApplication {
    Q_OBJECT

public:
    CadViewerApplication(int& argc, char* argv[]);

    static MainWindow& getMainWindow();

private:
    static MainWindow* mainWindow;
};

}

#endif // Gui_CadViewerApplication_H
