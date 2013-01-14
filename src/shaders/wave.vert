attribute vec3 aPosition;

void main(void)
{
   gl_Position = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0f);
}
