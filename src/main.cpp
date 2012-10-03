/*
 * CAD Viewer
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

#include <QTextCodec>
#include <QPlastiqueStyle>
#include <QMessageBox>
#include <QStringList>

#include <locale.h>

#include "gui/mainwindow.h"
#include "gui/cadviewerapplication.h"

#if !defined Q_OS_WIN32 && !defined Q_OS_LINUX
	#error "Supported only Linux and Windows"
#endif

int main(int argc, char *argv[]) {
	try {
		Gui::CADViewerApplication app(argc, argv);

		Gui::CADViewerApplication::setStyle(new QPlastiqueStyle());

		setlocale(LC_ALL, "rus_rus");
		setlocale(LC_NUMERIC, "English");
		setlocale(LC_TIME, "English");

		QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
		QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
		QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

		Gui::MainWindow& win = Gui::CADViewerApplication::getMainWindow();
		win.show();

		QStringList args;
		if (argc > 1) {
			for (int i = 1; i < argc; ++i)
				args << argv[i];
		}

		win.openFiles(args);

		return app.exec();
	} catch(...) {
		QMessageBox::critical(0, QObject::tr("Error"),
			QObject::tr("Unhandled exception"));
		return -1;
	}
}

