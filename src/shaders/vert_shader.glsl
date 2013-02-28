uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

attribute vec3 aAmbient;
attribute vec3 aDiffuse;
/*attribute vec3 aSpecular;*/
attribute vec3 aNormal;
attribute vec3 aPosition;
attribute vec2 aTexture;

varying vec3 vAmbient;
varying vec3 vDiffuse;
varying vec3 vSpecular;
varying vec4 vPosition;
varying vec4 vNormal;
varying vec2 vTexture;

void main() {
   vPosition = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
   gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vPosition;

   vNormal = uNormalMatrix * vec4(aNormal.x, aNormal.y, aNormal.z, 0.0);

   vDiffuse = aDiffuse;
   vAmbient = aAmbient;
   vTexture = aTexture;
}
