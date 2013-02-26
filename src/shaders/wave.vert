#version 120
/* what we still need:
 * the light
 *    direction vec3 (x,y,z,0)
 *    color vec3(r,g,b)
 * the material
 *    diffuse, ambient, specular
 *    (each are vec3s)
 * the eye position
 */

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;
uniform mat4 uNormalMatrix;
uniform vec4 uLights[3];
uniform int uLightTypes;
uniform vec3 uCameraPosition;

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec3 aAmbient;
attribute vec3 aDiffuse;
attribute vec3 aSpecular;
attribute vec3 aTexture;

varying vec4 vPosition;
varying vec4 vNormal;
varying vec3 vAmbient;
varying vec3 vDiffuse;
varying vec3 vSpecular;

void main(void)
{
   vPosition = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0f);
   gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vPosition;
   vNormal = uNormalMatrix * vec4(aNormal.x, aNormal.y, aNormal.z, 0.0f);
   vPosition = gl_Position;
   vAmbient = aAmbient;
   vDiffuse = aDiffuse;
   vSpecular = aSpecular;
}
