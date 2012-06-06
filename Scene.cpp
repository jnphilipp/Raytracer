#include "Scene.h"
#include <fstream>

Scene::Scene(QWidget *parent)
{
	setParent(parent);
	setGeometry(0, 0, 800, 600);
	initializeGL();
	resizeGL(800, 600);
	zoom = -10.0;
	xRot = 0.0;
	yRot = 0.0;
	zRot = 0.0;
	transx = 0.0;
	transy = -2.0;
	mousepressed = false;
	useShaders = false;
	shadersAvaiable = false;
	selectedObject = selectedAxis = -1;

	//init GUI
	xCyl = gluNewQuadric();
	yCyl = gluNewQuadric();
	zCyl = gluNewQuadric();

	/*makeCurrent();
	GLenum err = glewInit();
    	if (GLEW_OK != err)
    		cout << "Error: glewInit() failed\n";
    	else
		cout << "Succesfully initiated GLEW\n";
	shadersAvaiable=initShaders();
	useShaders=shadersAvaiable;*/
	nameCount = 10;
	show();
	updateGL();
	
}

Scene::~Scene()
{
}

void Scene::startPicking(int cursorX, int cursorY)
{
	GLint viewport[4];

	glSelectBuffer(512, selectBuf);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(cursorX, viewport[3]-cursorY, 5, 5, viewport);
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
	glPushMatrix();
	updateGL();
	glPopMatrix();
	stopPicking();
	
}

void Scene::stopPicking()
{
	int hits;
	
	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	
	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);
	
	// if there are hits process them
	if (hits != 0)
		processHits(hits,selectBuf);
	else
	{
		selectedObject = -1;
		selectedAxis = -1;
	}

}

void Scene::processHits(GLint hits, GLuint buffer[])
{
	GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

	//cout<<"hits = "<<hits<<"\n";
	ptr = (GLuint *) buffer;
	minZ = 0xffffffff;
	uint count = 0;
	for (int i = 0; i < hits; i++)
	{	
		names = *ptr;
		ptr++;
		if (*ptr < minZ)
		{
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr+2;
			++count;
		}
		
		ptr += names+2;
	}
	ptr = ptrNames;
	int selectedEntity = -1;
	for (uint j = 0; j < numberOfNames; j++,ptr++) 
			selectedEntity = *ptr;
			
	//unselect, if selected
	if (selectedEntity == selectedObject)
	{
		selectedObject = -1;
		selectedAxis = -1;
		return;
	}	
	if (selectedEntity > 9)
		selectedObject = selectedEntity;
	else
		selectedAxis = selectedEntity;
	
	cout<<"Selected Entity: "<<selectedEntity<<endl;

	
}

void Scene::initializeGL()
{
	//glClearColor(0.4, 0.4, 1.0, 0.0);
	glClearColor(0.1, 0.1, 0.3, 0.0);
	
	glDepthFunc(GL_LEQUAL);							// Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);						// Enable Depth Testing
	glDisable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//lighting
	glEnable(GL_LIGHTING);
	float position[] = {0.0,12.0,0.0,1.0};
	float ambient[] = {0.7,0.7,0.7,1.0};
	float diffuse[] = {0.9,0.9,0.9,1.0};
	float specular[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

}

/*bool Scene::initShaders()
{
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		cout<<"Ready for GLSL\n";
	}
	else 
	{
		cout<<"Not totally ready :( \n";
		return false;
	}

	//phong/shadowshader
	GLhandleARB vertexShaderHandle;
	GLhandleARB fragmentShaderHandle;
	
	vertexShaderHandle   = loadShader((char*)"Shaders/PhongShader_vert.c",GL_VERTEX_SHADER);
	fragmentShaderHandle = loadShader((char*)"Shaders/PhongShader_frag.c",GL_FRAGMENT_SHADER);

	if (vertexShaderHandle == 0 || fragmentShaderHandle == 0)
		return false;
	
	phongShaderId = glCreateProgramObjectARB();
	
	glAttachObjectARB(phongShaderId,vertexShaderHandle);
	glAttachObjectARB(phongShaderId,fragmentShaderHandle);
	glLinkProgramARB(phongShaderId);

	return true;
	
}*/


void Scene::resizeGL(int w, int h)
{
	height = h;
	width = w;

	// Reset the viewport
	glViewport(0, 0, width, height);
	// Reset the projection and modelview matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0);
	glMatrixMode(GL_MODELVIEW);	
    
}

void Scene::refresh()
{
	updateGL();
}


void Scene::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();

	if (selectedObject > 0) //check for axis -> since it does not work the "normal" way of picking (something is wrong with the ortho projection), 
							//we try color coding (this is a hack and not the way it should be)
	{
		GLint viewport[4];
		GLubyte pixel[3];
		glGetIntegerv(GL_VIEWPORT,viewport);
		glReadPixels(lastPos.x(), viewport[3]-lastPos.y(), 1, 1, GL_RGB,GL_UNSIGNED_BYTE, (void *)pixel);
		if (pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0)
			selectedAxis = 1;
		else
		if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0)
			selectedAxis = 2;
		else
		if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255)
			selectedAxis = 3;
		else
			selectedAxis = -1;
	}
	if (selectedAxis > 0) //we can drag the object
		return;
	cout<<"Selected Axis: "<<selectedAxis<<endl;
	startPicking(event->x(), event->y());
	updateGL();
}


