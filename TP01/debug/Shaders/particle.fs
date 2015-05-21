#version 140

in vec4 vColor;
out vec4 fragColor;
uniform sampler2D tex;
void isBlack (vec3 pixel){
	if (pixel.x < 0.1	&& pixel.y < 0.1 && pixel.z < 0.1){
		discard;
	}
}
void main(){
 
    vec4 texColor = texture2D(tex, gl_PointCoord);
	isBlack(texColor.rgb);
    fragColor = vec4(texColor.rgb, texColor.a)*vColor;

}
