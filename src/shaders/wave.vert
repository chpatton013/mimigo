#version 120

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uNormalMatrix;

attribute vec3 aPosition;
attribute vec3 aNormal;

varying vec4 vPosition;
varying vec4 vNormal;

void main(void)
{
   vPosition = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0f);
   gl_Position = uViewMatrix * uModelMatrix * vPosition;
   vNormal = uNormalMatrix * vec4(aNormal.x, aNormal.y, aNormal.z, 0.0f);
}
