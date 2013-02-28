// Color, Position, Direction
uniform vec4 uLights[3];
uniform int  uLightTypes[1];
uniform sampler2D uTextureUnit;
uniform int uUseTexture;
uniform int uCelShaderUnit;
/*uniform vec4 uCameraPosition;*/

varying vec3 vAmbient;
varying vec3 vDiffuse;
varying vec3 vSpecular;
varying vec4 vNormal;
varying vec4 vPosition;
varying vec2 vTexture;

void main() {
   vec4 lightDirection = normalize(uLights[2]);
   vec4 normal = vec4(normalize(vNormal.xyz), 1.0);

   vec3 intensity;
   float intensity_float = max(0.0, dot(lightDirection, normal));
   if (intensity_float > 30.0/32.0)
      intensity = vec3(1.0);
   else if (intensity_float > 25.0 / 32.0)
      intensity = vec3(0.85);
   else if (intensity_float > 17.0/32.0)
      intensity = vec3(0.7);
   else if (intensity_float > 9.0/32.0)
      intensity = vec3(0.5);
   else
      intensity = vec3(0.2);

   vec3 light = vDiffuse + vAmbient;

   vec4 color = vec4(uLights[0].x, uLights[0].y, uLights[0].z, 0.0f); 
   color = vec4(color.r * light.r, color.g * light.g, color.b * light.b, 1.0);
   color = vec4(color.r * intensity.r, color.g*intensity.g, color.b*intensity.b, 1.0);
   gl_FragColor = color;
}