void Scene::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (selectedAxis==-1) //if no widget is selected
	{
		if (event->buttons() & Qt::LeftButton) 
		{
			setXRotation(xRot + 8 * dy);
			setYRotation(yRot + 8 * dx);
		}
		else 
			if (event->buttons() & Qt::RightButton)
			{
				setXRotation(xRot + 8 * dy);
				setZRotation(zRot + 8 * dx);
			}
			else
				if (event->buttons() & Qt::MidButton)
				{
					transx+=(double)dx*0.01;
					transy-=(double)dy*0.01;
				}
	}
	else
	{
		//search the models
		int n=-1;
		for (uint i=0;i<models.size();++i)
		{
			if (models[i]->getName()==selectedObject)
			{
				n=i;
				break;
			}
		}
		if (n != -1)
		{
			if (event->buttons() & Qt::LeftButton) 
			{
				float vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
				glGetFloatv(GL_MODELVIEW_MATRIX, vals);	
				Matrix m(vals);
				if (selectedAxis == 1) //X
				{
					Vector transX = m*Vector(1.0, 0.0, 0.0, 1.0);
					if (90<xRot && xRot<270)
						models[n]->translate(-(float)(dx+dy)*0.01*transX(0), transX(1), transX(2));
					else
						models[n]->translate((float)(dx+dy)*0.01*transX(0), transX(1), transX(2));
				}
				if (selectedAxis == 2) //Y
				{
					Vector transY = m*Vector(0.0, 1.0, 0.0, 1.0);
					if (90<yRot && yRot<270)
						models[n]->translate(transY(0), (float)(dx+dy)*0.01*transY(1), transY(2));
					else
						models[n]->translate(transY(0), -(float)(dx+dy)*0.01*transY(1), transY(2));
				}
				if (selectedAxis == 3) //Z
				{
					Vector transZ = m*Vector(0.0, 0.0, 1.0, 1.0);
					if (90<zRot && zRot<270)
						models[n]->translate(transZ(0), transZ(1), (float)dx*0.01*transZ(2));
					else
						models[n]->translate(transZ(0), transZ(1), -(float)dx*0.01*transZ(2));
				}
			}
		}
		//search the lights
		n = -1;
		for (uint i=0; i<lights.size(); ++i)
		{
			if (lights[i]->getName() == selectedObject)
			{
				n = i;
				break;
			}
		}
		if (n!=-1)
		{
			if (event->buttons() & Qt::LeftButton) 
			{
				float vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
				glGetFloatv(GL_MODELVIEW_MATRIX, vals);	
				Matrix m(vals);
				if (selectedAxis == 1) //X
				{
					Vector transX = m*Vector(1.0, 0.0, 0.0, 1.0);
					lights[n]->translate((float)(dx+dy)*0.01*transX(0), transX(1), transX(2));
				}
				if (selectedAxis == 2) //Y
				{
					Vector transY = m*Vector(0.0, 1.0, 0.0, 1.0);
					lights[n]->translate(transY(0), -(float)(dx+dy)*0.01*transY(1), transY(2));
				}
				if (selectedAxis == 3) //Z
				{
					Vector transZ = m*Vector(0.0, 0.0, 1.0, 1.0);
					lights[n]->translate(transZ(0), transZ(1), -(float)dx*0.01*transZ(2));
				}
			}
		}
		
	}
	lastPos = event->pos();
	updateGL();

}

void Scene::wheelEvent(QWheelEvent *event)
{
	zoom += event->delta()*0.005;
	updateGL();
}

void Scene::keyPressEvent(QKeyEvent *event)
{
	
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
	mousepressed = false;
}

void Scene::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}

void Scene::setXRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != xRot) 
	{
		xRot = angle;
		//updateGL();
	}
}

void Scene::setYRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != yRot) 
	{
		yRot = angle;
		//updateGL();
	}
}

void Scene::setZRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != zRot) 
	{
		zRot = angle;
		//updateGL();
	}
}

void Scene::setTransformations()
{
	glLoadIdentity();
	glTranslatef(transx,transy, zoom);
	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);

}

Vector Scene::getCameraPosition()
{
	GLdouble mdl[16];
	Vector cam;
	setTransformations();
	glGetDoublev(GL_MODELVIEW_MATRIX, mdl);
	cam(0) = -(mdl[0] * mdl[12] + mdl[1] * mdl[13] + mdl[2] * mdl[14]);
	cam(1) = -(mdl[4] * mdl[12] + mdl[5] * mdl[13] + mdl[6] * mdl[14]);
	cam(2) = -(mdl[8] * mdl[12] + mdl[9] * mdl[13] + mdl[10] * mdl[14]);
	return cam;
}

Vector Scene::getViewDirection()
{
	GLdouble mdl[16];	
	setTransformations();
	glGetDoublev(GL_MODELVIEW_MATRIX, mdl);
	return Vector (mdl[8], mdl[9], -mdl[10]);
}

Vector Scene::getUpVector()
{
	GLdouble mdl[16];	
	setTransformations();
	glGetDoublev(GL_MODELVIEW_MATRIX, mdl);
	return Vector (mdl[1], mdl[5], mdl[9]);
}


void Scene::scaleObject(double sx, double sy, double sz)
{
	if (selectedObject<10)
		return;

	int index=-1;
	for (int i=0;i<(int)models.size();++i)
	{
		if (models[i]->getName()==selectedObject)
		{
			index=i;
			i=models.size(); //for statement can be exited
		}
	}
	if (index!=-1)
		models[index]->scale(sx,sy,sz);
	
	updateGL();
}

