uniform int numLights;
varying vec3 normal, vertex;

void main()
{
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
	for (int l=0; l<numLights; ++l)
	{
		vec3 lightPosition = gl_LightSource[l].position.xyz;
		color.r += dot (normal, lightPosition - vertex);
		color.g += dot (normal, lightPosition - vertex);
		color.b += dot (normal, lightPosition - vertex);
	}
	
	gl_FragColor = color;
}
