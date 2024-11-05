// The MIT License
// Copyright © 2021 Inigo Quilez
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// Exact distance to a sphere cut by a plane. Beware doing the max() of
// a sphere and a plane won't produce an exact Euclidean distance.
// Based on sdCutDisk(): https://www.shadertoy.com/view/ftVXRc
//
// It is a useful primitive when combined with rounding/inflating, which
// cannot be done with the non-Euclidean max() approach, since you can do
// things like mushroom heads.

// List of other 3D SDFs: https://www.shadertoy.com/playlist/43cXRl
//
// and https://iquilezles.org/articles/distfunctions
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

vec3 gcolor( vec2 hit ){
  return vec3 (hit.y > 0.5 ?  vec3(0.25, 0.4, 0.33) : vec3(0.05, 0.3, 0.57));
}
void main(){
  
  // normalize pixel space
  vec2 uv = gl_FragCoord.xy / res;
  // center the origin
  uv -= 0.5;
  //uv *= 2.0;

  // apply aspectratio
  uv.x *= res.x / res.y;

  vec3 col = vec3( 0.0 ); // this is our canvas

  vec3 ro = vec3( 0.0, 0.0, -1.0 ); // ray origin a.k.a. the eye or camera position
  vec3 rd = normalize( vec3( uv, 1.0 ) ); // ray direction - we cast a ray to each uv-coordinate

  vec2 t = ray(ro, rd);
  vec3 pos = ro + rd * t.x; // the rays endpoint relative to the eye
  vec3 posl = vec3( cos ( time * 0.03 ) * 60.75 + 30., sin( time * 0.3) * 20.75 + 10., -1.0) ;//+ sin ( time ); // the position of the light source

  float amb = 0.2; // + 0.5 * dot( calcNormal(pos), vec3( 0.0, 1.0, 0.0));

  float dif = dlight(pos, posl);
  
  float checker = mod(floor(pos.x) + floor(pos.z), 2.0);

  vec3 color = gcolor(t);

  color *= t.y < 0.5 ? checker : 1.0;

  col = vec3( vec3( 0.2 * amb ) + vec3( 0.9 * dif ) );

  //  gl_FragColor = vec4( clamp(vec3(col), 0.05, 0.9), 1.0 );
  gl_FragColor = vec4( clamp(vec3(color * dif / ( 0.5 * ( abs(pos.z * 0.3) + 0.6 ) ) ), 0.0, 1.0 ), 1.0 );
  }
