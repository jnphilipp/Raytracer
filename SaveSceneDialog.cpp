#include "SaveSceneDialog.h"

SaveDialog::SaveDialog(Parameters *p)
{
	this->p = p;
	QVBoxLayout *grid = new QVBoxLayout(this);
	QDoubleValidator *val1 = new QDoubleValidator( 0.0, 1.0, 6, this );
	QIntValidator *val2 = new QIntValidator ( 0, 4096, this );
	QDoubleValidator *val3 = new QDoubleValidator( -4000.0, 4000.0, 6, this );
	setWindowTitle("Set Propertiesfor the Raytracer");

	QHBoxLayout* box1 = new QHBoxLayout();
	QLabel* label1 = new QLabel( QString("Window Size:"), this);
	QLabel* label2 = new QLabel( QString("X"), this);
	sizeEditX = new QLineEdit( this );
	sizeEditX->setText( "640" );
	sizeEditX->setValidator( val2 );
	sizeEditY = new QLineEdit( this );
	sizeEditY->setText( "480" );
	sizeEditY->setValidator( val2 );
	box1->addWidget(label1);
	box1->addWidget(sizeEditX);
	box1->addWidget(label2);
	box1->addWidget(sizeEditY);
	grid->addLayout(box1);

	QHBoxLayout* box2 = new QHBoxLayout();
	QLabel* label3 = new QLabel( QString("Eye Point:"), this);
	eye_x = new QLineEdit( this );
	eye_x->setText( QString("%1").arg(p->eyePoint(0)) );
	eye_x->setValidator( val3 );
	eye_y = new QLineEdit( this );
	eye_y->setText( QString("%1").arg(p->eyePoint(1)) );
	eye_y->setValidator( val3 );
	eye_z = new QLineEdit( this );
	eye_z->setText( QString("%1").arg(p->eyePoint(2)) );
	eye_z->setValidator( val3 );
	box2->addWidget(label3);
	box2->addWidget(eye_x);
	box2->addWidget(eye_y);
	box2->addWidget(eye_z);	
	grid->addLayout(box2);

	QHBoxLayout* box3 = new QHBoxLayout();
	QLabel* label5 = new QLabel( QString("View Direction:"), this);
	lookAt_x = new QLineEdit( this );
	lookAt_x->setText( QString("%1").arg(p->viewDirection(0)) );
	lookAt_x->setValidator( val3 );
	lookAt_y = new QLineEdit( this );
	lookAt_y->setText( QString("%1").arg(p->viewDirection(1)) );
	lookAt_y->setValidator( val3 );
	lookAt_z = new QLineEdit( this );
	lookAt_z->setText( QString("%1").arg(p->viewDirection(2)) );
	lookAt_z->setValidator( val3 );
	box3->addWidget(label5);
	box3->addWidget(lookAt_x);
	box3->addWidget(lookAt_y);
	box3->addWidget(lookAt_z);	
	grid->addLayout(box3);

	QHBoxLayout* box4 = new QHBoxLayout();
	QLabel* label6 = new QLabel( QString("Focal Length:"), this);
	focal_length = new QLineEdit( this );
	focal_length->setText( "1.8" );
	focal_length->setValidator( val3 );
	box4->addWidget(label6);
	box4->addWidget(focal_length);	
	grid->addLayout(box4);

	QHBoxLayout* box7 = new QHBoxLayout();
	QLabel* label9 = new QLabel( QString("Up Vector:"), this);
	up_x = new QLineEdit( this );
	up_x->setText( QString("%1").arg(p->upVector(0)) );
	up_x->setValidator( val3 );
	up_y = new QLineEdit( this );
	up_y->setText( QString("%1").arg(p->upVector(1)) );
	up_y->setValidator( val3 );
	up_z = new QLineEdit( this );
	up_z->setText( QString("%1").arg(p->upVector(2)) );
	up_z->setValidator( val3 );
	box7->addWidget(label9);
	box7->addWidget(up_x);
	box7->addWidget(up_y);
	box7->addWidget(up_z);	
	grid->addLayout(box7);

	QHBoxLayout* box5 = new QHBoxLayout();
	QLabel* label7 = new QLabel( QString("Color of Background:"), this);
	back_r = new QLineEdit( this );
	back_r->setText( "0.0" );
	back_r->setValidator( val1 );
	back_g = new QLineEdit( this );
	back_g->setText( "0.0" );
	back_g->setValidator( val1 );
	back_b = new QLineEdit( this );
	back_b->setText( "1.0" );
	back_b->setValidator( val1 );
	box5->addWidget(label7);
	box5->addWidget(back_r);
	box5->addWidget(back_g);
	box5->addWidget(back_b);	
	grid->addLayout(box5);

	QHBoxLayout* box6 = new QHBoxLayout();
	QLabel* label8 = new QLabel( QString("Color of Ambient Light:"), this);
	amb_r = new QLineEdit( this );
	amb_r->setText( "0.1" );
	amb_r->setValidator( val1 );
	amb_g = new QLineEdit( this );
	amb_g->setText( "0.1" );
	amb_g->setValidator( val1 );
	amb_b = new QLineEdit( this );
	amb_b->setText( "0.1" );
	amb_b->setValidator( val1 );
	box6->addWidget(label8);
	box6->addWidget(amb_r);
	box6->addWidget(amb_g);
	box6->addWidget(amb_b);	
	grid->addLayout(box6);

	// Add the ok and cancel button
	QHBoxLayout *buttonBox = new QHBoxLayout();
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

void SaveDialog::accept()
{
	p->width = sizeEditX->text().toInt();
	p->height = sizeEditY->text().toInt();
	p->eyePoint = Vector(eye_x->text().toDouble(), eye_y->text().toDouble(), eye_z->text().toDouble());    
	p->viewDirection = Vector(lookAt_x->text().toDouble(), lookAt_y->text().toDouble(),lookAt_z->text().toDouble());
	p->focalLength = focal_length->text().toDouble();
	p->upVector = Vector(up_x->text().toDouble(), up_y->text().toDouble(), up_z->text().toDouble());
	p->back_r = back_r->text().toDouble();
	p->back_g = back_g->text().toDouble();
	p->back_b = back_b->text().toDouble();
	p->back_brigthness_r = amb_r->text().toDouble();
	p->back_brigthness_g = amb_g->text().toDouble();
	p->back_brigthness_b = amb_b->text().toDouble();

	QDialog::accept();
}
