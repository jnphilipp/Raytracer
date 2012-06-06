#ifndef SHADERSTUFF_H
#define SHADERSTUFF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

#include <GL/glew.h>
#include <GL/glext.h>

using namespace std;

// Loading shader function
GLhandleARB loadShader(char* filename, unsigned int type);

#endif
