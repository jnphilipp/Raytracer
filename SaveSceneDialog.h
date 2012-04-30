#ifndef SAVESCENEDIALOG_H
#define SAVESCENEDIALOG_H

#include "CGMath.h"
#include <sstream>

struct Parameters
{
	int width, height;
	Vector eyePoint;
	Vector viewDirection; //Mittelpunkt der Bildebene
	float focalLength;
	Vector upVector;
	float back_r, back_g, back_b;
	float back_brigthness_r, back_brigthness_g, back_brigthness_b;
};

class SaveDialog : public QDialog
{
	Q_OBJECT
	
	public:
		SaveDialog(Parameters *p);
	
	protected slots:
		void accept();

	private:
		Parameters *p;

		QLineEdit *sizeEditX, *sizeEditY;
		QLineEdit *eye_x, *eye_y, *eye_z;
		QLineEdit *lookAt_x, *lookAt_y, *lookAt_z;
		QLineEdit *focal_length;
		QLineEdit *up_x, *up_y, *up_z;
		QLineEdit *back_r, *back_g, *back_b;
		QLineEdit *amb_r, *amb_g, *amb_b;

		QPushButton *okPushButton;
		QPushButton *cancelPushButton;
};

#endif
