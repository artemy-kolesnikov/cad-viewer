/*
 * sobackgroundgradient.h: Background gradient color
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

#ifndef Gui_Viewer_Inventor_SoBackgroundGradient_H
#define Gui_Viewer_Inventor_SoBackgroundGradient_H

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SbColor.h>

namespace Gui {
namespace Viewer {
namespace Inventor {

class SoBackgroundGradient : public SoNode {
    typedef SoNode inherited;

    SO_NODE_HEADER(SoBackgroundGradient);

public:
    static void initClass();
    static void finish();

    void GLRender(SoGLRenderAction* action);

    void setColorGradient(const SbColor& fromColor, const SbColor& toColor);

protected:
    virtual ~SoBackgroundGradient() {}

private:
    SbColor fromColor;
    SbColor toColor;
};

}
}
}

#endif // Gui_Viewer_Inventor_SoBackgroundGradient_H
