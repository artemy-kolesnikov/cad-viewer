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

#include "modeling/fileloader.h"

#include <boost/foreach.hpp>

using Modeling::FileLoader;
using Modeling::Shape;

namespace Gui {

void Model::load(QString& fileName) {
    std::list<Shape::SharedPtr> shapes;
    FileLoader::loadShapes(fileName.toStdString(), shapes);

    BOOST_FOREACH(Shape::SharedPtr shape, shapes) {
        addShape(shape);
    }

    this->fileName = fileName;

    Q_EMIT fileNameChanged(fileName);
}

void Model::addShape(Modeling::Shape::SharedPtr shape) {
    shapeList.push_back(shape);
    Q_EMIT shapeAdded(shape);
}

}

