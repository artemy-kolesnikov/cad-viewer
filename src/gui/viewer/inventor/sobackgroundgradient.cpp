/*
 * sobackgroundgradient.cpp: Background gradient color
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

#include "gui/viewer/inventor/sobackgroundgradient.h"

#include <GL/gl.h>

namespace Gui {
namespace Viewer {
namespace Inventor {

SO_NODE_SOURCE(SoBackgroundGradient);

void SoBackgroundGradient::initClass() {
    SO_NODE_INIT_CLASS(SoBackgroundGradient, SoNode, "Node");
}

void SoBackgroundGradient::finish() {
    atexit_cleanup();
}

void SoBackgroundGradient::setColorGradient(const SbColor& fromColor, const SbColor& toColor) {
    this->fromColor = fromColor;
    this->toColor = toColor;
}

void SoBackgroundGradient::GLRender(SoGLRenderAction* action) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_TRIANGLE_STRIP);

    glColor3f(fromColor[0], fromColor[1], fromColor[2]);
    glVertex2f(-1, 1);

    glColor3f(toColor[0], toColor[1], toColor[2]);
    glVertex2f(-1,-1);

    glColor3f(fromColor[0], fromColor[1], fromColor[2]);
    glVertex2f(1, 1);

    glColor3f(toColor[0], toColor[1], toColor[2]);
    glVertex2f( 1,-1);

    glEnd();

    glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

}
}
}
