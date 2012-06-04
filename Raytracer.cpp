#include "Raytracer.h"
#include <fstream>
#include <omp.h>

#include <iostream>
#include <QShortcut>
using namespace std;

Raytracer::Raytracer( QString path ) {
	QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Q), this);
	QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(close()));

	superSamplingRate = 1; //TODO: setting this to 1 and enabling on the fly output will cause a crash
	//read file and init everything

	vector<Vector> vectors;
	vector<Vector> normals;
	vector<Material> materials;
	vector<Vector> tex_coords;

	int nLights = 0, nMat =0, nVert=0, nNorm=0, nTexCoords=0, nFaces=0;

	//QString path("scene.tri");
	//create File
	ifstream file(path.toStdString().c_str());

	file>>nLights>>nMat>>nVert>>nNorm>>nTexCoords>>nFaces;	//read Header

	//0.5 read Raytracer-Properties
	int width,height;
	float tx,ty,tz;
	file>>width;file>>height;
	file>>tx; file>>ty; file>>tz;
	camera = Vector(tx,ty,tz);
	file>>tx; file>>ty;file>>tz;
	center = Vector(tx,ty,tz);
	file>>focalLength;
	float ux, uy, uz;
	file>>ux>>uy>>uz;
	upVector = Vector(ux,uy,uz);
	//file>>rotationAngle;
	float back_r,back_g,back_b;
	file>>back_r>>back_g>>back_b;
	backgroundColor.setRgb(back_r*255,back_g*255,back_b*255);
	float amb_r,amb_g,amb_b;
	file>>amb_r>>amb_g>>amb_b;
	ambientLight.setRgb(amb_r*255,amb_g*255,amb_b*255);

	image = new QImage(width*superSamplingRate, height*superSamplingRate, QImage::Format_RGB32);
	image->fill(qRgb(255,255,255));

	//0.75 read the lights
	for (int i=0;i<nLights;++i) {
		Lightsource l;
		file>>tx>>ty>>tz;
		l.position = Vector(tx,ty,tz);
		file>>l.ambient[0]>>l.ambient[1]>>l.ambient[2];
		file>>l.diffuse[0]>>l.diffuse[1]>>l.diffuse[2];
		file>>l.specular[0]>>l.specular[1]>>l.specular[2];
		file>>l.constAtt>>l.linAtt>>l.quadAtt;
		lights.push_back(l);
	}

	//1. Materials->Meshes
	for ( int i = 0; i < nMat; ++i ) {
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
		mat.isTexture=false;
		file>>isTexture;
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
			if(!texture.isNull())
			{
				mat.texture = texture;
				mat.isTexture = true;
			}
			else
				QMessageBox::warning(this, tr("Texture Loader"), tr("Texture couldn't be loaded!"), QMessageBox::Ok);
		}
		materials.push_back(mat);
	}
	//2.Fill vertices
	for (int i=0;i<nVert;++i)
	{
		float x,y,z;
		file>>x>>y>>z;
		vectors.push_back(Vector(x,y,z));
	}
	//3.Fill normals
	for (int i=0;i<nNorm;++i)
	{
		float x,y,z;
		file>>x>>y>>z;
		Vector n(x,y,z);
		n.normalize();
		normals.push_back(n);
	}
	//3.Fill texCoords
	for (int i=0;i<nTexCoords;++i)
	{
		float u,v;
		file>>u>>v;
		tex_coords.push_back(Vector(u,v,1.0));
	}
	//4.Fill faces /Triangles
	float minx = FLT_MAX, miny = FLT_MAX, minz = FLT_MAX, maxx = FLT_MIN, maxy = FLT_MIN, maxz = FLT_MIN;
	for ( int i = 0; i < nFaces; ++i ) {
		int matNr,vertNr1,vertNr2,vertNr3,NormNr1,NormNr2,NormNr3,TexCoordsNr1,TexCoordsNr2,TexCoordsNr3;
		file>>matNr>>vertNr1>>vertNr2>>vertNr3>>NormNr1>>NormNr2>>NormNr3>>TexCoordsNr1>>TexCoordsNr2>>TexCoordsNr3;
		Triangle t;
		t.material = materials[matNr];
		t.vertices[0]=vectors[vertNr1];
		t.vertices[1]=vectors[vertNr2];
		t.vertices[2]=vectors[vertNr3];
		t.normals[0]=normals[NormNr1];
		t.normals[1]=normals[NormNr2];
		t.normals[2]=normals[NormNr3];
		t.normal = crossProduct(t.vertices[0]-t.vertices[1], t.vertices[0]-t.vertices[2]);
		t.normal.normalize();

		Vector b = t.vertices[1]-t.vertices[0];
		Vector c = t.vertices[2]-t.vertices[0];
		float d = (scalarProduct(c,c) * scalarProduct(b,b)) - (scalarProduct(c,b) * scalarProduct(b,c));

		t.ubeta = (b * (scalarProduct(c, c) / d)) - (c * (scalarProduct(c, b) / d));
		t.ugamma = (c * (scalarProduct(b, b) / d)) - (b * (scalarProduct(b, c) / d));
		t.kbeta = scalarProduct(-t.vertices[0], t.ubeta);
		t.kgamma = scalarProduct(-t.vertices[0], t.ugamma);

		//corner 1
		if ( minx > t.vertices[0][0] )
			minx = t.vertices[0][0];
		else if ( maxx < t.vertices[0][0] )
			maxx = t.vertices[0][0];
		if ( miny > t.vertices[0][1] )
			miny = t.vertices[0][1];
		else if ( maxy < t.vertices[0][1] )
			maxy = t.vertices[0][1];
		if ( minz > t.vertices[0][2] )
			minz = t.vertices[0][2];
		else if ( maxz < t.vertices[0][2] )
			maxz = t.vertices[0][2];

		//corner 2
		if ( minx > t.vertices[1][0] )
			minx = t.vertices[1][0];
		else if ( maxx < t.vertices[1][0] )
			maxx = t.vertices[1][0];
		if ( miny > t.vertices[1][1] )
			miny = t.vertices[1][1];
		else if ( maxy < t.vertices[1][1] )
			maxy = t.vertices[1][1];
		if ( minz > t.vertices[1][2] )
			minz = t.vertices[1][2];
		else if ( maxz < t.vertices[1][2] )
			maxz = t.vertices[1][2];

		//corner 3
		if ( minx > t.vertices[2][0] )
			minx = t.vertices[2][0];
		else if ( maxx < t.vertices[2][0] )
			maxx = t.vertices[2][0];
		if ( miny > t.vertices[2][1] )
			miny = t.vertices[2][1];
		else if ( maxy < t.vertices[2][1] )
			maxy = t.vertices[2][1];
		if ( minz > t.vertices[2][2] )
			minz = t.vertices[2][2];
		else if ( maxz < t.vertices[2][2] )
			maxz = t.vertices[2][2];

		if (materials[matNr].isTexture) {
			t.texCoords[0]=tex_coords[TexCoordsNr1];
			t.texCoords[1]=tex_coords[TexCoordsNr2];
			t.texCoords[2]=tex_coords[TexCoordsNr3];
		}

		triangles.push_back(t);
	}
	cout << "Got "<< triangles.size() << " Triangles\n";

	minx -= 0.1f;
	maxx += 0.1f;
	miny -= 0.1f;
	maxy += 0.1f;
	minz -= 0.1f;
	maxz += 0.1f;

	//octree
	cout << "Setting up octree.\n";
	octree = new Octree();
	QTime t;
	t.start();
	octree->build(&triangles, minx, miny, minz, maxx, maxy, maxz);
	cout<<"Time: "<<t.elapsed()/1000.0<<endl;
	cout << "Got " << octree->size() << " Voxels\n";
	cout << "Got " << lights.size() << " Lights\n";
}