void Scene::translateObject(double dx, double dy, double dz)
{
	if (selectedObject<10)
		return;

	int index=-1;
	for (int i=0;i<(int)models.size();++i)
	{
		if (models[i]->getName()==selectedObject)
		{
			index = i;
			continue; //for statement can be exited
		}
	}
	if (index != -1)
		models[index]->translate(dx,dy,dz);

	//the lights
	index=-1;
	for (int i=0;i<(int)lights.size();++i)
	{
		if (lights[i]->getName() == selectedObject)
		{
			index = i;
			continue; //for statement can be exited
		}
	}
	if (index != -1)
		lights[index]->translate(dx,dy,dz);
	
	updateGL();
}

void Scene::rotateObject(double ax, double ay, double az, double angle)
{
	if (selectedObject<10)
		return;

	int index = -1;
	for (int i=0;i<(int)models.size();++i)
	{
		if (models[i]->getName()==selectedObject)
		{
			index = i;
			continue; //for statement can be exited
		}
	}
	if (index != -1)
		models[index]->rotate(Vector(ax,ay,az), angle);
		
	updateGL();
}

void Scene::addLight()
{
	Light *l = new Light(nameCount);
	++nameCount;
	LightDialog ld(l);
	if (ld.exec())
	{		
		lights.push_back(l);
		updateGL();
	}
}

void Scene::deleteObject()
{
	if (selectedObject<10)
		return;

	int index = -1;
	//models
	for (int i=0;i<(int)models.size();++i)
	{
		if (models[i]->getName() == selectedObject)
		{
			index = i;
			i = models.size(); //for statement can be exited
		}
	}
	if (index!=-1)
	{
		models[index]->~Model();
		models[index] = NULL;
		vector<Model*>::iterator it = models.begin();
		models.erase(it+index);
		return;
	}
	//or is it a light
	index =- 1;
	for (int i=0;i<(int)lights.size();++i)
	{
		if (lights[i]->getName()==selectedObject)
		{
			index=i;
			i=lights.size(); //for statement can be exited
		}
	}
	if (index!=-1)
	{
		lights[index]->~Light();
		lights[index] = NULL;
		vector<Light*>::iterator it = lights.begin();
		lights.erase(it+index);
		return;
	}
}


bool Scene::readOBJFile(QString fileName)
{
	ifstream file;
  	file.open(fileName.toStdString().c_str());
	
	if (!file)
		return false;

	vector<Vector> vectors;
	vector<Face> faces;
	vector<Vector> normals;
	vector<Mesh> meshes;
	vector<Material> materials;
	vector<Vector> tex_coords;
	vector<Texture> textures;
	while (!file.eof())
	{
		string s;
		file>>s;
		//materials
		if (s.compare("mtllib") == 0)
		{
			string m_fn;
			file>>m_fn;
			QString path; //path in were the
			path = fileName;
			path.chop(fileName.length()-fileName.lastIndexOf("/"));
			path.append(QString("/%1").arg(QString(m_fn.c_str())));
			readMTLFile(path, &materials, &textures);
		}
		//vertex
		if (s.compare("v") == 0)
		{
			float vx,vy,vz;
			file>>vx>>vy>>vz;
			vectors.push_back(Vector(vx,vy,vz));
		}
		//tex coords
		if (s.compare("vt") == 0)
		{
			float u,v;
			file>>u>>v;
			tex_coords.push_back(Vector(u,v));
		}
		//normals
		if (s.compare("vn") == 0)
		{
			float vx,vy,vz;
			file>>vx>>vy>>vz;
			normals.push_back(Vector(vx,vy,vz));
		}
		//Mesh - characterized by the same material
		if (s.compare("usemtl") == 0)
		{
			string matName;
			file>>matName;
			//look what index should be used
			Mesh m;
			int index=0;
			for (uint i=1;i<materials.size();++i)
			{
				if (materials[i].name.compare(matName)==0)
					index=i;
			}
			m.material = index;
			
			meshes.push_back(m);
		}
		//face (int our case: TRIANGLES)
		if (s.compare("f")==0)
		{
			string v1,v2,v3;
			//the programm assumes we only read triangles! if not then holes will occur
			file>>v1>>v2>>v3;
			//decompose the string of the form v/vt/vn
			QString str1(v1.c_str());
			QString str2(v2.c_str());
			QString str3(v3.c_str());
			QStringList list1 = str1.split("/");
			QStringList list2 = str2.split("/");
			QStringList list3 = str3.split("/");
			if (list1.size()>0 && list2.size()>0 && list3.size()>0)
			{
				Face f;
				//save the vertices
				f.vectors.push_back(list1[0].toInt()-1);
				f.vectors.push_back(list2[0].toInt()-1);
				f.vectors.push_back(list3[0].toInt()-1);
				//save the tex_coords TODO: check if it is necessary to save them
				if (list1.size()<3 || list2.size()<3 || list3.size()<3)
				{
					f.normals.push_back(list1[1].toInt()-1);
					f.normals.push_back(list2[1].toInt()-1);
					f.normals.push_back(list3[1].toInt()-1);
				}
				else
				{
					f.tex_coords.push_back(list1[1].toInt()-1);
					f.tex_coords.push_back(list2[1].toInt()-1);
					f.tex_coords.push_back(list3[1].toInt()-1);
					f.normals.push_back(list1[2].toInt()-1);
					f.normals.push_back(list2[2].toInt()-1);
					f.normals.push_back(list3[2].toInt()-1);
				}
				faces.push_back(f);
				meshes.back().faces.push_back(faces.size()-1);
			}
		}
	}

	//give at least on (grey) standard material
	if (materials.empty())
	{
		cout<<"No Materials found creating dummy...\n";
		Material m;
		m.name = string("dummy");
		//for consistency: init the other values
		m.ambient[0] = 0.2;
		m.ambient[1] = 0.2;
		m.ambient[2] = 0.2;
		m.ambient[3] = 1.0;
		m.diffuse[0] = 0.6;
		m.diffuse[1] = 0.6;
		m.diffuse[2] = 0.6;
		m.diffuse[3] = 1.0;
		m.specular[0] = 1.0;
		m.specular[1] = 1.0;
		m.specular[2] = 1.0;
		m.specular[3] = 1.0;
		m.shininess = 100.0;
		m.alpha = 1.0;
		m.density = 1.0;
		m.isTexture = false;
		materials.push_back(m);
	}
	//a sanity check (can happen that the model is not exported correctly)
	bool hasTexture = false;
	for (unsigned int i=0;i<materials.size();++i)
	{
		if (materials[i].isTexture)
			hasTexture = true;
	}
	if (hasTexture && tex_coords.empty())
	{
		QMessageBox msgBox;
		msgBox.setText("Warning! Model has Texture(s) but no Texture Coordinates.");
		msgBox.setInformativeText("Proceed? (will most likely result in a crash)");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Cancel)
			return false;
	}
	Model *m = new Model(nameCount, vectors, faces, normals, meshes, materials, tex_coords, textures);
	models.push_back(m);
	++nameCount;
	updateGL();
	cout<<"New Model: \n";
	cout<<materials.size()<<" Materials "<<meshes.size()<<" Meshes "<<vectors.size()<<" Vertices, "<<faces.size()<<" Faces "<<normals.size()<<" Normals "<<tex_coords.size()<<" TexCoords\n";
	int oldIndex = selectedObject;
	selectedObject = nameCount-1;
	rotateObject( 1.f, 0.f, 0.f, -90.0 );
	selectedObject = oldIndex;
	return true;
}

