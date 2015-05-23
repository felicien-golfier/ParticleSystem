#version 140


uniform mat4 MVP;
in vec3 position;
in vec4 color;
out vec4 vColor;
out float theta;

// Retourne un résultat compris entre 0 et 1 exclut.
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
  
	gl_Position =  MVP * vec4(position, 1);

	float d = distance(gl_Position, vec4(0,0,0,1));
	gl_PointSize = 1000/(d);
	vColor = color;

	theta = 3.14 * rand(gl_Position.yz);
	// theta = 1.0;
}


