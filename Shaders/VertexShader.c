varying vec3 normal, vertex;

void main()
{
	//gl_Position 	= ftransform()
 	gl_Position     = gl_ModelViewProjectionMatrix * gl_Vertex;
	normal 			= normalize(gl_NormalMatrix * gl_Normal);
	vertex 			= vec3(gl_ModelViewMatrix * gl_Vertex);
}