void Scene::readMTLFile(QString fileName, vector <Material> *materials, vector<Texture> *textures)
{
	//vector <Material> materials;
	ifstream file;
  	file.open(fileName.toStdString().c_str());
	if (!file)
		return;
	while (!file.eof())
	{
		string s;
		file>>s;
		//create a new material
		if (s.compare("newmtl")==0)
		{
			string mtlName;
			file>>mtlName;
			Material m;
			m.name = mtlName;
			//for consistency: init the other values
			m.ambient[0] = 0.5;
			m.ambient[1] = 0.5;
			m.ambient[2] = 0.5;
			m.ambient[3] = 1.0;
			m.diffuse[0] = 0.6;
			m.diffuse[1] = 0.6;
			m.diffuse[2] = 0.6;
			m.diffuse[3] = 1.0;
			m.specular[0] = 1.0;
			m.specular[1] = 1.0;
			m.specular[2] = 1.0;
			m.specular[3] = 1.0;
			m.shininess = 20.0;
			m.alpha = 1.0;
			m.sharpness = 0.0;
			m.density = 1.0;
			m.isTexture = false;
			materials->push_back(m);
		}
		if (s.compare("Ns")==0)
		{
			float ns;
			file>>ns;
			if (ns>128.0)
				ns=128.0;
			materials->back().shininess = ns;
		}
		if (s.compare("Ni")==0)
		{
			float ni;
			file>>ni;
			materials->back().density = ni;
		}
		if (s.compare("Ka")==0)
		{
			float x,y,z;
			file>>x>>y>>z;
			materials->back().ambient[0] = x;
			materials->back().ambient[1] = y;
			materials->back().ambient[2] = z;
			materials->back().ambient[3] = 1.0;
		}
		if (s.compare("Kd")==0)
		{
			float x,y,z;
			file>>x>>y>>z;
			materials->back().diffuse[0] = x;
			materials->back().diffuse[1] = y;
			materials->back().diffuse[2] = z;
			materials->back().diffuse[3] = 1.0;
		}
		if (s.compare("Ks")==0)
		{
			float x,y,z;
			file>>x>>y>>z;
			materials->back().specular[0] = x;
			materials->back().specular[1] = y;
			materials->back().specular[2] = z;
			materials->back().specular[3] = 1.0;
		}
		if (s.compare("d")==0)
		{
			float d;
			file>>d;
			materials->back().alpha = d;
		}
		if (s.compare("sharpness")==0)
		{
			float s;
			file>>s;
			materials->back().sharpness = s/1000.0; //obj defines sharpness from 0 - 1000 but we need it from 0.0 to 1.0
		}
		
		//TODO: Textures are not completed
		//diffuse and ambient maps are treated the same way
		if (s.compare("map_Kd")==0 || s.compare("map_Ka")==0)
		{
			string tex_name;
			file>>tex_name;
			QImage *texture=NULL;
			QString path; //path in were the
			path = fileName;
			path.chop(fileName.length()-fileName.lastIndexOf("/"));
			path.append(QString("/%1").arg(QString(tex_name.c_str())));
			texture=new QImage(QString(path));
			if(!texture->isNull())
			{
				QImage texImage=QGLWidget::convertToGLFormat(*texture);
				Texture t;
				GLuint tex;
				glGenTextures( 1, &tex );
				glBindTexture( GL_TEXTURE_2D, tex );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
				glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );  //DECAL
				if (texImage.hasAlphaChannel())
					glTexImage2D(GL_TEXTURE_2D, 0, 4, texImage.width(), texImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage.bits());
				else
					glTexImage2D(GL_TEXTURE_2D, 0, 4, texImage.width(), texImage.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, texImage.bits());
				materials->back().isTexture=true;
				t.name = tex_name;
				t.texID=tex;
				t.texture = texImage;
				textures->push_back(t);
				materials->back().tex_id=textures->size()-1;
			}
			//else
			//	QMessageBox::warning(this, tr("Texture Loader"), QString("Texture %1\ncouldn't be loaded!").arg(path),QMessageBox::Ok);	
			texture->~QImage();
			texture=NULL;
		}
	}
}


