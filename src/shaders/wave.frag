#version 120

uniform vec4 uLights[3];
uniform int uLightTypes;
uniform vec3 uEyePosition;

varying vec4 vPosition;
varying vec4 vNormal;
varying vec3 vAmbient;
varying vec3 vDiffuse;
varying vec3 vSpecular;

void main()
{
   /* h = (l + eye) / ||l + eye||*/
   /* v = vPosition - eyePosition */
   /* facing = 1 if n.l > 0, 0 otherwise */
   /* ambient light is ambient * light color */
   /* diffuse light is diffuse * light * max(N.L, 0) */
   /* specular light: specular * light * facing * (v.r)^shininess */

   float shininess = 5.0;
   vec3 amb = /*vAmbient;*/vec3(0.5,0.2,0.5);
   vec3 dif = /*vDiffuse;*/vec3(0.4, 0.3, 0.5);
   vec3 spec = /*vSpecular;*/vec3(0.3, 0.1, 0.4);
   vec3 color = /*uLights[0].xyz;*/vec3(0.5, 0.5, 0.5);

   vec3 l;
   if(uLightTypes == 0)
      l = uLights[2].xyz - uEyePosition;
   else if(uLightTypes == 1 || uLightTypes == 2)
      l = uLights[1].xyz;
   l = normalize(l);
   vec3 normal = normalize(vNormal.xyz);
   vec3 r = -1.0f * l + 2.0f * dot(normal, l) * normal;
   float nDotL = dot(normal, l);
   int facing = 1;
   if(nDotL < 0.0f) {
      facing = 0;
   }
   vec3 v = normalize(uEyePosition-vPosition.xyz);
   
   vec3 ambient = clamp(amb * color,0.0f,1.0f);
   vec3 diffuse = clamp(dif * color * nDotL,0.0f,1.0f);
   vec3 specular = clamp(spec * color * facing * pow(dot(v, r), shininess), 0.0f, 1.0f);

   if(uLightTypes == 2)
      gl_FragColor = vec4(normal.x, normal.y, normal.z, 1.0f);
   else if(uLightTypes == 0 || uLightTypes == 1)
      gl_FragColor = vec4(clamp(ambient + diffuse,0.0f,0.9999999f), 1.0f);
   else
      gl_FragColor = vec4(0.6, 0.3, 0.1, 1.0);
   
   /*gl_FragColor = vec4(0.5, 0.6, 0.7, 1.0);*/
   /*gl_FragColor = vec4(0, 0, 0, 1.0f);*/
}
