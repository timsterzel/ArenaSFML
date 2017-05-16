uniform sampler2D texture;

void main()
{	
	vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);
    // Use luminance values for r,g,b to calculate grayscale
    float col = 0.2126 * texColor.r + 0.7152 * texColor.g + 0.0722 * texColor.b;
    texColor.r = col;
	texColor.g = col;
	texColor.b = col;
	gl_FragColor = texColor;	
}