/*void Scene::setUseShaders(bool s)
{
	if (s && shadersAvaiable)
		useShaders=true;
	else
		useShaders=false;
}*/

void Scene::setCullingMode(bool enable)
{
	if (enable)
	{
		//glCullMode(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	else
		glDisable(GL_CULL_FACE);
	updateGL();
}

void Scene::saveScene(QString path, Parameters p)
{
	//create File
	ofstream file(path.toStdString().c_str());
		
	//1st: write Header (nMat, nVert, nNorm, nTexCoords, nFaces)
	size_t nLights = lights.size(), nMat =0, nVert=0, nNorm=0, nTexCoords=0, nFaces=0;
	for (size_t i=0;i<models.size();++i)
	{
		nMat+=models[i]->materials.size();
		nVert+=models[i]->vectors.size();
		nNorm+=models[i]->normals.size();
		nTexCoords+=models[i]->tex_coords.size();
		nFaces+=models[i]->faces.size();
	}	
	file<<nLights<<" "<<nMat<<" "<<nVert<<" "<<nNorm<<" "<<nTexCoords<<" "<<nFaces<<endl;
	file<<endl;

	//1.5 : the properties for the raytracer
	file<<p.width<<" "<<p.height<<endl;
	file<<p.eyePoint(0)<<" "<<p.eyePoint(1)<<" "<<p.eyePoint(2)<<endl;
	file<<p.viewDirection(0)<<" "<<p.viewDirection(1)<<" "<<p.viewDirection(2)<<endl;
	file<<p.focalLength<<endl;
	file<<p.upVector(0)<<" "<<p.upVector(1)<<" "<<p.upVector(2)<<endl;
	file<<p.back_r<<" "<<p.back_g<<" "<<p.back_b<<endl;
	file<<p.back_brigthness_r<<" "<<p.back_brigthness_g<<" "<<p.back_brigthness_b<<endl;
	file<<endl;
	//1.75 ALL LIGHTS (amb,spec,diff, att)
	for (size_t i=0;i<lights.size();++i)
	{
		Vector center = lights[i]->getTransformations()*Vector(0,0,0);
		file<<center(0)<<" "<<center(1)<<" "<<center(2)<<"      ";
		file<<lights[i]->getAmbient()[0]<<" "<<lights[i]->getAmbient()[1]<<" "<<lights[i]->getAmbient()[2]<<"  ";
		file<<lights[i]->getDiffuse()[0]<<" "<<lights[i]->getDiffuse()[1]<<" "<<lights[i]->getDiffuse()[2]<<"  ";
		file<<lights[i]->getSpecular()[0]<<" "<<lights[i]->getSpecular()[1]<<" "<<lights[i]->getSpecular()[2]<<"      ";
		for (unsigned int j=0; j<3; ++j)
		{
			if (fabs(lights[i]->getAttenuation()[j])<1e-5)
				file<<"0 ";
			else
				file<<lights[i]->getAttenuation()[j]<<" ";
		}
		file<<"\n";
		//file<<lights[i]->getAttenuation()[0]<<" "<<lights[i]->getAttenuation()[1]<<" "<<lights[i]->getAttenuation()[2]<<"\n";
	}
	file<<endl;
	//2nd List of all Materials (amb,diff,spec,shininess,alpha,density, isTexture, texturepath)
	for (size_t i=0;i<models.size();++i)
	{
		for (uint j=0;j<models[i]->materials.size();++j)
		{
			Material m = models[i]->materials[j];
			file<<m.ambient[0]<<" "<<m.ambient[1]<<" "<<m.ambient[2]<<" ";
			file<<m.diffuse[0]<<" "<<m.diffuse[1]<<" "<<m.diffuse[2]<<" ";
			file<<m.specular[0]<<" "<<m.specular[1]<<" "<<m.specular[2]<<" ";
			file<<m.shininess<<" "<<m.alpha<<" "<<m.sharpness<<" "<<m.density<<" ";
			if (m.isTexture)
			{
				file<<"1 "<<models[i]->textures[m.tex_id].name<<endl;
				//copy textures in the path
				QString texpath = path;
				texpath.chop(path.length()-path.lastIndexOf("/"));
				texpath.append(QString("/%1").arg(models[i]->textures[m.tex_id].name.c_str()));
				cout<<texpath.toStdString()<<endl;
				//the image is saved wrong -> convert
				QImage tempImage = models[i]->textures[m.tex_id].texture.mirrored();
				tempImage = tempImage.rgbSwapped();
				if (!tempImage.save(texpath))
					QMessageBox::warning(this, tr("Save Image"), tr("Couldn't save image.\nTry to copy it manually to the destination path"),QMessageBox::Ok);					
			}
			else
				file<<"0"<<endl;			
		}
	}
	file<<endl;
	//3rd: List of vertices
	for (size_t i=0;i<models.size();++i)
	{
		for (uint j=0;j<models[i]->vectors.size();++j)
		{
			Vector v = models[i]->vectors[j];
			v = models[i]->trafoMatrix*v; //apply the transformations
			for (uint k=0;k<3;++k)
				if ( fabs(v(k))<0.0001 ) 
					v(k) = 0.0;
			file<<v(0)<<" "<<v(1)<<" "<<v(2)<<endl;
		}
	}
	file<<endl;
	//4th: List of Normals
	for (size_t i=0;i<models.size();++i)
		{
		for (size_t j=0;j<models[i]->normals.size();++j)
		{
			Vector v = models[i]->normals[j];
			//v = models[i]->trafoMatrix*v; //apply the transformations
			//v = models[i]->rotateMatrix*models[i]->scaleMatrix.GenerateInverseMatrix4f()*models[i]->translateMatrix*v;
			v = models[i]->rotateMatrix*v;
			v.normalize();
			for (uint k=0;k<3;++k)
				if ( fabs(v(k))<0.0001 ) 
					v(k) = 0.0;
			file<<v(0)<<" "<<v(1)<<" "<<v(2)<<endl;
		}
	}
	file<<endl;
	//5th: Texture Coords
	for (size_t i=0;i<models.size();++i)
	{
		for (size_t j=0;j<models[i]->tex_coords.size();++j)
		{
			Vector t = models[i]->tex_coords[j];
			for (size_t k=0;k<2;++k)
				if ( fabs(t(k))<0.0001 ) 
					t(k) = 0.0;
			file<<t(0)<<" "<<t(1)<<endl;
		}
	}
	file<<endl;
	//6th: the faces
	//remark: if there are more than one model we have to calculate the index correctly
	//face : ( matNr, VertNr*3, NormNr*3, TexCoordNr*3 (-1 if no texture) )
	for (size_t i=0;i<models.size();++i)
	{
		for (size_t j=0;j<models[i]->meshes.size();++j)
		{
			//get Material for mesh
			int matNr = models[i]->meshes[j].material;
			for (uint k=0;k<i;++k)
				matNr += models[k]->materials.size();
			//loop through all faces
			for (size_t k=0;k<models[i]->meshes[j].faces.size();++k)
			{
				Face f = models[i]->faces[models[i]->meshes[j].faces[k]];
				file<<matNr<<" ";
				//vertices
				for (size_t l=0;l<3;++l) //the f.vectors.size() must be 3 - since we're dealing with triangles
				{
					int nV = f.vectors[l];
					for (uint m=0;m<i;++m)
						nV += models[m]->vectors.size();
					file<<nV<<" ";
				}
				//normals
				for (size_t l=0;l<3;++l) //the f.vectors.size() must be 3 - since we're dealing with triangles
				{
					int nV = f.normals[l];
					for (uint m=0;m<i;++m)
						nV += models[m]->normals.size();
					file<<nV<<" ";
				}
				//texcoords
				for (size_t l=0;l<3;++l) //the f.vectors.size() must be 3 - since we're dealing with triangles
				{
					if (models[i]->materials[models[i]->meshes[j].material].isTexture)
					{
						int nV = f.tex_coords[l];
						for (uint m=0;m<i;++m)
							nV += models[m]->tex_coords.size();
						file<<nV<<" ";
					}
					else
						file<<"-1";
				}
				file<<endl;
			}
			
		}
	}
	file.close();
}

void Scene::saveAsPrimitive(QString path)
{
	//dialog to ask for the parameters for the raytracer
	Parameters p;
	p.eyePoint = getCameraPosition();
	p.viewDirection = getViewDirection();
	p.upVector = getUpVector();
 	SaveDialog sd(&p);
	if( sd.exec() )
	{
		saveScene(path, p);
	}
	
}

void Scene::loadPrimitive(QString path)
{
	vector<Vector> vectors;
	vector<Face> faces;
	vector<Vector> normals;
	vector<Mesh> meshes;
	vector<Material> materials;
	vector<Vector> tex_coords;
	vector<Texture> textures;

	size_t nLights = 0, nMat = 0, nVert = 0, nNorm = 0, nTexCoords = 0, nFaces = 0;

	//QString path("scene.tri");
	//create File
	ifstream file(path.toStdString().c_str());

	file>>nLights>>nMat>>nVert>>nNorm>>nTexCoords>>nFaces;	//read Header

	//0.5 read Raytracer-Properties
	Parameters p;
	file>>p.width;file>>p.height;
	file>>p.eyePoint(0); file>>p.eyePoint(1); file>>p.eyePoint(2);
	file>>p.viewDirection(0); file>>p.viewDirection(1); file>>p.viewDirection(2);
	file>>p.focalLength;
	file>>p.upVector(0); file>>p.upVector(1); file>>p.upVector(2);
	file>>p.back_r; file>>p.back_g; file>>p.back_b;
	file>>p.back_brigthness_r; file>>p.back_brigthness_g; file>>p.back_brigthness_b;
	
	//0.75 read the lights
	for (size_t i=0;i<nLights;++i)
	{
		Light *l = new Light(nameCount);
		++nameCount;
		float x,y,z;
		float amb_r,amb_g,amb_b;
		float diff_r,diff_g,diff_b;
		float spec_r,spec_g,spec_b;
		float constAtt, linAtt, quadAtt;
		file>>x>>y>>z;
		file>>amb_r>>amb_g>>amb_b;
		file>>diff_r>>diff_g>>diff_b;
		file>>spec_r>>spec_g>>spec_b;
		file>>constAtt>>linAtt>>quadAtt;
		l->setAmbient(amb_r,amb_g,amb_b);
		l->setDiffuse(diff_r,diff_g,diff_b);
		l->setSpecular(spec_r,spec_g,spec_b);
		l->setAttenuation(constAtt, linAtt, quadAtt);
		l->translate(x,y,z);
		lights.push_back(l);		
	}

	//1. Materials->Meshes
	for (size_t i=0;i<nMat;++i)
	{
		Material mat;
		float r,g,b,shininess,alpha,sharpness,density;
		int isTexture;
		file>>r>>g>>b;
		mat.ambient[0]=r; mat.ambient[1]=g; mat.ambient[2]=b; mat.ambient[3]=1.0;
		file>>r>>g>>b;
		mat.diffuse[0]=r; mat.diffuse[1]=g; mat.diffuse[2]=b; mat.diffuse[3]=1.0;
		file>>r>>g>>b;
		mat.specular[0]=r; mat.specular[1]=g; mat.specular[2]=b; mat.specular[3]=1.0;
		file>>shininess;
		mat.shininess = shininess;
		file>>alpha;
		mat.alpha=alpha;
		file>>sharpness;
		mat.sharpness=sharpness;
		file>>density;
		mat.density=density;
		file>>isTexture;
		mat.isTexture=false;
		if (isTexture == 1) //load texture
		{
			string texName;
			file>>texName;
			cout<<"Texture: "<<texName<<endl;
			QString filepath; //path in were the
			filepath = path;
			filepath.chop(path.length()-path.lastIndexOf("/"));
			filepath.append(QString("/%1").arg(QString(texName.c_str())));
			QImage texture(filepath);
			if (texture.isNull()) //try the "textures" sub directory
			{
				filepath = path;
				filepath.chop(path.length()-path.lastIndexOf("/"));
				filepath.append(QString("/textures/%1").arg(QString(texName.c_str())));
				//cout<<".....failed: try Texture: "<<filepath.toStdString()<<endl;
				texture = QImage(filepath);
			}
			if(!texture.isNull())
			{
				QImage texImage=QGLWidget::convertToGLFormat(texture);
				Texture t;
				GLuint tex;
				glGenTextures( 1, &tex );
				glBindTexture( GL_TEXTURE_2D, tex );
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
				glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );  //DECAL
				if (texImage.hasAlphaChannel())
					glTexImage2D(GL_TEXTURE_2D, 0, 4, texImage.width(), texImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage.bits());
				else
					glTexImage2D(GL_TEXTURE_2D, 0, 4, texImage.width(), texImage.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, texImage.bits());
				mat.isTexture=true;
				t.name = mat.name = texName;
				t.texID=tex;
				t.texture = texImage;
				textures.push_back(t);
				mat.tex_id=textures.size()-1;
			}			
		}
		materials.push_back(mat);
		Mesh mesh;
		mesh.material = i;//materials.size()-1;
		meshes.push_back(mesh);
	}
	//2.Fill vertices
	for (size_t i=0;i<nVert;++i)
	{
		float x,y,z;
		file>>x>>y>>z;
		vectors.push_back(Vector(x,y,z));
	}
	//3.Fill normals
	for (size_t i=0;i<nNorm;++i)
	{
		float x,y,z;
		file>>x>>y>>z;
		Vector n = Vector(x,y,z);
		n.normalize();
		normals.push_back(n);
	}
	//3.Fill texCoords
	for (size_t i=0;i<nTexCoords;++i)
	{
		float u,v;
		file>>u>>v;
		tex_coords.push_back(Vector(u,v));
	}
	//4.Fill faces /Triangles
	for (size_t i=0;i<nFaces;++i)
	{
		int matNr,vertNr1,vertNr2,vertNr3,NormNr1,NormNr2,NormNr3,TexCoordsNr1,TexCoordsNr2,TexCoordsNr3;
		file>>matNr>>vertNr1>>vertNr2>>vertNr3>>NormNr1>>NormNr2>>NormNr3>>TexCoordsNr1>>TexCoordsNr2>>TexCoordsNr3;
		Face f;
		f.vectors.push_back(vertNr1);
		f.vectors.push_back(vertNr2);
		f.vectors.push_back(vertNr3);
		f.normals.push_back(NormNr1);
		f.normals.push_back(NormNr2);
		f.normals.push_back(NormNr3);
		f.tex_coords.push_back(TexCoordsNr1);
		f.tex_coords.push_back(TexCoordsNr2);
		f.tex_coords.push_back(TexCoordsNr3);
		faces.push_back(f);
		meshes[matNr].faces.push_back(i);
	}


	Model *m = new Model(nameCount, vectors, faces, normals, meshes, materials, tex_coords, textures);
	models.push_back(m);
	++nameCount;
	cout<<"New Model: \n";
	cout<<materials.size()<<" Materials "<<meshes.size()<<" Meshes "<<vectors.size()<<" Vertices, "<<faces.size()<<" Faces "<<normals.size()<<" Normals\n";
	
	//gluLookAt(p.eyePoint(0), p.eyePoint(1), p.eyePoint(2), p.viewDirection(0), p.viewDirection(1), p.viewDirection(2), p.upVector(0), p.upVector(1), p.upVector(2));
	
	updateGL();	
}

