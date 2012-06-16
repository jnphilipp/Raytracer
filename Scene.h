#ifndef SCENE_H
#define SCENE_H

#include "ShaderStuff.h"
#include "Model.h"
#include "Light.h"
#include "EditWidgets.h"
#include "SaveSceneDialog.h"

#include <QtOpenGL>
#include <GL/glu.h>

class Scene : public QGLWidget
{
	Q_OBJECT
	public:
		Scene(QWidget* parent);
		~Scene();

		void addLight();
		void setUseShaders(bool s);
		void scaleObject(double sx, double sy, double sz);
		void translateObject(double dx, double dy, double dz);
		void rotateObject(double ax, double ay, double az,double angle);
		void deleteObject();		
		void setCullingMode(bool enable); //only backface culling
		//reads a file, creates a model and adds it to the scene
		bool readOBJFile(QString path);
		void saveAsPrimitive(QString path);
		void saveAnimation(QString path);
		void loadPrimitive(QString path);

	public slots:
		void refresh();

	protected:
		void initializeGL();
		void resizeGL( int width, int height );
		void paintGL();  
  		void wheelEvent(QWheelEvent *event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		void mouseMoveEvent(QMouseEvent *event);
		void keyPressEvent(QKeyEvent *event);
	
	private:
		
		//screen adjustments
		int width;
		int height;
		int xRot;
		int yRot;
		int zRot;
		double zoom;
		double transx;
		double transy;
		void normalizeAngle(int *angle);
		void setTransformations();
		void setXRotation(int angle);
		void setYRotation(int angle);
		void setZRotation(int angle);
		bool initShaders(std::string vs, std::string fs);
		void drawEnvironment();
		Vector getCameraPosition();
		Vector getViewDirection();
		Vector getUpVector();
		void saveScene(QString path, Parameters p);
		//input related
		QPoint lastPos;
		bool mousepressed;		
		//shadestuff
		bool shadersAvaiable;
		bool useShaders; //used for switching beetween fixed and programmable pipeline
		GLuint phongShaderId;
		//the rest
		vector<Model*> models;
		vector<Light*> lights;
		//GUI
		GLUquadricObj *xCyl, *yCyl, *zCyl;
		
		//bool initShaders();

		//picking stuff
		GLuint selectBuf[512];
		void startPicking(int cursorX, int cursorY);
		void stopPicking();
		void processHits (GLint hits, GLuint buffer[]);
		int selectedObject;
		int selectedAxis;

		//read the materials for the model
		void readMTLFile(QString path, vector <Material> *materials);
		//used to name the Objects (give'em an ID)
		int nameCount;


};

#endif



