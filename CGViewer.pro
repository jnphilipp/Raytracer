TEMPLATE		= app
TARGET			= CGViewer

CONFIG			+= qt warn_on release
QT          	+= opengl

CONFIG			+= console

QMAKE_CXXFLAGS 	+= -fopenmp

LIBS			+= -lGLEW -lGLU -fopenmp

OBJECTS_DIR		= ./obj
MOC_DIR 		= ./moc

HEADERS			= main.h GUI.h CGMath.h Matrix.h Model.h Scene.h EditWidgets.h Light.h SaveSceneDialog.h Raytracer.h Octree.h Voxel.h

SOURCES			= main.cpp GUI.cpp Matrix.cpp Model.cpp Scene.cpp EditWidgets.cpp Light.cpp SaveSceneDialog.cpp Raytracer.cpp Octree.cpp Voxel.cpp