void Raytracer::init()
{

	//draw the geometry into a texture and save the primary-Rays
	GLubyte *renderedImage = new GLubyte[image->height()*image->width()*4];

	//TODO: implement a rotation angle
	gluLookAt(camera[0], camera[1], camera[2], center[0], center[1], center[2], upVector[0], upVector[1], upVector[2]);
	setGeometry(0,0,1024,768);
	makeCurrent();
	GLenum err = glewInit();
	if (GLEW_OK != err)
		cout << "Error: glewInit() failed\n";
	else
		cout << "Succesfully initiated GLEW\n";


	//create DisplayList
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	for ( unsigned int i = 0; i < triangles.size(); ++i ) {
		//glUniform1fARB( indexPos, i );
		float r = (float)(i % 255);
		float g = (float)((i/255) % 255);
		float b = (float)(((i/255)/255) % 255);
		float a = (float)(((((i/255)/255))/255) % 255);
		glColor4f(r/255.0,g/255.0,b/255.0,a/255.0);
		glBegin(GL_TRIANGLES);
		glVertex3fv( triangles[i].vertices[0].getValues() );
		glVertex3fv( triangles[i].vertices[1].getValues() );
		glVertex3fv( triangles[i].vertices[2].getValues() );
		glEnd();
	}
	glEndList();


	glGenTextures(1, &screenTexID);
	glBindTexture(GL_TEXTURE_2D,screenTexID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, image->width(), image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	// create a renderbuffer object to store depth info
	GLuint rboId;
	glGenRenderbuffersEXT(1, &rboId);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rboId);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, image->width(), image->height());
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	//GLuint fboId;
	glGenFramebuffersEXT(1, &fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId);

	// attach the texture to FBO color attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, screenTexID, 0);
	// attach the renderbuffer to depth attachment point
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rboId);

	resizeGL(image->width(), image->height());

	paintGL();

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glBindTexture(GL_TEXTURE_2D, screenTexID);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)renderedImage);


	idx = new unsigned int[image->height()*image->width()];

	for (int i=0; i<image->height()*image->width()*4; i+=4)
		idx[i/4] = (int)renderedImage[i] + (int)(renderedImage[i+1])*255 + (int)(renderedImage[i+2])*255*255 + (int)(renderedImage[i+3])*255*255*255;

	delete renderedImage;

}

