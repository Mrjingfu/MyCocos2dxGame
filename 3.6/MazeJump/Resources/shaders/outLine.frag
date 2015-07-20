uniform vec3 u_outlineColor;
uniform vec4 u_color;

void main(void)
{
    gl_FragColor =  vec4(u_outlineColor,1.0) * u_color;
}
