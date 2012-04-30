#include <QApplication>
#include "main.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);

     GUI window;
     window.resize(1244,700);

     window.show();
     return app.exec();
} 
