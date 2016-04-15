uniform sampler2D color_map;
uniform sampler2D data_map;
uniform sampler2D environment_map;


uniform float f_bufferWidth;
uniform float f_bufferHeight;

varying vec2 Texcoord;

void main( void )
{

  vec4  displaceColor = texture2D( data_map, Texcoord );

  float value = displaceColor.r;
  float speed = displaceColor.g;


  float pixel_offsetX = 1.0/f_bufferWidth;
  float pixel_offsetY = 1.0/f_bufferHeight;

  float f_value_up   = texture2D( data_map, Texcoord + vec2(0.0, pixel_offsetY) ).r;
  float f_value_down = texture2D( data_map, Texcoord + vec2(0.0, -pixel_offsetY) ).r;

  float f_value_left  = texture2D( data_map, Texcoord + vec2(-pixel_offsetX, 0.0) ).r;
  float f_value_right = texture2D( data_map, Texcoord + vec2(pixel_offsetX, 0.0) ).r;

  float f_value = value;

  float diff_left  = f_value - f_value_left;
  float diff_right = f_value_right - f_value;

  float averageH = (diff_left + diff_right) * 0.5;


  float diff_up  = f_value - f_value_up;
  float diff_down = f_value_down - f_value;

  float averageV = (diff_up + diff_down) * 0.5;

  vec2 offset = vec2(averageH, -averageV);





  /// LIGHTING
  vec4 v4_backgroundDisplacedColor = texture2D( color_map, vec2(0.0, 1.0) - Texcoord + offset*0.9);


  /// ambient
  vec4 finalAmbient = mix(v4_backgroundDisplacedColor * 0.9, displaceColor, 0.001);
//  vec4 finalAmbient = v4_backgroundDisplacedColor * (vec4(1.0, 1.0, 1.0, 1.0) - displaceColor);


  /// some vectors for diffuse and specular
  vec3 normal      = vec3(averageH, averageV, 0.0);
  vec3 f3_lightVec = normalize(vec3(-1.0, 1.0, 0.5));


  /// diffuse light
  float f_NDotL         = dot(normal, f3_lightVec) ;
  vec4  v4_finalDiffuse = v4_backgroundDisplacedColor * f_NDotL * 4.5;

  v4_finalDiffuse = clamp(v4_finalDiffuse, -0.4, 1.0);

  /// specular light
  vec3  f3_ViewDirection = normalize(vec3(0.0, -0.5, 1.0));

  vec3  v3_Reflection   = normalize( ( ( 2.0 * normal ) * f_NDotL ) - f3_lightVec );
  float f_RDotV         = max( 0.0, dot( v3_Reflection, f3_ViewDirection ) );
  float f_TotalSpecular = pow(f_RDotV*100.0, 2.0) * 2.0;




  /// env map
  vec3 u2 = normalize(f3_lightVec);
  vec3 r = reflect( normal, u2 );
  float m = 2.0 * sqrt( r.x*r.x + r.y*r.y + (r.z+1.0)*(r.z+1.0) );
  vec2 new_TextCoord;
  new_TextCoord.s = r.x/m + 0.5;
  new_TextCoord.t = 1.0-(r.y/m + 0.5);

  vec4 v4_reflection = (texture2D(environment_map, new_TextCoord.st ) * 1.0) * abs(dot(normal, vec3(1.0,1.0,0.0)));


  ///
  gl_FragColor = ( finalAmbient +  f_TotalSpecular + v4_finalDiffuse + v4_reflection);
//  gl_FragColor = (/*finalAmbient + v4_finalDiffuse + f_TotalSpecular*/ + v4_reflection);
//  gl_FragColor =   v4_finalDiffuse;
//  gl_FragColor =   displaceColor;
}
