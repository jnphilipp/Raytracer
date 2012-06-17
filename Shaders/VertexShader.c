varying vec3 normal, eyeVec, vertex;

void main() {
 	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	normal = normalize(gl_NormalMatrix * gl_Normal);
	vertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	eyeVec = -vertex;

	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}
