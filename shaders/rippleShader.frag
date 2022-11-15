// attributes from vertShader.vert
varying vec4 vColor; //is a vector with four values.
varying vec2 vTexCoord;//is a vector with two values

// uniforms These variables can be manipulated directly from our C++ code
uniform sampler2D uTexture; //will hold a texture.
uniform float uTime;

void main() {
	float coef = sin(gl_FragCoord.y * 0.1 + 1 * uTime);
	vTexCoord.y +=  coef * 0.03;
	gl_FragColor = vColor * texture2D(uTexture, vTexCoord);
}

//this executes for each pixel
//involved in the draw function that's called on each frame of our game