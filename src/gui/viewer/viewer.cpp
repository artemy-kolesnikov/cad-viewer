/*
 * viewer.cpp: Base class for model rendering
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

#include "gui/viewer/viewer.h"

#include "gui/viewer/opencascadeviewer.h"

#include <boost/make_shared.hpp>

namespace Gui {
namespace Viewer {

Viewer::SharedPtr Viewer::create(Gui::Model::SharedPtr model) {
    return boost::make_shared<OpenCASCADEViewer>(model);
}

}
}
