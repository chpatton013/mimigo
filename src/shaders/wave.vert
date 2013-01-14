uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

attribute vec3 aPosition;
attribute vec3 aNormal;

varying vec4 vPosition;
varying vec4 vNormal;

void main(void)
{
   vPosition = uModelMatrix * vec4(aPosition.x, aPosition.y, aPosition.z, 1.0f);
   gl_Position = vPosition;
   vNormal = vec4(aNormal.x, aNormal.y, aNormal.z, 0.0f);
}