void Raytracer::resizeGL(int w, int h)
{
	// Reset the viewport
    glViewport(0, 0, w, h);
    // Reset the projection and modelview matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45.0,(GLfloat)w/(GLfloat)h,1.0f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Raytracer::initializeGL()
{
	glClearColor((float)backgroundColor.red()/255.0, (float)backgroundColor.green()/255.0, (float)backgroundColor.blue()/255.0, 1.0);
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	cout<<"Back_Color: "<<backgroundColor.red()/255.0<<", "<<(float)backgroundColor.green()/255.0<<", "<<(float)backgroundColor.blue()/255.0<<endl;
	cout<<"Ambient_Light: "<<ambientLight.red()/255.0<<", "<<(float)ambientLight.green()/255.0<<", "<<(float)ambientLight.blue()/255.0<<endl;

	glDepthFunc(GL_LEQUAL);							// Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);						// Enable Depth Testing
}


void Raytracer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glCallList(displayList);
}

void Raytracer::close() {
	setVisible(false);
}

void Raytracer::genImage()
{
	QTime t;
	t.start();

	init();

	int count = 0;

	unsigned int backgroundCode = backgroundColor.red() + backgroundColor.green()*255 + backgroundColor.blue()*255*255 + (unsigned int)((unsigned int)255*(unsigned int)255*(unsigned int)255*(unsigned int)255); //the alpha value of background is always set  to 1.0 (255)
	cout<<"Back_Code: "<<backgroundCode<<endl;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId);
	paintGL();
	GLdouble mvMatrix[16];
	GLdouble projMatrix[16];
	int viewPort[4];
	float* zValues = new float[image->height()*image->width()];
	glReadPixels( 0, 0, image->width(), image->height(), GL_DEPTH_COMPONENT, GL_FLOAT, zValues );
	glGetIntegerv(GL_VIEWPORT, viewPort);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projMatrix);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);

	QWidget *w = new QWidget(NULL);
	QLabel *label = new QLabel(w);
	label->setGeometry(0,0,image->width()/superSamplingRate, image->height()/superSamplingRate);
	w->resize(label->size());
	w->setWindowTitle(QString("Rendered image"));
	w->show();


