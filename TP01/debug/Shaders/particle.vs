#version 140


uniform mat4 MVP;
in vec3 position;
in vec3 color;
in float alpha;
out vec4 vColor;

  void main(){
	  
	gl_Position =  MVP * vec4(position,1);
	gl_PointSize = 10000/(gl_Position.z*gl_Position.z);
    vColor = vec4(color,alpha);
}


