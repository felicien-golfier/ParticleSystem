#version 140

uniform sampler2D texture;
in vec4 vColor;

out vec4 fragColor;


void main()
{
  gl_FragColor = vColor ;

  }
