// Color, Position, Direction
uniform vec4 uLights[3];
uniform int  uLightTypes[1];
uniform sampler2D uTextureUnit;
uniform int uUseTexture;
uniform int uCelShaderUnit;
uniform vec3 uCameraPos;

varying vec3 vAmbient;
varying vec3 vDiffuse;
varying vec3 vSpecular;
varying vec4 vNormal;
varying vec4 vPosition;
varying vec2 vTexture;

void main() {

vec4 texColor1 = texture2D(uTextureUnit, vTexture);
   vec4 lightDirection = normalize(uLights[2]);
   vec4 normal = vec4(normalize(vNormal.xyz), 1.0);

   // assuming the view vector is always orthagonal (0,0,-1);
   //float outline = dot((vPosition.xyz - uCameraPos), vNormal.xyz);

   vec3 intensity;
   float intensity_float = max(0.0, dot(lightDirection, normal));
   if (intensity_float > 32.0/32.0)
      intensity = vec3(1.0);
   else if (intensity_float > 27.0 / 32.0)
      intensity = vec3(0.85);
   else if (intensity_float > 19.0/32.0)
      intensity = vec3(0.7);
   else if (intensity_float > 9.0/32.0)
      intensity = vec3(0.5);
   else
      intensity = vec3(0.2);
   
   /*if(outline > 0.51f)
      intensity = vec3(0.1);*/

   vec3 light = vec3(1.0);

   vec4 color = texColor1;
   color = vec4(color.r * light.r, color.g * light.g, color.b * light.b, 1.0);
   color = vec4(color.r * intensity.r, color.g*intensity.g, color.b*intensity.b, 1.0);
   gl_FragColor = color;
  gl_FragColor = vec4( color[0],  color[1],  color[2], 1);
}
