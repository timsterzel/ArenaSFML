uniform sampler2D texture;

float minThree(float r, float g, float b);
float maxThree(float r, float g, float b);

void main()
{	
	vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);
	float colMin = minThree(texColor.r, texColor.b, texColor.g);
	float colMax = maxThree(texColor.r, texColor.b, texColor.g);
	float col = (colMin + colMax) / 2.0;
	texColor.r = col;
	texColor.g = col;
	texColor.b = col;
	gl_FragColor = texColor;	
	//gl_FragColor = gl_Color;
	//gl_FragColor = texture2D(texture, gl_TexCoord[0].xy);
}

float minThree(float r, float g, float b)
{
	float minVar = min(r, g);
	minVar = min(minVar, b);
	return minVar;
}

float maxThree(float r, float g, float b)
{
	float maxVar = max(r, g);
	maxVar = max(maxVar, b);
	return maxVar;
}
