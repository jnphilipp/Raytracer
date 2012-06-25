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
			float shin = (gl_FrontMaterial.shininess == 0.0 ? 0.0 : pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess));
			float fatt = gl_LightSource[l].constantAttenuation + gl_LightSource[l].linearAttenuation * length(L) + gl_LightSource[l].quadraticAttenuation * length(L) * length(L);

			if ( fatt != 0.0 )
				fatt = 1.0 / fatt;
			else
				fatt = 1.0;

			color += fatt * (dot(N, L) * gl_LightSource[l].diffuse * gl_FrontMaterial.diffuse + gl_LightSource[l].specular * gl_FrontMaterial.specular * shin);
		}
	}
	
	gl_FragColor = color * texture2D(colorMap, gl_TexCoord[0].st);
}