//comment this line out to disable parallel computation - recommended for bug tracing
#pragma omp parallel for schedule(dynamic, 1)
	for (int j=0; j<image->height(); j+=1)
	{
		for (int i=0; i<image->width(); i+=1)
		{
			//unsigned int index = idx[j*image->width()+i];
			double dX=0.0, dY=0.0, dZ=0.0;
			gluUnProject( (float)i, (float)j, zValues[j*image->width()+i], mvMatrix, projMatrix, viewPort, &dX, &dY, &dZ );
			Vector intersection(dX, dY, dZ);
			Vector dir = intersection - camera;

			//!---------this is the call to the raytracing function------------!
			QColor c = raytrace(camera, dir, MAX_DEPTH);
			image->setPixel(i,image->height()-(j+1), QRgb(c.rgb()));

		}

		#pragma omp critical
		{
			++count;
			cout<<"\r----"<<(float)count/(float)image->height()*100.0<<"----";
		}

		#pragma omp master
		{
			if (!(superSamplingRate <= 1.0) || omp_get_num_threads()==1)
			{
				label->setPixmap(QPixmap::fromImage(image->scaled ( image->width()/superSamplingRate, image->height()/superSamplingRate, Qt::IgnoreAspectRatio, Qt::FastTransformation )));
				label->repaint();
			}
		}
	}

	delete[] zValues;
	cout<<endl;

	label->setPixmap(QPixmap::fromImage(image->scaled ( image->width()/superSamplingRate, image->height()/superSamplingRate, Qt::IgnoreAspectRatio, Qt::SmoothTransformation )));
	label->repaint();
	cout<<"Time: "<<t.elapsed()/1000.0<<endl;

}

