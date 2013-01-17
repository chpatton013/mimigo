#version 120

varying vec4 vPosition;
varying vec4 vNormal;

void main()
{
   vec3 normal = normalize(vNormal.xyz);
   gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
