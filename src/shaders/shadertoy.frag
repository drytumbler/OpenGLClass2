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
#define ITERATIONS 64
#define MIN_DIST 0.005
#define MAX_DIST 128.0


in vec3 fragmentColor;
in vec2 fragmentTexCoord;


uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;
uniform sampler2D moon;

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

float sdBox ( vec3 p, vec3 z) {
  vec3 q = abs( p ) - z;
  return length(max(q, 0.0)) + min(max(q.x, max(q.y, q.z)), 0.0);
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

float circle (vec2 uv, vec2 p, float r, float blur){
  float d = length( uv - p );
  return smoothstep( r + blur, r - blur, d );
}

float toline(vec3 ro, vec3 rd, vec3 p){
  return length( cross( p - ro, rd ) ) / length( rd );
}

float smin( float a, float b, float k ){
  //https://www.youtube.com/watch?v=khblXafu7iA&t=1069s
  float h = max( k - abs( a - b ), 0.0 ) / k;
  return min( a, b ) - h * h * h * k * .125;
}
vec3 flip (vec3 p ) {
  vec3 res;
  if (p.x >= 0.0 ){
    res = p.yxz;
    return res;
  }
  return p;
}
vec2 map( vec3 p ){
  vec2 result = vec2( 0.0 );
  vec3 spherePos = vec3( 1.77 * sin( time * 0.5 + 0.5), 0.0, 0.0 );
  spherePos = flip(spherePos);
  float c = sdSphere(p*vec3(1.3,1.0,1.4), spherePos, 0.35 + (0.1 * (1.0 + sin(time))));

  vec3 boxDim = vec3(0.65);
  float b = sdBox(p, boxDim); 

  float v = sdPlane(p, vec3(0., 1., 0.), .5);

  result.x = min(smin(.7 * c, b, 1.05), v );
  return result;
  //return sphere;
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

vec3 calcNormal( in vec3 pos)
{
  vec2 e = vec2(1.0,-1.0) * 0.57703;
    const float eps = 0.005;
    return normalize( e.xyy*map( pos + e.xyy*eps ).x + 
					  e.yyx*map( pos + e.yyx*eps ).x + 
					  e.yxy*map( pos + e.yxy*eps ).x + 
					  e.xxx*map( pos + e.xxx*eps ).x );
}

float dlight ( vec3 pos, vec3 posl ){
  vec3 l = normalize( posl - pos );
  vec3 nor = calcNormal( pos );
  float dif = clamp( dot( nor, l ), 0.0, 1.0 );
  vec2 d = ray( pos + nor * 0.07, l );
  if( d.x < length( posl - pos ) ) dif *= 0.7;
  return dif;
}

vec3 lookat( vec2 uv, vec3 ro, vec3 p, float zm ){
  // https://www.youtube.com/watch?v=PBxuVlp7nuM&list=PLGmrMu-IwbguU_nY2egTFmlg691DN7uE5&index=10
  vec3 f = normalize(p - ro);
  vec3 r = cross(vec3(0., 1., 0.), f);
  vec3 u = cross(f, r);

  vec3 c = ro + f * zm;
  vec3 i = c + uv.x*r + uv.y*u;

  return i - ro;
}

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float inc = 0.1;
void main(){
  float blur =  MIN_DIST;
  
  // normalize pixel space 0 / 1
  vec2 uv = gl_FragCoord.xy / res;
  // center the origin -0.5 / +0.5
  uv -= 0.5;
  // make it -1 / +1
  //uv *= 2.0;
  // apply aspectratio
  uv.x *= res.x / res.y;

  // distortion
  /*
  uv += sin(time * 0.1) * 0.02 * rand(uv);
  if (sin(time) < 0){
    uv.x += .25;
  }
  */

  
  vec3 col = vec3( 1.0 ); // this is our canvas
  //-------------------------------------------
  // camera
  vec3 ro = vec3(5.0 * cos(time * 0.3), 3.0, 5.0 * sin(time * 0.3 + 0.2) );
  //vec3 ro = vec3(0.0, 0.0, -3.0);
  vec3 rd = lookat(uv, ro, vec3(-0.5773, 0.5, 0.), 1.);
  // raytracing
  float t = ray(ro, rd).x;
  vec3 pos = ro + rd*t;
  vec3 posl = vec3(-1.0, 1.0, -1.0);
  vec3 posl2 = vec3(.0, 5.0, .0);
  vec3 posl3 = vec3(3.0, 0.3, 3.0);

  float dif = dlight(pos, posl);
  float dif2 = dlight(pos, posl2);
  float dif3 = dlight(pos, posl3);

  vec3 lcol = vec3(0.98, 0.97, 1.);
  
  //col = vec3(texture(moon, 0.5 + pos.xy).r);
  //col = vec3(t);
  col *= t/8.;
  col *= 0.5*col + 0.5;
  //col*=(0.5 * dif + min(dif, dif2));
  col *= 0.8 * (dif * 1.5 + dif2 * 2.0 + dif3 * 0.9);

  
  //-------------------------------------------
  
  gl_FragColor = vec4( pow(0.5 * vec3(0.5 * dif + 0.5 * dif2 + dif3), vec3(1.2) - 0.3) * lcol, 1.0 );
  //gl_FragColor *= vec4(uv.x, uv.y, pos.z, 1.0);
}
