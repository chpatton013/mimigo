#version 120

varying vec4 vPosition;
varying vec4 vNormal;

void main()
{
   vec3 normal = normalize(vNormal.xyz);
   gl_FragColor = vec4(vNormal.x, vNormal.y, vNormal.z, 1.0f);
}