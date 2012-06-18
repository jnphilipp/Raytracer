uniform sampler2D colorMap;
uniform int numLights;
varying vec3 normal, vertex, eyeVec;

void main() {
	vec4 color = gl_FrontLightModelProduct.sceneColor * gl_FrontMaterial.ambient;
	vec3 N = normalize(normal);
	vec3 E = normalize(eyeVec);

	for ( int l = 0; l<numLights; ++l ) {
		vec3 L = normalize(gl_LightSource[l].position.xyz - vertex);

		if ( dot(N, L) > 0.0 ) {
			vec3 R = reflect(-L, N);
			//float shin = 1.0f;
			float shin = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);

			color.r += dot(N, L) * gl_LightSource[l].diffuse.r * gl_FrontMaterial.diffuse.r + gl_LightSource[l].specular.r * gl_FrontMaterial.specular.r * shin;
			color.g += dot(N, L) * gl_LightSource[l].diffuse.g * gl_FrontMaterial.diffuse.g + gl_LightSource[l].specular.g * gl_FrontMaterial.specular.g * shin;
			color.b += dot(N, L) * gl_LightSource[l].diffuse.b * gl_FrontMaterial.diffuse.b + gl_LightSource[l].specular.b * gl_FrontMaterial.specular.b * shin;
		}
	}
	
	gl_FragColor = color * texture2D(colorMap, gl_TexCoord[0].st);
}
