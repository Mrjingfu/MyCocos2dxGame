
uniform vec3 u_DirLightSourceColor[1];
uniform vec3 u_DirLightSourceDirection[1];

uniform vec3 u_AmbientLightSourceColor;

#ifdef GL_ES
varying mediump vec2 v_texture_coord;
varying mediump vec3 v_normal;
#else
varying vec2 v_texture_coord;
varying vec3 v_normal;
#endif


varying float v_fogFactor;

uniform vec4 u_fogColor;

uniform vec4 u_color;

vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation)
{
    float diffuse = max(dot(normalVector, lightDirection), 0.0);
    vec3 diffuseColor = lightColor  * diffuse * attenuation;
    
    return diffuseColor;
}

void main(void)
{
    vec3 normal  = normalize(v_normal);
    
    vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);

    vec3 lightDirection = normalize(u_DirLightSourceDirection[0] * 2.0);
    combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[0], 1.0);
    
    vec4 finalColor = texture2D(CC_Texture0, v_texture_coord);
    
    gl_FragColor = mix(u_fogColor, texture2D(CC_Texture0, v_texture_coord), v_fogFactor ) * u_color * combinedColor;
}
