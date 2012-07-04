uniform sampler2D basemap;
uniform sampler2D normalmap;
uniform int numLights;
varying vec3 normal, vertex, eyeVec;

void main() {
	vec4 color = gl_FrontLightModelProduct.sceneColor;
	vec3 N = normalize(normal);
	vec3 E = normalize(eyeVec);


	if ( gl_TexCoord[0].s > 0.0 && gl_TexCoord[0].t > 0.0 ) {
		const float maxVariance = 2.5; // Mess around with this value to increase/decrease normal perturbation (2.0 is standard)
		const float minVariance = maxVariance / 2.0;
		N = texture2D(normalmap, gl_TexCoord[0].st).rgb * maxVariance - minVariance;
		//calculate Tangtent
		vec3 Q1 = dFdx(vertex);
		vec3 Q2 = dFdy(vertex);
		vec2 st1 = dFdx(gl_TexCoord[0]).xy;
		vec2 st2 = dFdy(gl_TexCoord[0]).xy;
		vec3 t = normalize(Q1*st2.t - Q2*st1.t);
		vec3 b = normalize(-Q1*st2.s + Q2*st1.s);
		//smoothing
		t = normalize(cross(t, N));
		b = normalize(cross(b, N));
		// the transpose of texture-to-eye space matrix
		mat3 TBN = mat3(t, b, normal);
		N = N * TBN;
		N = normalize (normal + N);
	}

	for ( int l = 0; l < numLights; ++l ) {
		vec3 L = normalize(gl_LightSource[l].position.xyz - vertex);

		if ( dot(N, L) > 0.0 ) {
			vec3 R = reflect(-L, N);
			float shin = pow(max(dot(R, E), 0.0), gl_FrontMaterial.shininess);
			float fatt = gl_LightSource[l].constantAttenuation + gl_LightSource[l].linearAttenuation * length(L) + gl_LightSource[l].quadraticAttenuation * length(L) * length(L);

			if ( fatt != 0.0 )
				fatt = 1.0 / fatt;
			else
				fatt = 1.0;

			color += fatt * (dot(N, L) * gl_LightSource[l].diffuse * gl_FrontMaterial.diffuse + gl_LightSource[l].specular * gl_FrontMaterial.specular * shin);
		}
	}
	
	gl_FragColor = color * texture2D(basemap, gl_TexCoord[0].st);

	//check, if a black border has to be drawn
	if ( abs(dot(normalize(eyeVec), normal)) < 0.2 ) {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
		return;
	}

	color = gl_FrontLightModelProduct.sceneColor;

	for ( int l = 0; l<numLights; ++l ) {
		float lambert = dot (normalize(normal), normalize(gl_LightSource[l].position.xyz - vertex));
		if ( lambert < 0.0 )
			lambert = 0.0;

		// Discretize the intensity, based on a few cutoff points
    if ( lambert > 0.85 )
        color += vec4(1.0, 1.0, 1.0, 1.0) * gl_FragColor;
    else if ( lambert > 0.5 )
        color += vec4(0.7, 0.7, 0.7, 1.0) * gl_FragColor;
    else if ( lambert > 0.05 )
        color += vec4(0.35, 0.35, 0.35, 1.0) * gl_FragColor;
    else
        color += vec4(0.1, 0.1, 0.1, 1.0) * gl_FragColor;
	}

	gl_FragColor = color;
}
