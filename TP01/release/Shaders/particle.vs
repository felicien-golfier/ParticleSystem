#version 140


uniform mat4 MVP;
in vec3 position;
in vec4 color;
out vec4 vColor;

  void main(){
	  
	gl_Position =  MVP * vec4(position, 1);

	float d = distance(gl_Position, vec4(0,0,0,1));
	gl_PointSize = 1000/(d);
    vColor = color;
}