void Scene::drawEnvironment()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	
	glPushMatrix();
	glLoadIdentity();
	setTransformations();
	//daw grid	
	glBegin(GL_LINES);
	for (int i=-100;i<100;++i)
	{	
		if (i==0)
			glColor3f(0.0,0.0,1.0);
		else
			glColor3f(0.8,0.8,0.8);
		glVertex3f(i,0.0,-100.0);
		glVertex3f(i,0.0,100.0);
	}
	for (int i=-100;i<100;++i)
	{	
		if (i==0)
			glColor3f(1.0,0.0,0.0);
		else
			glColor3f(0.8,0.8,0.8);
		glVertex3f(-100.0,0.0,i);
		glVertex3f(100.0,0.0,i);
	}
	glEnd();	
	glPopMatrix();	

	if (selectedObject != -1) //an object was selected -> draw the translation arrows
	{
		
		//find object
		int n = -1;
		Vector center;
		for (size_t i=0; i<models.size(); ++i)
		{
			if (models[i]->getName() == selectedObject)
			{
				n=i;
				center = models[n]->getCenter();
				break;
			}
		}
		if (n == -1) //find light
			for (size_t i=0; i<lights.size(); ++i)
			{
				if (lights[i]->getName() == selectedObject)
				{
					n=i;
					Matrix m = lights[n]->getTransformations();
					center = Vector(m[12], m[13], m[14]);
					break;
				}
			}
		if (n == -1) //an axis was selected or something
		{
			glEnable(GL_LIGHTING);
			return;
		}

		glPushMatrix();

		setTransformations();
				
		GLdouble projection[16];
		GLdouble modelview[16];
		GLint viewport[4];
		GLdouble screen_coords[3];

		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetIntegerv(GL_VIEWPORT,viewport);

		float cx = center[0];
		float cy = center[1];
		float cz = center[2];

		//project object center to screen coordinates
		gluProject(cx, cy, cz, modelview, projection, viewport, screen_coords, screen_coords+1 , screen_coords+2);

		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		
		//x-Axis
		glLoadIdentity();
		glOrtho(0, width, 0, height, -100, 100);
		glTranslatef(screen_coords[0], screen_coords[1], 0.0);
		glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
		glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
		glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
		glRotated(90, 0.0, 1.0, 0.0);
		glPushName(1);
		glColor3f(1.0, 0.0, 0.0);
		gluCylinder(xCyl , 6 , 0 , 35 , 20 , 20 );
		glPopName();

		//y-Axis
		glLoadIdentity();
		glOrtho(0, width, 0, height, -100, 100);
		glTranslatef(screen_coords[0], screen_coords[1], 0.0);		
		glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
		glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
		glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
		glRotated(270, 1.0, 0.0, 0.0);		
		glPushName(2);
		glColor3f(0.0, 1.0, 0.0);
		gluCylinder(xCyl , 6 , 0 , 35 , 20 , 20 );
		glPopName();

		//z-Axis
		glLoadIdentity();
		glOrtho(0, width, 0, height, -100, 100);
		glTranslatef(screen_coords[0], screen_coords[1], 0.0);
		glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
		glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
		glRotated(zRot / 16.0, 0.0, 0.0, 1.0);		
		glPushName(3);
		glColor3f(0.0, 0.0, 1.0);
		gluCylinder(xCyl , 6 , 0 , 35 , 20 , 20 );
		glPopName();

		//reset Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0);
		glMatrixMode(GL_MODELVIEW);
		

		glPopMatrix();
	}
	glEnable(GL_LIGHTING);

}

