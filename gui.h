#ifndef GUI_H
#define GUI_H

#include <QtGui>
#include <vector>
#include <sstream>
#include <iostream>
#include "Scene.h"
#include "EditWidgets.h"



class GUI : public QMainWindow
{
	Q_OBJECT
	public:
	     GUI();

	private slots:
		void loadFile();
		//void setShaders();
		void setCulling();
		void saveScene();
		void loadScene();
		void addLight();
		void scale();
		void translate();
		void rotate();
		void deleteObject();
		void render();
		
	private:
		//the scene to be rendered
		Scene* scene;	
	
		//just for now
		//bool useShaders;
		bool useCulling;
}; 

#endif
 
