varying vec4 vPosition;
varying vec4 vNormal;

void main()
{
   /*gl_FragColor = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0f);*/
   gl_FragColor = vec4(vNormal.x, vNormal.y, vNormal.z, 1.0f);
}