void Scene::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glPushMatrix();
	
	drawEnvironment();
	
	setTransformations();

	//standard light
	glPushMatrix();
	glLoadIdentity();
	GLfloat position[] = { -3.0f, +10.0f, 20.0f, 1.0f };
	float ambient[] = {0.7,0.7,0.7,1.0};
	float diffuse[] = {0.9,0.9,0.9,1.0};
	float specular[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glPopMatrix();

	for (uint i=0; i<lights.size(); ++i)
	{
		glPushName(lights[i]->getName());
		lights[i]->draw(selectedObject);
		glPopName();
	}	

	//enable the lights
	//but first reset them
	//float black[] = {0.0,0.0,0.0,0.0};
	if (!lights.empty()) //delete only if there is at least one light set by the user
	{
		for (uint i=0;i<8;++i)
		{
			glDisable(GL_LIGHT0+i);
		}
	}
	for (uint i=0;i<lights.size();++i)
	{
		if (i<8)
		{
			glEnable(GL_LIGHT0+i);
			glLightfv(GL_LIGHT0+i, GL_AMBIENT, lights[i]->getAmbient());
			glLightfv(GL_LIGHT0+i, GL_DIFFUSE, lights[i]->getDiffuse());
			glLightfv(GL_LIGHT0+i, GL_SPECULAR, lights[i]->getSpecular());
			glLightfv(GL_LIGHT0+i, GL_POSITION, (lights[i]->getTransformations()*Vector(0,0,0)).getValues());
		}
	}
			
	for (uint i=0; i<models.size(); ++i)
	{
		glPushName(models[i]->getName());
		models[i]->draw(selectedObject);
		glPopName();
	}
	
	glPopMatrix();

}


