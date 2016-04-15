uniform sampler2D data_map;
uniform sampler2D targetTex;
uniform sampler2D objects_map;

uniform float f_reset;
uniform float f_texelWidth;
uniform float f_texelHeight;



varying vec2 Texcoord;

void main( void )
{



  // the value is in the RED color
  // the speed is in the GREEN color

  float influence  = 390.0;
  float smallWaves = 39999.0; /// size of waves
  float viscosity  = 1.999;
  float friction   = 0.9999;



  float offsetX = f_texelWidth;
  float offsetY = f_texelHeight;

  float neighboursValues = 0.0;

  neighboursValues += texture2D( data_map, Texcoord + vec2(offsetX, offsetY) ).r;
  neighboursValues += texture2D( data_map, Texcoord + vec2(offsetX, -offsetY) ).r;
  neighboursValues += texture2D( data_map, Texcoord + vec2(-offsetX, offsetY) ).r;
  neighboursValues += texture2D( data_map, Texcoord + vec2(-offsetX, -offsetY) ).r;

  neighboursValues += texture2D( data_map, Texcoord + vec2(offsetX, 0) ).r;
  neighboursValues += texture2D( data_map, Texcoord + vec2(-offsetX, 0) ).r;
  neighboursValues += texture2D( data_map, Texcoord + vec2(0, offsetY) ).r;
  neighboursValues += texture2D( data_map, Texcoord + vec2(0, -offsetY) ).r;


  float value   = (texture2D( targetTex, Texcoord).r);
  //float value   = objectsInWaterValue;



  float allOverCenter = (value + neighboursValues*influence)/(8.0 * influence + 1.0);
  float forceToCenter = (allOverCenter - value) * viscosity;



  float speed = (texture2D( targetTex, Texcoord)).g;
        speed = (speed + forceToCenter * smallWaves)/(smallWaves + 1.0);

  value += speed;

  /// the brush
  float objectsInWaterValue = texture2D( objects_map, Texcoord).g;

  float newValue = (value) + objectsInWaterValue;
  float newSpeed = (speed);

  if (f_reset!=0.0)
  {
   gl_FragColor = noise4(3.0);
  }
  else
  {
   gl_FragColor = vec4(newValue*friction, newSpeed, 0.0, 0.0);
  }
}
