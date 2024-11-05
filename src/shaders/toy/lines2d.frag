#version 330 core

#define  red		vec3(1.0, 0.0, 0.0)
#define  green		vec3(0.17, 1.0, 0.2)
#define  blue  	       	vec3(0.0, 0.0, 1.0)
#define  yellow	       	vec3(1.0, 1.0, 0.0)
#define  magenta       	vec3( 1.0, 0.0, 1.0 )
#define  cyan       	vec3( 0.0, 1.0, 1.0 )
#define  white       	vec3( 1.0, 1.0, 1.0 )
#define  black		vec3( 0.0, 0.0, 0.0 )

#define SHARPNESS 0.005
#define ITERATIONS 256
#define MIN_DIST 0.001
#define MAX_DIST 500.0


in vec3 fragmentColor;
in vec2 fragmentTexCoord;


uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;

uniform float time;
uniform vec2 res;


float sdPlane( vec3 p, vec3 n, float h )
{
  // n must be normalized
  return dot( p , n ) + h;
}

float sdSphere( vec3 p, vec3 center, float r ){
  return length( p - center ) - r;
}


vec2 map( vec3 p ){
  vec2 result = vec2( 0.0 );
  vec3 spherePos = vec3( 2.0 + 2.7 * sin( time / 4.0 ) + 0.2, 1.66 + - 1.4 * cos( time / 4.0 + 1.7 ) - 0.1, 6.0 + 5.5 * sin( time / 4.0 - 0.5) );
  float sphere = sdSphere(vec3(p.x, p.y, p.z + sin( time )), spherePos, 0.16);

  result.x = sphere;
  result.y = 1.0;
  
  float plane = sdPlane( vec3( p.x * sin( time ) + 5. * cos (time ), p.y, p.z  + 3. * cos( time + 0.3)), normalize(vec3(0.02*sin(time / 7.), 1.0, 0.0)), 4.0);

  if (plane < result.x) {
    result.x = plane;
    result.y = 0.0;
  }
  return result;
  //return sphere;
}

vec3 calcNormal( in vec3 pos)
{
  vec2 e = vec2(1.0,-1.0) * 0.57703;
    const float eps = 0.005;
    return normalize( e.xyy*map( pos + e.xyy*eps ).x + 
					  e.yyx*map( pos + e.yyx*eps ).x + 
					  e.yxy*map( pos + e.yxy*eps ).x + 
					  e.xxx*map( pos + e.xxx*eps ).x );
}

vec2 ray( vec3 ro, vec3 rd ){
  vec2 t = vec2( 0.0 );
  for( int i = 0; i < ITERATIONS; i++ ){
    vec3 p = ro + rd * t.x;
    vec2 d = map( p );
    t.x += d.x;
    t.y = d.y;
    if ( d.x < MIN_DIST || t.x > MAX_DIST ) break; // break if we hit an object or travel to far
  }
  return t;
}

float dlight ( vec3 pos, vec3 posl ){
  vec3 l = normalize( posl - pos );
  vec3 nor = calcNormal( pos );
  float dif = clamp( dot( nor, l ), 0.0, 1.0 );
  vec2 d = ray( pos + nor * MIN_DIST * 2., l );
  if( d.x < length( posl - pos ) ) dif *= 0.7;
  return dif;
}

float vline (vec2 uv, float x, float wd, float blur){
  float vsplit1 = smoothstep( 0.00, blur, uv.x - x + wd );
  float vsplit2 = smoothstep( blur, 0.00, uv.x - x - wd );
  return vsplit1 * vsplit2;
}

float hline (vec2 uv, float y, float wd, float blur){
  float hsplit1 = smoothstep( 0.00, blur, uv.y - y + wd );
  float hsplit2 = smoothstep( blur, 0.00, uv.y - y - wd );
  return hsplit1 * hsplit2;
}

float line (float t, float wd, float blur){
  float split1 = smoothstep( 0.00, blur, t + wd );
  float split2 = smoothstep( blur, 0.00, t - wd );
  return split1 * split2;
}

float pline (vec2 uv, float t, vec2 p, float wd, float blur) {
  float split1 = smoothstep( blur, 0.00, uv.x - t * ( uv.y - p.y ) - p.x - wd);
  float split2 = smoothstep( 0.00, blur, uv.x - t * ( uv.y - p.y ) - p.x + wd);
  return split1 * split2;

}

void main(){
  
  // normalize pixel space
  vec2 uv = gl_FragCoord.xy / res;
  // center the origin
  uv -= 0.5;
  uv *= 2.0;

  // apply aspectratio
  uv.x *= res.x / res.y;

  vec3 col = vec3( 1.0 ); // this is our canvas

  // circle
  float blur =  MIN_DIST * 1;
  vec2 p = vec2( cos( time ), 0.25 );
  float r = 0.2;
  float d = length( uv - p );
  float c = smoothstep( r + blur, r - blur, d );
  col.g = c;

  // vertical
  float wd = 0.01;
  float x = 0.250;
  float vsplit1 = smoothstep( 0.00, blur, uv.x - x + wd );
  float vsplit2 = smoothstep( blur, 0.00, uv.x - x - wd );
  float vert = vline(uv, x, wd, blur);

  // horizontal
  float y = -0.5;
  float hsplit1 = smoothstep( 0.00, blur, uv.y - y + wd );
  float hsplit2 = smoothstep( blur, 0.00, uv.y - y - wd );
  float horz = hline(uv, y, wd, blur);

  // line
  vec2 s = vec2(x, y);
  float dx = 2.0;
  float split1 = smoothstep( blur, 0.00, uv.x - dx * ( uv.y - s.y ) - s.x - wd);
  float split2 = smoothstep( 0.00, blur, uv.x - dx * ( uv.y - s.y ) - s.x + wd);
  //float line = ( split1 == 0. && split2 == 0. ) ? 0.0 : 1.0;

  float q = line(uv.y + uv.x + 0.5, wd, blur);
  float m = pline(uv, 1.5, vec2(0.0, 0.5), 2 * wd, blur);
  // dot
  float dot = vert * horz;

  // perpendicular lines through point k:
  vec2 k = vec2( 0.3, 0.3 );
  float t = 1.41;
  float perp =  pline(uv, t, k, wd, blur) + pline( uv, -1 / t, k, wd, blur );
  
  float cross = vert + horz + q + m + perp;

  wd = 0.1;
  float rect = line(uv.x * cos(time) + .2, wd, blur) * line(2.0 * uv.y * sin(time) + 0.2, wd, blur); 
  gl_FragColor = vec4( vec3( rect + cross ), 1.0 );
}
