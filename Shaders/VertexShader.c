varying vec3 normal, lightDir, eyeVec;

void main() {
	normal = gl_NormalMatrix * gl_Normal;

	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
	eyeVec = -vVertex;

	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}


/*varying vec3 normal, vertex;

void main()
{
	//gl_Position 	= ftransform()
 	gl_Position     = gl_ModelViewProjectionMatrix * gl_Vertex;
	normal 			= normalize(gl_NormalMatrix * gl_Normal);
	vertex 			= vec3(gl_ModelViewMatrix * gl_Vertex);
}*/
