#include "Raytracer.h"
#include "gui.h"
#include "CGMath.h"

GUI::GUI()
{
	scene = new Scene (this);
	setCentralWidget(scene);

	QMenu *file = new QMenu( QString("File"), this );
	menuBar()->addMenu( file );
 	file->addAction( "Import OBJ-File", this, SLOT(loadFile()), Qt::CTRL+Qt::Key_I );
	file->addAction( "Load Scene", this, SLOT(loadScene()), Qt::CTRL+Qt::Key_L );
	file->addAction( "Save Scene", this, SLOT(saveScene()), Qt::CTRL+Qt::Key_S );
	file->addAction( "Quit", this, SLOT(quit()), Qt::Key_Q );

	QMenu *options = new QMenu( QString("Edit"), this );
	menuBar()->addMenu( options );
	options->addAction( "Add Light", this, SLOT(addLight()));
	options->addAction( "Scale Object", this, SLOT(scale()));
	options->addAction( "Translate Object", this, SLOT(translate()));
	options->addAction( "Rotate Object", this, SLOT(rotate()));
	options->addAction( "Delete Object", this, SLOT(deleteObject()));
 	//options->addAction( "Change RenderMode", this, SLOT(setShaders()), Qt::CTRL+Qt::Key_M );
	options->addAction( "Enable/Disable Backface Culling", this, SLOT(setCulling()), Qt::CTRL+Qt::Key_B );

	QMenu *render = new QMenu( QString("Render"), this );
	menuBar()->addMenu( render );
	render->addAction( "Render Saved Scene", this, SLOT(render()));

	//only for now
	//useShaders=false;
	useCulling=false;
	//scene->setUseShaders(useShaders);
	statusBar()->showMessage(tr("Ready"));

	setWindowTitle(QString("CGViewer"));
	
}

void GUI::loadFile()
{
	QString path;
        path = QFileDialog::getOpenFileName(this,"Choose a file to open",QString::null,QString::null);
	if (!path.isEmpty())
	{
		if (scene->readOBJFile(path))
			statusBar()->showMessage(tr("File Loaded"));
		else
			statusBar()->showMessage(tr("Error on Loading: Couldn't open OBJ-file!"));
    	}
	else
		statusBar()->showMessage(tr("Loading aborted"));
}


/*void GUI::setShaders()
{
	useShaders=!useShaders;
	scene->setUseShaders(useShaders);
}*/

void GUI::setCulling()
{
	useCulling=!useCulling;
	scene->setCullingMode(useCulling);
}

void GUI::scale()
{
	double sx,sy,sz;
	sx=sy=sz=1.0;
	ScaleDialog sd(&sx,&sy,&sz);
	if( sd.exec() )
		scene->scaleObject(sx,sy,sz);
}

void GUI::translate()
{
	double dx,dy,dz;
	dx=dy=dz=0.0;
	TranslateDialog td(&dx,&dy,&dz);
	if( td.exec() )
		scene->translateObject(dx,dy,dz);
}

void GUI::rotate()
{
	double ax,ay,az;
	ax=ay=az=0.0;
	double angle = 0.0;
	RotateDialog rd(&ax,&ay,&az, &angle);
	if( rd.exec() )
		scene->rotateObject(ax,ay,az, angle);
}

void GUI::deleteObject()
{
	//delete selected Object
	scene->deleteObject();
}

void GUI::addLight()
{
	scene->addLight();
}

void GUI::saveScene()
{
	QString path;
	path = QFileDialog::getSaveFileName(this,"Choose a file to save",QString::null,QString::null);
	if (!path.isEmpty())
	{
		scene->saveAsPrimitive(path);
		statusBar()->showMessage(tr("File Saved"));
	}
	else
		statusBar()->showMessage(tr("Saving aborted"));
}


void GUI::loadScene()
{
	QString path;
	path = QFileDialog::getOpenFileName(this,"Choose a file to open",QString::null,QString::null);
	if (!path.isEmpty())
	{
		scene->loadPrimitive(path);
		statusBar()->showMessage(tr("File Loaded"));
	}
	else
		statusBar()->showMessage(tr("Loading aborted"));
}

void GUI::render()
{
	QString path;
	path = QFileDialog::getOpenFileName(this,"Choose a file to open",QString::null,QString::null);
	if (!path.isEmpty())
	{
		Raytracer *r = new Raytracer(path);
		r->show();
		r->genImage();
		r->hide();
	}
	else
		statusBar()->showMessage(tr("Loading aborted"));
}

void GUI::quit() {
	exit(0);
} 
