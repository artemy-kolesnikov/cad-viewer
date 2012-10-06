/*
 * inventorshape.cpp: Open Inventor shape presentation
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

#include "gui/viewer/inventor/inventorshape.h"

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoLocateHighlight.h>
#include <Inventor/nodes/SoPointSet.h>

#include <BRepBndLib.hxx>
#include <BRepMesh.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomLProp_SLProps.hxx>
#include <Poly_Array1OfTriangle.hxx>
#include <Poly_Polygon3D.hxx>
#include <Poly_PolygonOnTriangulation.hxx>
#include <Poly_Triangulation.hxx>
#include <Poly_Triangle.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <gp_Trsf.hxx>

#include <vector>

#include <QDebug>

namespace {

void getIndexedVerts(const TopoDS_Face& face, std::vector<SbVec3f>& vertices,
        std::vector<int32_t>& indices) {
    TopLoc_Location location;

    Handle(Poly_Triangulation) polygon = BRep_Tool::Triangulation(face, location);

    if (polygon.IsNull()) {
        //throw exception
        return;
    }

    gp_Trsf transform;
    bool identity = true;
    if (!location.IsIdentity()) {
        identity = false;
        transform = location.Transformation();
    }

    vertices.resize(polygon->NbNodes());
    indices.resize(4 * polygon->NbTriangles());

    TopAbs_Orientation orient = face.Orientation();

    const Poly_Array1OfTriangle& triangles = polygon->Triangles();

    const TColgp_Array1OfPnt& nodes = polygon->Nodes();

    for (int triangleIndex = 1; triangleIndex <= polygon->NbTriangles(); ++triangleIndex) {
        Standard_Integer index1, index2, index3;
        triangles.Value(triangleIndex).Get(index1, index2, index3);

        // change orientation of the triangles
        if (orient != TopAbs_FORWARD) {
            std::swap(index1, index2);
        }

        gp_Pnt point1 = nodes(index1);
        gp_Pnt point2 = nodes(index2);
        gp_Pnt point3 = nodes(index3);

        // transform the vertices to the place of the face
        if (!identity) {
            point1.Transform(transform);
            point2.Transform(transform);
            point3.Transform(transform);
        }

        --index1;
        --index2;
        --index3;

        vertices[index1].setValue(point1.X(), point1.Y(), point1.Z());
        vertices[index2].setValue(point2.X(), point2.Y(), point2.Z());
        vertices[index3].setValue(point3.X(), point3.Y(), point3.Z());

        int index = triangleIndex - 1;
        indices[4 * index + 0] = index1;
        indices[4 * index + 1] = index2;
        indices[4 * index + 2] = index3;
        indices[4 * index + 3] = SO_END_FACE_INDEX;
    }
}

void computeEdges(SoGroup* edgeRoot, const TopoDS_Shape &shape) {
    // get a indexed map of edges
    TopTools_IndexedMapOfShape mapOfShape;
    TopExp::MapShapes(shape, TopAbs_EDGE, mapOfShape);

    // build up map edge->face
    TopTools_IndexedDataMapOfShapeListOfShape edge2Face;
    TopExp::MapShapesAndAncestors(shape, TopAbs_EDGE, TopAbs_FACE, edge2Face);

    const size_t lastShapeIndex = mapOfShape.Extent();

    for (size_t shapeIndex = 1; shapeIndex <= lastShapeIndex; ++shapeIndex) {
        const TopoDS_Edge& edge = TopoDS::Edge(mapOfShape(shapeIndex));

        // Edge transformation
        gp_Trsf transform;
        bool identity = true;
        TopLoc_Location location;

        Handle(Poly_Polygon3D) polygon = BRep_Tool::Polygon3D(edge, location);

        // Triangulation vertices
        std::vector<SbVec3f> vertices;

        if (!polygon.IsNull()) {
            // Edges already triangulated

            if (!location.IsIdentity()) {
                identity = false;
                transform = location.Transformation();
            }

            vertices.resize(polygon->NbNodes());

            const TColgp_Array1OfPnt& nodes = polygon->Nodes();

            for (Standard_Integer nodeIndex = nodes.Lower(); nodeIndex <= nodes.Upper(); ++nodeIndex) {
                gp_Pnt point = nodes(nodeIndex);

                if (!identity) {
                    point.Transform(transform);
                }

                vertices[nodeIndex].setValue(point.X(), point.Y(), point.Z());
            }
        } else {
            // Get triangulation from attached face
            const TopoDS_Face& face = TopoDS::Face(edge2Face.FindFromKey(edge).First());

            Handle(Poly_Triangulation) triangulation  = BRep_Tool::Triangulation(face,location);

            if (!location.IsIdentity()) {
                identity = false;
                transform = location.Transformation();
            }

            if (triangulation.IsNull()) {
                // throw exception;
                return;
            }

            // Get appriximate presentation of triangulated polygon
            Handle(Poly_PolygonOnTriangulation) polygon = BRep_Tool::PolygonOnTriangulation(edge, triangulation, location);

            if (polygon.IsNull()) {
                // polygon does not exist
                continue;
            }

            vertices.resize(polygon->NbNodes());

            const TColStd_Array1OfInteger& indices = polygon->Nodes();
            const TColgp_Array1OfPnt& nodes = triangulation->Nodes();

            int pos = 0;
            for (Standard_Integer index = indices.Lower(); index <= indices.Upper(); ++index) {
                gp_Pnt point = nodes(indices.Value(index));

                if (!identity) {
                    point.Transform(transform);
                }

                vertices[pos++].setValue(point.X(), point.Y(), point.Z());
            }
        }

        // define vertices
        SoCoordinate3 * coords = new SoCoordinate3;
        coords->point.setValues(0, vertices.size(), &vertices[0]);
        edgeRoot->addChild(coords);

        SoLocateHighlight* h = new SoLocateHighlight();

        SoLineSet * lineset = new SoLineSet;
        h->addChild(lineset);
        edgeRoot->addChild(h);
    }
}

void computeVertices(SoGroup* vertexRoot, const TopoDS_Shape &shape) {
    TopTools_IndexedMapOfShape mapOfShape;
    TopExp::MapShapes(shape, TopAbs_VERTEX, mapOfShape);

    const size_t lastShapeIndex = mapOfShape.Extent();
    for (size_t shapeIndex = 1; shapeIndex <= lastShapeIndex; ++shapeIndex) {
        const TopoDS_Vertex& vertex = TopoDS::Vertex(mapOfShape(shapeIndex));

        SoCoordinate3 * coords = new SoCoordinate3;
        coords->point.setNum(1);
        vertexRoot->addChild(coords);

        gp_Pnt point = BRep_Tool::Pnt(vertex);
        coords->point.set1Value(0, static_cast<float>(point.X()),
                static_cast<float>(point.Y()), static_cast<float>(point.Z()));

        SoLocateHighlight* highlight = new SoLocateHighlight();

        SoPointSet * pointset = new SoPointSet;
        highlight->addChild(pointset);
        vertexRoot->addChild(highlight);
    }
}

void computeFaces(SoGroup* faceRoot, const TopoDS_Shape &shape) {
    TopExp_Explorer explorer;

    for (explorer.Init(shape, TopAbs_FACE); explorer.More(); explorer.Next()) {
        const TopoDS_Face& face = TopoDS::Face(explorer.Current());

        std::vector<SbVec3f> vertices;
        std::vector<int32_t> indices;

        getIndexedVerts(face, vertices, indices);

        if (vertices.empty())
            continue;

        SoCoordinate3* coords = new SoCoordinate3();
        coords->point.setValues(0, vertices.size(), &vertices[0]);
        faceRoot->addChild(coords);

        SoIndexedFaceSet * faceset = new SoIndexedFaceSet;
        faceset->coordIndex.setValues(0, indices.size(), &indices[0]);
        SoLocateHighlight* sel = new SoLocateHighlight();
        sel->addChild(faceset);
        faceRoot->addChild(sel);
    }
}

}

namespace Gui {
namespace Viewer {
namespace Inventor {

InventorShape::InventorShape(Modeling::Shape::SharedPtr aShape) : shape(aShape) {
    group.reset(new SoGroup());

    separator.reset(new SoSeparator());
    group->addChild(separator.get());

    computeShape();
}

SoGroup* InventorShape::getGroup() const {
    return group.get();
}

void InventorShape::computeShape() {
    Bnd_Box bounds;
    BRepBndLib::Add(shape->getShape(), bounds);
    bounds.SetGap(0.0);
    Standard_Real xMin, yMin, zMin, xMax, yMax, zMax;
    bounds.Get(xMin, yMin, zMin, xMax, yMax, zMax);
    Standard_Real deflection = ((xMax-xMin)+(yMax-yMin)+(zMax-zMin))/300.0 * 0.2;
    BRepMesh::Mesh(shape->getShape(), deflection);

    SoGroup* faces = new SoGroup();

    computeFaces(faces, shape->getShape());

    separator->addChild(faces);

    /*SoGroup* edges = new SoGroup();
    computeEdges(edges, shape->getShape());

    separator->addChild(edges);

    SoGroup* vertices = new SoGroup();
    computeVertices(vertices, shape->getShape());

    separator->addChild(vertices);*/
}

}
}
}
