uniform sampler2D colorMap;
varying vec3 normal, lightDir, eyeVec;

void main (void) {
	vec4 final_color = (gl_FrontLightModelProduct.sceneColor * gl_FrontMaterial.ambient) + (gl_LightSource[0].ambient * gl_FrontMaterial.ambient);

	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);

	float lambertTerm = dot(N,L);

	if(lambertTerm > 0.0) {
		final_color += gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * lambertTerm;

		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), gl_FrontMaterial.shininess);
		final_color += gl_LightSource[0].specular * gl_FrontMaterial.specular * specular;
	}

	gl_FragColor = final_color * texture2D( colorMap, gl_TexCoord[0].st);
}

/*uniform int numLights;
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
}*/
