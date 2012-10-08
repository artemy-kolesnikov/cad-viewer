/*
 * soaxes.cpp: Axes in right corner
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

#include "gui/viewer/inventor/soaxes.h"

#include <Inventor/SbMatrix.h>
#include <Inventor/SbRotation.h>
#include <Inventor/SbVec3f.h>

#include <GL/gl.h>

namespace Gui {
namespace Viewer {
namespace Inventor {

SO_NODE_SOURCE(SoAxes);

void SoAxes::initClass() {
    SO_NODE_INIT_CLASS(SoAxes, SoNode, "Node");
}

void SoAxes::finish() {
    atexit_cleanup();
}

void SoAxes::GLRender(SoGLRenderAction* action) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);

    SbMat matrix;
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat*>(matrix));

    glPushMatrix();

    SbMatrix sbMatrix(matrix);

    SbVec3f translation;
    SbRotation rotation;
    SbVec3f scaleFactor;
    SbRotation scaleOrientation;

    sbMatrix.getTransform(translation, rotation, scaleFactor, scaleOrientation);
    rotation.getValue(sbMatrix);
    sbMatrix.getValue(matrix);

    glLoadMatrixf(reinterpret_cast<GLfloat*>(matrix));

    GLint wndSize[4];
    glGetIntegerv(GL_VIEWPORT, wndSize);

    float ratio = wndSize[3] / (float)wndSize[2];

    float scaleX = wndSize[2] > wndSize[3] ? wndSize[3] / (float)wndSize[2] : 1.0;
    float scaleY = wndSize[3] > wndSize[2] ? wndSize[2] / (float)wndSize[3] : 1.0;

    glScalef(0.25 * scaleX, 0.25 * scaleY, 0.25);
    glLineWidth(2.0);

    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

}
}
}
