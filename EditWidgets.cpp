#include "EditWidgets.h"
#include <QLabel>
#include <sstream>


ScaleDialog::ScaleDialog( double *sx, double *sy, double *sz ) : sx(sx), sy(sy), sz(sz)
{
	setWindowTitle(QString("Scaling"));
	resize( 300, 100 );
	
	grid = new QVBoxLayout( this);
	
	// Add parameters for scaling
	scaling = new QHBoxLayout();
	
	QLabel *scaleX = new QLabel( "sx", this);
	QDoubleValidator *val = new QDoubleValidator( this );
	xEdit = new QLineEdit( this );
	xEdit->setText( "1.0" );
	xEdit->setValidator( val );
	scaling->addWidget( scaleX );
	scaling->addWidget( xEdit );
	
	QLabel *scaleY = new QLabel( "sy", this);
	yEdit = new QLineEdit( this );
	yEdit->setText( "1.0" );
	yEdit->setValidator( val );
	scaling->addWidget( scaleY );
	scaling->addWidget( yEdit );
	
	QLabel *scaleZ = new QLabel( "sz", this);
	zEdit = new QLineEdit( this );
	zEdit->setText( "1.0" );
	zEdit->setValidator( val );
	scaling->addWidget( scaleZ );
	scaling->addWidget( zEdit );
	
	grid->addLayout( scaling );
	
	// Add the ok and cancel button
	buttonBox = new QHBoxLayout();
	QSpacerItem *spacer = new QSpacerItem( 0, 0, QSizePolicy::Expanding,
						QSizePolicy::Minimum );
	buttonBox->addItem( spacer );
	
	okPushButton = new QPushButton(this);
	okPushButton->setText( "OK" );
	okPushButton->setDefault( TRUE );
	buttonBox->addWidget( okPushButton );
	
	cancelPushButton = new QPushButton(this);
	cancelPushButton->setText( "Cancel" );
	//cancelPushButton->setAccel( Key_Escape );
	buttonBox->addWidget( cancelPushButton );
	
	grid->addLayout( buttonBox );
	
	connect( okPushButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

	//setModal(true);

}

void ScaleDialog::accept()
{
	*sx = xEdit->text().toDouble();
	*sy = yEdit->text().toDouble();
	*sz = zEdit->text().toDouble();
	QDialog::accept();
}

//----------------------------------------------------------------------------


TranslateDialog::TranslateDialog( double *dx, double *dy, double *dz ) : dx(dx), dy(dy), dz(dz)
{
	setWindowTitle(QString("Translating"));
	resize( 300, 100 );
	
	grid = new QVBoxLayout( this);
	
	// Add parameters for scaling
	scaling = new QHBoxLayout();
	
	QLabel *scaleX = new QLabel( "dx", this);
	QDoubleValidator *val = new QDoubleValidator( this );
	xEdit = new QLineEdit( this );
	xEdit->setText( "0.0" );
	xEdit->setValidator( val );
	scaling->addWidget( scaleX );
	scaling->addWidget( xEdit );
	
	QLabel *scaleY = new QLabel( "dy", this);
	yEdit = new QLineEdit( this );
	yEdit->setText( "0.0" );
	yEdit->setValidator( val );
	scaling->addWidget( scaleY );
	scaling->addWidget( yEdit );
	
	QLabel *scaleZ = new QLabel( "dz", this);
	zEdit = new QLineEdit( this );
	zEdit->setText( "0.0" );
	zEdit->setValidator( val );
	scaling->addWidget( scaleZ );
	scaling->addWidget( zEdit );
	
	grid->addLayout( scaling );
	
	// Add the ok and cancel button
	buttonBox = new QHBoxLayout();
	QSpacerItem *spacer = new QSpacerItem( 0, 0, QSizePolicy::Expanding,
						QSizePolicy::Minimum );
	buttonBox->addItem( spacer );
	
	okPushButton = new QPushButton(this);
	okPushButton->setText( "OK" );
	okPushButton->setDefault( TRUE );
	buttonBox->addWidget( okPushButton );
	
	cancelPushButton = new QPushButton(this);
	cancelPushButton->setText( "Cancel" );
	//cancelPushButton->setAccel( Key_Escape );
	buttonBox->addWidget( cancelPushButton );
	
	grid->addLayout( buttonBox );
	
	connect( okPushButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

	//setModal(true);

}

void TranslateDialog::accept()
{
	*dx = xEdit->text().toDouble();
	*dy = yEdit->text().toDouble();
	*dz = zEdit->text().toDouble();
	QDialog::accept();
}

//----------------------------------------------------------------------------


RotateDialog::RotateDialog( double *ax, double *ay, double *az, double *angle ) : ax(ax), ay(ay), az(az), angle(angle)
{
	setWindowTitle(QString("Translating"));
	resize( 300, 100 );
	
	grid = new QVBoxLayout( this);
	
	// Add parameters for scaling
	scaling = new QHBoxLayout();
	
	QLabel *scaleX = new QLabel( "ax", this);
	QDoubleValidator *val = new QDoubleValidator( this );
	xEdit = new QLineEdit( this );
	xEdit->setText( "0.0" );
	xEdit->setValidator( val );
	scaling->addWidget( scaleX );
	scaling->addWidget( xEdit );
	
	QLabel *scaleY = new QLabel( "ay", this);
	yEdit = new QLineEdit( this );
	yEdit->setText( "0.0" );
	yEdit->setValidator( val );
	scaling->addWidget( scaleY );
	scaling->addWidget( yEdit );
	
	QLabel *scaleZ = new QLabel( "az", this);
	zEdit = new QLineEdit( this );
	zEdit->setText( "0.0" );
	zEdit->setValidator( val );
	scaling->addWidget( scaleZ );
	scaling->addWidget( zEdit );

	QLabel *rAngle = new QLabel( "angle", this);
	angleEdit = new QLineEdit( this );
	angleEdit->setText( "0.0" );
	angleEdit->setValidator( val );
	grid->addWidget( rAngle );
	grid->addWidget( angleEdit );
	
	grid->addLayout( scaling );
	
	// Add the ok and cancel button
	buttonBox = new QHBoxLayout();
	QSpacerItem *spacer = new QSpacerItem( 0, 0, QSizePolicy::Expanding,
						QSizePolicy::Minimum );
	buttonBox->addItem( spacer );
	
	okPushButton = new QPushButton(this);
	okPushButton->setText( "OK" );
	okPushButton->setDefault( TRUE );
	buttonBox->addWidget( okPushButton );
	
	cancelPushButton = new QPushButton(this);
	cancelPushButton->setText( "Cancel" );
	//cancelPushButton->setAccel( Key_Escape );
	buttonBox->addWidget( cancelPushButton );
	
	grid->addLayout( buttonBox );
	
	connect( okPushButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

	//setModal(true);

}

void RotateDialog::accept()
{
	*ax = xEdit->text().toDouble();
	*ay = yEdit->text().toDouble();
	*az = zEdit->text().toDouble();
	*angle = angleEdit->text().toDouble();
	QDialog::accept();
}

//------------------------------------------------------------------------------

LightDialog::LightDialog(Light *light)
{

	this->light=light;
	
	unsigned int labelWidth = 68, labelHight = 20;
	
	setWindowTitle( QString("Add Lightsource") );
	resize( 300, 200 );
	
	QDoubleValidator *att      = new QDoubleValidator( 0.0, 1.0, 6, this );
	QDoubleValidator *val = new QDoubleValidator( 0.0, 300.0, 6, this );

	grid = new QVBoxLayout( this);
	
	// Add ambient color
	ambientBox = new QHBoxLayout();
	QLabel *ambientLabel = new QLabel( QString("Ambient"), this);
	ambientLabel->setMinimumSize( QSize(labelWidth,labelHight) );
	ambientLabel->setMaximumSize( QSize(labelWidth,labelHight) );
	
	ambColorButton = new QPushButton(this);
	//ambColorButton->setPaletteBackgroundColor ( QColor( 50, 50, 50 ) );
	connect( ambColorButton, SIGNAL( clicked() ), this, SLOT( setAmbientColor() ));
	
	aaEdit = new QLineEdit( this );
	aaEdit->setText( "1.0" );
	aaEdit->setValidator( val );
	
	ambientBox->addWidget( ambientLabel );
	ambientBox->addWidget( ambColorButton );
	ambientBox->addWidget( aaEdit );
	
	grid->addLayout( ambientBox );
	
	// Add diffuse color
	diffuseBox = new QHBoxLayout();
	QLabel *diffuseLabel = new QLabel( QString("Diffuse"), this);
	diffuseLabel->setMinimumSize( QSize(labelWidth,labelHight) );
	diffuseLabel->setMaximumSize( QSize(labelWidth,labelHight) );
	
	diffColorButton = new QPushButton(this);
	//diffColorButton->setPaletteBackgroundColor ( QColor( 50, 50, 50 ) );
	connect( diffColorButton, SIGNAL( clicked() ), this, SLOT( setDiffuseColor() ));
	
	daEdit = new QLineEdit( this );
	daEdit->setText( "1.0" );
	daEdit->setValidator( val );
	
	diffuseBox->addWidget( diffuseLabel );
	diffuseBox->addWidget( diffColorButton );
	diffuseBox->addWidget( daEdit );
	
	grid->addLayout( diffuseBox );
	
	// Add specular color
	specularBox = new QHBoxLayout();
	QLabel *specularLabel = new QLabel( QString("Specular"), this);
	specularLabel->setMinimumSize( QSize(labelWidth,labelHight) );
	specularLabel->setMaximumSize( QSize(labelWidth,labelHight) );
	
	specColorButton = new QPushButton(this);
	//specColorButton->setPaletteBackgroundColor ( QColor( 50, 50, 50 ) );
	connect( specColorButton, SIGNAL( clicked() ), this, SLOT( setSpecularColor() ));
	
	saEdit = new QLineEdit( this );
	saEdit->setText( "1.0" );
	saEdit->setValidator( val );
	
	specularBox->addWidget( specularLabel );
	specularBox->addWidget( specColorButton );
	specularBox->addWidget( saEdit );
	
	grid->addLayout( specularBox );
	
	// Add attenuation
	attBox = new QVBoxLayout();
	QLabel *attLabel1 = new QLabel( QString("constant Attenuation"), this);
	QLabel *attLabel2 = new QLabel( QString("linear Attenuation"), this);
	QLabel *attLabel3 = new QLabel( QString("quadratic Attenuation"), this);
	attLabel1->setMinimumSize( QSize(300,labelHight) );
	attLabel1->setMaximumSize( QSize(300,labelHight) );
	attLabel2->setMinimumSize( QSize(300,labelHight) );
	attLabel2->setMaximumSize( QSize(300,labelHight) );
	attLabel3->setMinimumSize( QSize(300,labelHight) );
	attLabel3->setMaximumSize( QSize(300,labelHight) );
	constAttEdit = new QLineEdit( this );
	constAttEdit->setText( "0.0" );
	constAttEdit->setValidator( att );
	linAttEdit = new QLineEdit( this );
	linAttEdit->setText( "0.0" );
	linAttEdit->setValidator( att );
	quadAttEdit = new QLineEdit( this );
	quadAttEdit->setText( "0.0" );
	quadAttEdit->setValidator( att );
	
	attBox->addWidget( attLabel1 );
	attBox->addWidget( constAttEdit );
	attBox->addWidget( attLabel2 );
	attBox->addWidget( linAttEdit );
	attBox->addWidget( attLabel3 );
	attBox->addWidget( quadAttEdit );
	
	grid->addLayout( attBox );
	
	// Add the ok and cancel button
	buttonBox = new QHBoxLayout();
	QSpacerItem *spacer = new QSpacerItem( 0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
	buttonBox->addItem( spacer );
	
	okPushButton = new QPushButton(this);
	okPushButton->setText( "OK" );
	okPushButton->setDefault( TRUE );
	buttonBox->addWidget( okPushButton );
	
	cancelPushButton = new QPushButton(this);
	cancelPushButton->setText( "Cancel" );
	buttonBox->addWidget( cancelPushButton );
	
	grid->addLayout( buttonBox );
	
	connect( okPushButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

//----------------------------------------------------------------------------

void LightDialog::accept()
{
	//QColor ambient, diffuse, specular;
	
	//ambient = ambColorButton->paletteBackgroundColor();
	//light->setAmbient( ambient.red()/255., ambient.green()/255., ambient.blue()/255., aaEdit->text().toDouble() );
	
	//diffuse = diffColorButton->paletteBackgroundColor();
	//light->setDiffuse( diffuse.red()/255., diffuse.green()/255.,diffuse.blue()/255., daEdit->text().toDouble() );
	
	//specular = specColorButton->paletteBackgroundColor();
	//light->setSpecular( specular.red()/255., specular.green()/255., specular.blue()/255., saEdit->text().toDouble() );
	
	//light->setAttenuation( attEdit->text().toDouble() );
	//light->setName( nameEdit->text() );

	light->setAmbient((float)ambientColor.red()/255.0,(float)ambientColor.green()/255.0,(float)ambientColor.blue()/255.0);
	light->setDiffuse((float)diffuseColor.red()/255.0,(float)diffuseColor.green()/255.0,(float)diffuseColor.blue()/255.0);
	light->setSpecular((float)specularColor.red()/255.0,(float)specularColor.green()/255.0,(float)specularColor.blue()/255.0);
	light->setAttenuation(constAttEdit->text().toDouble(), linAttEdit->text().toDouble(), quadAttEdit->text().toDouble());
	/*light->constAtt = attEdit->text().toDouble();
	light->linAtt = attEdit->text().toDouble();
	light->quadAtt = attEdit->text().toDouble();*/

	QDialog::accept();
}

void LightDialog::setAmbientColor()
{
	//QColor ambientColor = QColorDialog::getColor( ambColorButton->paletteBackgroundColor() );
	//ambColorButton->setPaletteBackgroundColor ( ambientColor );
	ambientColor = QColorDialog::getColor();
	std::stringstream s;
	s<<"* { background-color: rgb("<<ambientColor.red()<<","<<ambientColor.green()<<","<<ambientColor.blue()<<") }";
	ambColorButton->setStyleSheet(s.str().c_str());
		
}

void LightDialog::setDiffuseColor()
{
	//QColor diffuseColor = QColorDialog::getColor( diffColorButton->paletteBackgroundColor() );
	//diffColorButton->setPaletteBackgroundColor ( diffuseColor );
	diffuseColor = QColorDialog::getColor();
	std::stringstream s;
	s<<"* { background-color: rgb("<<diffuseColor.red()<<","<<diffuseColor.green()<<","<<diffuseColor.blue()<<") }";
	diffColorButton->setStyleSheet(s.str().c_str());
}

void LightDialog::setSpecularColor()
{
	//QColor specularColor = QColorDialog::getColor( specColorButton->paletteBackgroundColor() );
	//specColorButton->setPaletteBackgroundColor ( specularColor );
	specularColor = QColorDialog::getColor();
	std::stringstream s;
	s<<"* { background-color: rgb("<<specularColor.red()<<","<<specularColor.green()<<","<<specularColor.blue()<<") }";
	specColorButton->setStyleSheet(s.str().c_str());
}


