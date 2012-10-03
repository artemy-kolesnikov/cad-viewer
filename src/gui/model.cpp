/*
 * model.cpp: Model class. Keeps loaded data
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

#include "model.h"

namespace Gui {

void Model::load(QString& fileName) {
    /*std::list<TopoDS_Shape> shapes;
    FileHelper::readFile(fileName, shapes);

    std::list<TopoDS_Shape>::const_iterator it = shapes.begin();
    for (; it != shapes.end(); ++it)
        addShape(Shape(*it));*/

    this->fileName = fileName.toStdString();

    Q_EMIT fileNameChanged(fileName);
}

void Model::save(QString& fileName)
{
}

void Model::removeShape(const Shape& shape) {
    /*int index = shapeList.indexOf(shape);
    if (index != -1)
    {
        Q_EMIT shapeRemoved(shape);
        shapeList.removeAt(index);
    }*/
}

void Model::addShape(const Shape& shape) {
    /*shapeList.push_back(shape);
    Q_EMIT shapeAdded(shape);*/
}

}

