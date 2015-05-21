#version 140


uniform mat4 MVP;
in vec3 position;
in vec3 color;
in float alpha;
out vec4 vColor;

  void main(){
	
	//if (position.x == 0 && position.y == 0 && position.z == 0) {
	//	discard;
	//}  
	gl_Position =  MVP * vec4(position, 1);

	float d = distance(gl_Position, vec4(0,0,0,1));
	gl_PointSize = 10000/(d*d);
    vColor = vec4(color, 1.0f);
}


