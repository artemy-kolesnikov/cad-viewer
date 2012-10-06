/*
 * fileloader.h: Class for loading shape from file
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

#ifndef Modeling_FileLoader_H
#define Modeling_FileLoader_H

#include <list>
#include <string>

#include "modeling/shape.h"
#include "util/exception.h"

namespace Modeling {

class FileLoaderException : public Util::Exception {
public:
    FileLoaderException(const std::string& what) : Util::Exception(what) {}
};

class FileLoader {
public:
    static void loadShapes(const std::string& filePath, std::list<Shape::SharedPtr>& shapes);
};

}

#endif // Modeling_FileLoader_H
