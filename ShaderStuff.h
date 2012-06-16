#ifndef SHADERSTUFF_H
#define SHADERSTUFF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

#include <GL/glew.h>
#include <GL/glext.h>

// Loading shader function
GLhandleARB loadShader(const char* filename, unsigned int type);

#endif
