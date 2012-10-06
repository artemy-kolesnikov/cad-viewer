/*
 * fileloader.cpp: Class for loading shape from file
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

#include "modeling/fileloader.h"

#include <QFileInfo>
#include <QString>

#include <boost/make_shared.hpp>

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <FSD_File.hxx>
#include <IGESControl_Reader.hxx>
#include <MgtBRep.hxx>
#include <PTColStd_PersistentTransientMap.hxx>
#include <PTopoDS_HShape.hxx>
#include <STEPControl_Reader.hxx>
#include <ShapeSchema.hxx>
#include <Storage_HSeqOfRoot.hxx>
#include <Storage_Root.hxx>
#include <TopoDS_Shape.hxx>

using Modeling::Shape;

namespace {

enum FileType {
    ftUnknown,
    ftBREP,
    ftCSFDB,
    ftIGES,
    ftSTEP,
    ftSTL,
    ftVRML
};

FileType getFileType(const std::string& filePath);

bool loadBREP(const std::string& filePath, std::list<Shape::SharedPtr>& shapes);
bool loadIGES(const std::string& filePath, std::list<Shape::SharedPtr>& shapes);
bool loadSTEP(const std::string& filePath, std::list<Shape::SharedPtr>& shapes);
bool loadCSFDB(const std::string& filePath, std::list<Shape::SharedPtr>& shapes);

}

namespace Modeling {

void FileLoader::loadShapes(const std::string& filePath, std::list<Shape::SharedPtr>& shapes) {
    QFileInfo fi(filePath.c_str());

    if (!fi.exists()) {
        throw FileLoaderException("File doesn't exist");
    }

	FileType ft = getFileType(filePath);

    bool result = false;

    switch (ft) {
        case ftBREP:
            result = loadBREP(filePath, shapes);
            break;
        case ftCSFDB:
            result = loadCSFDB(filePath, shapes);
            break;
        case ftIGES:
            result = loadIGES(filePath, shapes);
            break;
        case ftSTEP:
            result = loadSTEP(filePath, shapes);
            break;
        default:
            throw FileLoaderException("Unknown file type");
    }

    if (!result) {
        throw FileLoaderException("Could not load file");
    }
}

}

namespace {

FileType getFileType(const std::string& filePath) {
    QFileInfo fi(filePath.c_str());

    QString ext = fi.completeSuffix();

    if (ext == "brep" || ext == "rle")
        return ftBREP;

    if (ext == "csfdb")
        return ftCSFDB;

    if (ext == "iges")
        return ftIGES;

    if (ext == "step")
        return ftSTEP;

    if (ext == "stl")
        return ftSTL;

    if (ext == "vrml.gs")
        return ftVRML;

    return ftUnknown;
}

bool loadBREP(const std::string& filePath, std::list<Shape::SharedPtr>& shapes) {
    TopoDS_Shape shape;
    BRep_Builder builder;

    Standard_Boolean result = BRepTools::Read(shape, (Standard_CString)filePath.c_str(), builder);
    if (result)
        shapes.push_back(boost::make_shared<Modeling::Shape>(shape));

    return result;
}

bool loadIGES(const std::string& filePath, std::list<Shape::SharedPtr>& shapes) {
    IGESControl_Reader reader;
    int status = reader.ReadFile((Standard_CString)filePath.c_str());

    if (status == IFSelect_RetDone) {
        reader.TransferRoots();
        shapes.push_back(boost::make_shared<Modeling::Shape>(reader.OneShape()));
    }

    return (status == IFSelect_RetDone);
}

bool loadSTEP(const std::string& filePath, std::list<Shape::SharedPtr>& shapes) {
    STEPControl_Reader reader;
    IFSelect_ReturnStatus status = reader.ReadFile((Standard_CString)filePath.c_str());

    if (status == IFSelect_RetDone) {
        bool failsonly = false;
        reader.PrintCheckLoad(failsonly, IFSelect_ItemsByEntity);

        int nbr = reader.NbRootsForTransfer();
        reader.PrintCheckTransfer(failsonly, IFSelect_ItemsByEntity);

        for (Standard_Integer n = 1; n <= nbr; ++n) {
            reader.TransferRoot(n);
            int nbs = reader.NbShapes();
            if (nbs > 0) {
                for (int i = 1; i <= nbs; ++i) {
                    shapes.push_back(boost::make_shared<Modeling::Shape>(reader.Shape(i)));
                }
            }
        }
    }

    return (status == IFSelect_RetDone);
}

bool loadCSFDB(const std::string& filePath, std::list<Shape::SharedPtr>& shapes) {
    if (FSD_File::IsGoodFileType((Standard_CString)filePath.c_str()) != Storage_VSOk)
        return false;

    static FSD_File fileDriver;
    TCollection_AsciiString name((Standard_CString)filePath.c_str());

    if (fileDriver.Open(name, Storage_VSRead) != Storage_VSOk)
        return false;

    Handle(ShapeSchema) schema = new ShapeSchema();
    Handle(Storage_Data) data  = schema->Read(fileDriver);
    if (data->ErrorStatus() != Storage_VSOk)
        return false;

    fileDriver.Close();

    Handle(Storage_HSeqOfRoot) roots = data->Roots();

    for (int i = 1; i <= roots->Length(); ++i) {
        Handle(Storage_Root) r = roots->Value(i);
        Handle(Standard_Persistent) p = r->Object();
        Handle(PTopoDS_HShape) pShape = Handle(PTopoDS_HShape)::DownCast(p);
        if (!pShape.IsNull() ) {
            PTColStd_PersistentTransientMap map;
            TopoDS_Shape tShape;
            MgtBRep::Translate(pShape, map, tShape, MgtBRep_WithTriangle);
            shapes.push_back(boost::make_shared<Modeling::Shape>(tShape));
        }
    }

    return true;
}

}
