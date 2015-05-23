// #version 140

// in vec4 vColor;
// out vec4 fragColor;
// uniform sampler2D tex;
// void isBlack (vec3 pixel){
// 	if (pixel.x < 0.01	&& pixel.y < 0.01 && pixel.z < 0.01){
// 		discard;
// 	}
// }
// void main(){
 
//     vec4 texColor = texture2D(tex, gl_PointCoord);
// 	isBlack(texColor.rgb);

// 	fragColor = vec4(texColor.rgb, texColor.a) * vColor;

// }

#version 140

in vec4 vColor;
in float theta;
out vec4 fragColor;
uniform sampler2D tex;

// Supprime les pixels noir. 
void isBlack (vec3 pixel){
	if (pixel.x < 0.01	&& pixel.y < 0.01 && pixel.z < 0.01){
		discard;
	}
}

// Retourne un résultat compris entre 0 et 1 exclut.
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// Discard de plus en plusw de pixel lorsqu'on s'éloigne du centre. 
void degrade (vec2 pos)
{

	if (abs(pos.x - 0.5) > 0.4 || abs(pos.y - 0.5) > 0.4){
		if(rand(pos) > 0.3)discard;
	}else if (abs(pos.x - 0.5) > 0.3 || abs(pos.y - 0.5) > 0.3){
		if(rand(pos) > 0.5)discard;
	}else if (abs(pos.x - 0.5) > 0.2 || abs(pos.y - 0.5) > 0.2){
		if(rand(pos) > 0.75)discard;
	}

	// if (abs(pos.y - 0.5) > 0.4 && abs(pos.y - 0.5) > 0.4){
	// 	if(rand(pos) > 0.3)discard;
	// }else if (abs(pos.y - 0.5) > 0.3 && abs(pos.y - 0.5) > 0.3){
	// 	if(rand(pos) > 0.5)discard;
	// }else if (abs(pos.y - 0.5) > 0.2 && abs(pos.y - 0.5) > 0.2){
	// 	if(rand(pos) > 0.75)discard;
	// }
	
}


void main(){

	//degrade(gl_PointCoord);
	mat2 rotation = mat2(
		cos(theta), -sin(theta),
		sin(theta), cos(theta)
	);

	float mid = 0.5;
	vec2 rotated = vec2(cos(theta) * (gl_PointCoord.x - mid) + sin(theta) * (gl_PointCoord.y - mid) + mid,
	                  cos(theta) * (gl_PointCoord.y - mid) - sin(theta) * (gl_PointCoord.x - mid) + mid);

    vec4 texColor = texture2D(tex, rotated);
	//isBlack(texColor.rgb);
    fragColor = vec4(texColor.rgb, texColor.a)*vColor;

}
