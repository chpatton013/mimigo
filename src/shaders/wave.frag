varying vec4 vPosition;
varying vec4 vNormal;

void main()
{
   /*gl_FragColor = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0f);*/
   vec3 normal = normalize(vNormal.xyz);
   gl_FragColor = vec4(normal.x, normal.y, normal.z, 1.0f);
}
