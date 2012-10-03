/*
 * model.h: Model class. Keeps loaded data
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

#ifndef Gui_Model_H
#define Gui_Model_H

#include <QObject>
#include <QList>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <memory>

#include "model/shape.h"

namespace Gui {

class Model : public QObject {
    Q_OBJECT

public:
    typedef boost::shared_ptr<Model> SharedPtr;

    QString getFileName() const {
        return fileName;
    }

    const std::list< ::Model::Shape::SharedPtr >& getShapes() const {
        return shapeList;
    }

    void removeShape(::Model::Shape::SharedPtr shape);
    void addShape(::Model::Shape::SharedPtr shape);

Q_SIGNALS:
    void shapeAdded(::Model::Shape::SharedPtr shape);
    void shapeRemoved(::Model::Shape::SharedPtr shape);
    void fileNameChanged(QString& newFileName);

public Q_SLOTS:
    void load(QString& fileName);
    void save(QString& fileName);

private:
    QString fileName;
    std::list< ::Model::Shape::SharedPtr > shapeList;
};

}

#endif // Gui_Model_H
