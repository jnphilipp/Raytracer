#ifndef EDITWIDGETS_H
#define EDITWIDGETS_H

#include <QtGui>
#include <iostream>
#include "Light.h"

class ScaleDialog : public QDialog
{
	Q_OBJECT
	public:
		ScaleDialog( double *sx, double *sy, double *sz );
	
	private:
		double *sx;
		double *sy;
		double *sz;
		QPushButton *okPushButton;
		QPushButton *cancelPushButton;
		QLineEdit *xEdit;
		QLineEdit *yEdit;
		QLineEdit *zEdit;
	
	protected:
		QVBoxLayout *grid;
		QHBoxLayout *scaling;
		QHBoxLayout *buttonBox;
	
	protected slots:
		void accept();
	
};

class TranslateDialog : public QDialog
{
	Q_OBJECT
	public:
		TranslateDialog( double *dx, double *dy, double *dz );
	
	private:
		double *dx;
		double *dy;
		double *dz;
		QPushButton *okPushButton;
		QPushButton *cancelPushButton;
		QLineEdit *xEdit;
		QLineEdit *yEdit;
		QLineEdit *zEdit;
	
	protected:
		QVBoxLayout *grid;
		QHBoxLayout *scaling;
		QHBoxLayout *buttonBox;
	
	protected slots:
		void accept();
	
};

class RotateDialog : public QDialog
{
	Q_OBJECT
	public:
		RotateDialog( double *ax, double *ay, double *az, double *angle );
	
	private:
		double *ax;
		double *ay;
		double *az;
		double *angle;
		QPushButton *okPushButton;
		QPushButton *cancelPushButton;
		QLineEdit *xEdit;
		QLineEdit *yEdit;
		QLineEdit *zEdit;
		QLineEdit *angleEdit;
	
	protected:
		QVBoxLayout *grid;
		QHBoxLayout *scaling;
		QHBoxLayout *buttonBox;
	
	protected slots:
		void accept();
	
};

class LightDialog : public QDialog
{
	Q_OBJECT
	
	public:
		LightDialog(Light *light);
	
	private:
			
		QLineEdit *nameEdit;
		QLineEdit  *aaEdit;
		QLineEdit  *daEdit;   
		QLineEdit  *saEdit;   
		QLineEdit  *constAttEdit;
		QLineEdit  *linAttEdit;
		QLineEdit  *quadAttEdit;
	
		QPushButton *ambColorButton;
		QPushButton *diffColorButton;
		QPushButton *specColorButton;

		QColor ambientColor;
		QColor diffuseColor;
		QColor specularColor;
	
		QPushButton *okPushButton;
		QPushButton *cancelPushButton;

		Light *light;
	
	protected:
		QVBoxLayout *grid;
		QHBoxLayout *ambientBox;
		QHBoxLayout *diffuseBox;
		QHBoxLayout *specularBox;
		QVBoxLayout *attBox;
		QHBoxLayout *buttonBox;
		QHBoxLayout *nameBox;
	
	protected slots:
		void accept();
		void setAmbientColor();
		void setDiffuseColor();
		void setSpecularColor();
};


#endif