QColor Raytracer::raytrace(Vector start, Vector dir, int depth) {
	float dis = FLT_MAX;
	Triangle triangle;
	Vector p;

	for ( int i = 0; i < octree->size(); i++ ) {
		if ( octree->cutVoxel(i, &start, &dir, dis) ) {
			Triangle tr;
			Vector q;

			float tmp = octree->cutTriangles(i, &start, &dir, &tr, &q);
			if ( tmp < dis ) {
				dis = tmp;
				triangle = tr;
				p = q;
			}
		}
	}

	if ( dis != FLT_MAX ) {
		float r = 0.0f, g = 0.0f, b = 0.0f, a1 = 0.0f, a2 = 0.0f, a3=0.0f;
		bool shadow = false;
		//r += triangle.material.ambient[0] * (ambientLight.red()/255.0);
		//g += triangle.material.ambient[1] * (ambientLight.green()/255.0);
		//b += triangle.material.ambient[2] * (ambientLight.blue()/255.0);
		
		if ( lights.size() >= 1 ) {
			r += triangle.material.ambient[0] * lights[0].ambient[0];
			g += triangle.material.ambient[1] * lights[0].ambient[1];
			b += triangle.material.ambient[2] * lights[0].ambient[2];
		}

		for ( unsigned int i = 0; i < lights.size(); i++ ) {
			//r += triangle.material.ambient[0] * lights[i].ambient[0];
			//g += triangle.material.ambient[1] * lights[i].ambient[1];
			//b += triangle.material.ambient[2] * lights[i].ambient[2];

			Vector l = lights[i].position - p;
			l.normalize();

			a2 = dot(p, triangle.ubeta) + triangle.kbeta;
			a3 = dot(p, triangle.ugamma) + triangle.kgamma;
			a1 = 1.0f - a2 - a3;
			//if ( a1 < 0 || a2 < 0 || a3 < 0 || a1 + a2 + a3 > 1 )
			//	cout << "a1: " << a1 << "\ta2: " << a2 << "\ta3: " << a3 << "\n";

			Vector n = triangle.normals[0] * a1 + triangle.normals[1] * a2 + triangle.normals[2] * a3;
			n.normalize();

			Vector a = (p - start); //umgekehrte blickrichtung
			a.normalize();

			if ( dot(n, a) < 0 ) // / (a.norm() * n.norm())) < 0 ) // wenn Winkel zwischen a und n > 90 Grad n invertieren
				n.invert();

			Vector v_r = (n * dot(n, l) * 2) - l;

			if ( dot(n, l) < 0 ) {// / (l.norm() * n.norm())) < 0 ) {
				float ldis = (lights[i].position - p).norm();

				for ( int j = 0; j < octree->size(); j++ ) {

					if ( octree->cutVoxel(j, &p, &l, ldis) ) {
						Vector m;

						octree->cutTriangles(j, &p, &l, &m, ldis);
						float t = (m[0] - p[0]) / l[0];
						Vector mt = p + l * t;
						if ( mt == m && t > 0.00001 && t < ldis ) {
							shadow = true;
							break;
						}
						t = (m[1] - p[1]) / l[1];
						mt = p + l * t;
						if ( mt == m && t > 0.00001 && t < ldis ) {
							shadow = true;
							break;
						}
						t = (m[2] - p[2]) / l[2];
						mt = p + l * t;
						if ( mt == m && t > 0.00001 && t < ldis ) {
							shadow = true;
							break;
						}
					}
				}

				if ( !shadow ) {
					float fatt = 1.0f;

					if ( lights[i].constAtt != 0 && lights[i].linAtt != 0 && lights[i].quadAtt != 0 ) {
						fatt = 1.0f / (lights[i].constAtt + lights[i].linAtt * l.norm() + lights[i].quadAtt * l.norm() * l.norm());
						cout << fatt << "\n";
					}

					r += fatt * (lights[i].diffuse[0] * triangle.material.diffuse[0] * fabs(dot(n, l)) + lights[i].specular[0] * triangle.material.specular[0] * pow(max(0.0f, (float)fabs(scalarProduct(a, v_r))), triangle.material.shininess));
					g += fatt * (lights[i].diffuse[1] * triangle.material.diffuse[1] * fabs(dot(n, l)) + lights[i].specular[1] * triangle.material.specular[1] * pow(max(0.0f, (float)fabs(scalarProduct(a, v_r))), triangle.material.shininess));
					b += fatt * (lights[i].diffuse[2] * triangle.material.diffuse[2] * fabs(dot(n, l)) + lights[i].specular[2] * triangle.material.specular[2] * pow(max(0.0f, (float)fabs(scalarProduct(a, v_r))), triangle.material.shininess));
				}
			}
		}

		r = min(1.0f, r);
		g = min(1.0f, g);
		b = min(1.0f, b);

		if ( triangle.material.isTexture ) {
			Vector tex = triangle.texCoords[0] * a1 + triangle.texCoords[1] * a2 + triangle.texCoords[2] * a3;
			int x = std::abs((int)(tex[0] * (triangle.material.texture.width() - 1))) % triangle.material.texture.width();
			int y = std::abs((int)((1-tex[1]) * (triangle.material.texture.height() - 1))) % triangle.material.texture.height();

			QColor tc = triangle.material.texture.pixel(x, y);

			r *= tc.red();
			g *= tc.green();
			b *= tc.blue();

			return QColor(min((int)r%256, 255), min((int)g%256, 255), min((int)b%256, 255));
		}

		return QColor(min((int)(r * 255)%256, 255), min((int)(g * 255)%256, 255), min((int)(b * 255)%256, 255));
	}

	return backgroundColor;
}
