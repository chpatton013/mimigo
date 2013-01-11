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
   vec4 normal = normalize(vNormal);

   if (uCelShaderUnit == 1) {
      gl_FragColor = vec4(0, 0, 0, 1.0);
   }
   else {
      /* Toon shading */
      vec3 intensity;
      float intensity_float = max(0.0, dot(lightDirection, normal));
      if (intensity_float > 14.0/32.0)
         intensity = vec3(1.0);
      else if (intensity_float > 4.0/32.0)
         intensity = vec3(0.5);
      else
         intensity = vec3(0.2);

      vec3 light = vDiffuse + vAmbient;

      vec4 color;
      if (uUseTexture == 0) {
         color = vec4(light.r, light.g, light.b, 1.0);
      } else {
         color = texture2D(uTextureUnit, vTexture);
         if (color.r == 1.0 && color.g == 0.0 && color.b == 1.0)
            discard;
         color = vec4(color.r + vAmbient.r/10.0,
                      color.g + vAmbient.g/10.0,
                      color.b + vAmbient.b/10.0, 1.0);
      }
      color = vec4(color.r * intensity.r, color.g*intensity.g, color.b*intensity.b, 1.0);
      gl_FragColor = color;
   }
}
