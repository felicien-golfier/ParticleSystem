#version 140


uniform mat4 MVP;

in vec3 position;
in vec3 color;

out vec4 vColor;


void main()
{

  gl_Position = MVP * vec4( position, 1.0f );

  gl_PointSize =  10000/(gl_Position.z*gl_Position.z);
  
  vColor = vec4(color,0.5f);

}
