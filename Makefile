#############################################################################
# Makefile for building: CGViewer
# Generated by qmake (2.01a) (Qt 4.8.1) on: Sat Jun 16 16:01:00 2012
# Project:  CGViewer.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile CGViewer.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -msse4.1 -fopenmp -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -I/usr/X11R6/include -Imoc
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L/usr/X11R6/lib64 -lGLEW -lGLU -fopenmp -lQtOpenGL -lQtGui -lQtCore -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = main.cpp \
		gui.cpp \
		Matrix.cpp \
		Model.cpp \
		Scene.cpp \
		EditWidgets.cpp \
		Light.cpp \
		SaveSceneDialog.cpp \
		Raytracer.cpp \
		Octree.cpp \
		Voxel.cpp \
		ShaderStuff.cpp moc/moc_gui.cpp \
		moc/moc_Scene.cpp \
		moc/moc_EditWidgets.cpp \
		moc/moc_SaveSceneDialog.cpp \
		moc/moc_Raytracer.cpp
OBJECTS       = obj/main.o \
		obj/gui.o \
		obj/Matrix.o \
		obj/Model.o \
		obj/Scene.o \
		obj/EditWidgets.o \
		obj/Light.o \
		obj/SaveSceneDialog.o \
		obj/Raytracer.o \
		obj/Octree.o \
		obj/Voxel.o \
		obj/ShaderStuff.o \
		obj/moc_gui.o \
		obj/moc_Scene.o \
		obj/moc_EditWidgets.o \
		obj/moc_SaveSceneDialog.o \
		obj/moc_Raytracer.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		CGViewer.pro
QMAKE_TARGET  = CGViewer
DESTDIR       = 
TARGET        = CGViewer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: CGViewer.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile CGViewer.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile CGViewer.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/CGViewer1.0.0 || $(MKDIR) obj/CGViewer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/CGViewer1.0.0/ && $(COPY_FILE) --parents main.h gui.h CGMath.h Matrix.h Model.h Scene.h EditWidgets.h Light.h SaveSceneDialog.h Raytracer.h Octree.h Voxel.h ShaderStuff.h obj/CGViewer1.0.0/ && $(COPY_FILE) --parents main.cpp gui.cpp Matrix.cpp Model.cpp Scene.cpp EditWidgets.cpp Light.cpp SaveSceneDialog.cpp Raytracer.cpp Octree.cpp Voxel.cpp ShaderStuff.cpp obj/CGViewer1.0.0/ && (cd `dirname obj/CGViewer1.0.0` && $(TAR) CGViewer1.0.0.tar CGViewer1.0.0 && $(COMPRESS) CGViewer1.0.0.tar) && $(MOVE) `dirname obj/CGViewer1.0.0`/CGViewer1.0.0.tar.gz . && $(DEL_FILE) -r obj/CGViewer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc/moc_gui.cpp moc/moc_Scene.cpp moc/moc_EditWidgets.cpp moc/moc_SaveSceneDialog.cpp moc/moc_Raytracer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_gui.cpp moc/moc_Scene.cpp moc/moc_EditWidgets.cpp moc/moc_SaveSceneDialog.cpp moc/moc_Raytracer.cpp
moc/moc_gui.cpp: Scene.h \
		Model.h \
		Matrix.h \
		CGMath.h \
		Light.h \
		EditWidgets.h \
		SaveSceneDialog.h \
		gui.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) gui.h -o moc/moc_gui.cpp

moc/moc_Scene.cpp: Model.h \
		Matrix.h \
		CGMath.h \
		Light.h \
		EditWidgets.h \
		SaveSceneDialog.h \
		Scene.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Scene.h -o moc/moc_Scene.cpp

moc/moc_EditWidgets.cpp: Light.h \
		CGMath.h \
		Matrix.h \
		EditWidgets.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) EditWidgets.h -o moc/moc_EditWidgets.cpp

moc/moc_SaveSceneDialog.cpp: CGMath.h \
		SaveSceneDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SaveSceneDialog.h -o moc/moc_SaveSceneDialog.cpp

moc/moc_Raytracer.cpp: CGMath.h \
		Octree.h \
		Matrix.h \
		Voxel.h \
		Raytracer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Raytracer.h -o moc/moc_Raytracer.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

obj/main.o: main.cpp main.h \
		gui.h \
		Scene.h \
		Model.h \
		Matrix.h \
		CGMath.h \
		Light.h \
		EditWidgets.h \
		SaveSceneDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o main.cpp

obj/gui.o: gui.cpp Raytracer.h \
		CGMath.h \
		Octree.h \
		Matrix.h \
		Voxel.h \
		gui.h \
		Scene.h \
		Model.h \
		Light.h \
		EditWidgets.h \
		SaveSceneDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/gui.o gui.cpp

obj/Matrix.o: Matrix.cpp Matrix.h \
		CGMath.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Matrix.o Matrix.cpp

obj/Model.o: Model.cpp Model.h \
		Matrix.h \
		CGMath.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Model.o Model.cpp

obj/Scene.o: Scene.cpp Scene.h \
		Model.h \
		Matrix.h \
		CGMath.h \
		Light.h \
		EditWidgets.h \
		SaveSceneDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Scene.o Scene.cpp

obj/EditWidgets.o: EditWidgets.cpp EditWidgets.h \
		Light.h \
		CGMath.h \
		Matrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/EditWidgets.o EditWidgets.cpp

obj/Light.o: Light.cpp Light.h \
		CGMath.h \
		Matrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Light.o Light.cpp

obj/SaveSceneDialog.o: SaveSceneDialog.cpp SaveSceneDialog.h \
		CGMath.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/SaveSceneDialog.o SaveSceneDialog.cpp

obj/Raytracer.o: Raytracer.cpp Raytracer.h \
		CGMath.h \
		Octree.h \
		Matrix.h \
		Voxel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Raytracer.o Raytracer.cpp

obj/Octree.o: Octree.cpp Octree.h \
		CGMath.h \
		Matrix.h \
		Voxel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Octree.o Octree.cpp

obj/Voxel.o: Voxel.cpp Voxel.h \
		CGMath.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Voxel.o Voxel.cpp

obj/ShaderStuff.o: ShaderStuff.cpp ShaderStuff.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/ShaderStuff.o ShaderStuff.cpp

obj/moc_gui.o: moc/moc_gui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_gui.o moc/moc_gui.cpp

obj/moc_Scene.o: moc/moc_Scene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_Scene.o moc/moc_Scene.cpp

obj/moc_EditWidgets.o: moc/moc_EditWidgets.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_EditWidgets.o moc/moc_EditWidgets.cpp

obj/moc_SaveSceneDialog.o: moc/moc_SaveSceneDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_SaveSceneDialog.o moc/moc_SaveSceneDialog.cpp

obj/moc_Raytracer.o: moc/moc_Raytracer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_Raytracer.o moc/moc_Raytracer.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

