varying vec2 Texcoord;
varying vec3 u;

void main( void )
{
  gl_Position = ftransform();
  Texcoord    = gl_MultiTexCoord0.xy;
}
