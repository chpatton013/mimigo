// Color, Position, Direction
uniform vec4 uLights[3];
uniform int uLightTypes[1];
uniform sampler2D uTextureUnit;
uniform int uUseTexture;
uniform int uCelShaderUnit;
//uniform vec3 uCameraPosition;
uniform vec3 uCameraForward;

varying vec3 vAmbient;
varying vec3 vDiffuse;
varying vec3 vSpecular;
varying vec4 vNormal;
varying vec4 vPosition;
varying vec2 vTexture;

void main() {
   vec4 lightDirection = normalize(uLights[2]);
   vec4 normal = vec4(normalize(vNormal.xyz), 1.0);

   vec4 texColor1 = texture2D(uTextureUnit, vTexture);
   vec3 light = vec3(1.0);

   vec3 intensity;
   if (dot(vec3(normal), normalize(uCameraForward)) < 0.2) {
      intensity = vec3(0.0);
   } else {
      float intensity_float = max(0.0, dot(lightDirection, normal));
      if (intensity_float > 32.0/32.0) {
         intensity = vec3(1.0);
      } else if (intensity_float > 27.0 / 32.0) {
         intensity = vec3(0.85);
      } else if (intensity_float > 19.0/32.0) {
         intensity = vec3(0.7);
      } else if (intensity_float > 9.0/32.0) {
         intensity = vec3(0.5);
      } else {
         intensity = vec3(0.2);
      }
   }

   gl_FragColor = vec4(
      texColor1.r * light.r * intensity.r,
      texColor1.g * light.g * intensity.g,
      texColor1.b * light.b * intensity.b,
      1.0
   );
}
