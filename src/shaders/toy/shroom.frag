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
#define  magenta       	vec3(1.0, 0.0, 1.0)
#define  cyan       	vec3(0.0, 1.0, 1.0)
#define  white       	vec3(1.0, 1.0, 1.0)
#define  black		vec3(0.0, 0.0, 0.0)

#define SHARPNESS 0.005


in vec3 fragmentColor;
in vec2 fragmentTexCoord;

out vec4 screenColor;

uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;

uniform float time;
uniform vec2 res;

// r is the sphere's radius, h is the plane's position
float sdCutSphere( in vec3 p, in float r, in float h )
{
    float w = sqrt(r*r-h*h); // constant for a given shape
    
    vec2 q = vec2( length(p.xz), p.y );
    
    float s = max( (h-r)*q.x*q.x+w*w*(h+r-2.0*q.y), h*q.x-w*q.y );

    return (s<0.0) ? length(q)-r :
           (q.x<w) ? h - q.y     :
                     length(q-vec2(w,h));
}

float map( in vec3 pos )
{
    if( sin(time*0.8)>-0.1 )
    {
    pos.yz = (mat2(-4,3,-3,-4)/5.0)*pos.yz;
    return sdCutSphere(pos, 0.5, -0.2 );
    }
    else
    {
    pos.y += 0.1;
    float d = sdCutSphere(pos, 0.5, 0.2 ) - 0.1;
    return min( d, max(length(pos.xz)-0.15,pos.y-0.2) );
    }
}

// https://iquilezles.org/articles/normalsSDF
vec3 calcNormal( in vec3 pos)
{
    vec2 e = vec2(1.0,-1.0)*0.5773;
    const float eps = 0.0005;
    return normalize( e.xyy*map( pos + e.xyy*eps ) + 
					  e.yyx*map( pos + e.yyx*eps ) + 
					  e.yxy*map( pos + e.yxy*eps ) + 
					  e.xxx*map( pos + e.xxx*eps ) );
}



float Circle (vec2 p, float r, float blur){
  float dC = length(p) - r;
  float c = smoothstep(blur, - blur, dC);
  return c;
}

float sdSphere( vec3 p, float s )
{
  return length(p)-s;
}

void main(){
  /*
  vec3 baseColor = texture(sandstone, fragmentTexCoord).rgb;
  float alpha = texture(mask, fragmentTexCoord).a;
  
  // Normalized pixel coordinates (from 0 to 1)
  vec2 uv = gl_FragCoord.xy / res;
  uv -= 0.5;
  //uv *= 2.0;
  uv.x *= res.x / res.y;

  vec3 col = vec3(uv.x, uv.y, 0.0);

  float d = length(uv);
  float r = 0.05 * sin(time) + 0.50;
  vec2 center = vec2(0.2 * sin(time), 0.1 * cos(time));
    
  float c = Circle(uv + center * 0.333, r, 0.05);
  float c2 = Circle(uv + center * 0.666 , r, 0.05);
  float c3 = Circle(uv + center, r, 0.05);
  //  c2 = c2 > 0 ? 1.0 : 0.0;
  
  //screenColor = vec4(vec3(c, c2, c3) * 0.2 * baseColor + baseColor * 0.8, 1.0f);
  float baseLight = 0.150;
  //float baseLight = 0.50;
  float spotLight = 0.850;
  //float spotLight = 0.50;
  //screenColor = vec4((vec3(c, c2, c3) + baseLight) * spotLight * baseColor, 1.0f);
  screenColor = vec4((vec3(c, c2, c3) + baseLight) * spotLight * baseColor, 1.0f);

  screenColor = pow(screenColor, vec4(1.1));


  float c4 = sdSphere(vec3(uv.x, uv.y, gl_FragCoord.z/20.0), 0.25);

  screenColor = vec4(vec3(c4), 1.0);
  */
       // camera movement	
	float an = 0.8*time;
	vec3 ro = vec3( 1.0*cos(an), 0.0, 1.0*sin(an) );
    vec3 ta = vec3( 0.0, 0.0, 0.0 );
    // camera matrix
    vec3 ww = normalize( ta - ro );
    vec3 uu = normalize( cross(ww,vec3(0.0,1.0,0.0) ) );
    vec3 vv = normalize( cross(uu,ww));
    
    
    vec3 tot = vec3(0.0);
    
    #if AA>1
    for( int m=0; m<AA; m++ )
    for( int n=0; n<AA; n++ )
    {
        // pixel coordinates
        vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
        vec2 p = (2.0*(gl_FragCoord.xy+o)-res.xy)/res.y;
        #else    
        vec2 p = (2.0*gl_FragCoord.xy-res.xy)/res.y;
        #endif

	    // create view ray
        vec3 rd = normalize( p.x*uu + p.y*vv + 1.5*ww );

        // raymarch
        const float tmax = 5.0;
        float t = 0.0;
        for( int i=0; i<256; i++ )
        {
            vec3 pos = ro + t*rd;
            float h = map(pos);
            if( h<0.0001 || t>tmax ) break;
            t += h;
        }
        
    
        // shading/lighting	
        vec3 col = vec3(0.0);
        if( t<tmax )
        {
            vec3 pos = ro + t*rd;
            vec3 nor = calcNormal(pos);
            float dif = clamp( dot(nor,vec3(0.57703)), 0.0, 1.0 );
            float amb = 0.5 + 0.5*dot(nor,vec3(0.0,1.0,0.0));
            col = vec3(0.2,0.3,0.4)*amb + vec3(0.8,0.7,0.5)*dif;
        }

        // gamma        
        col = sqrt( col );
	    tot += col;
    #if AA>1
    }
    tot /= float(AA*AA);
    #endif

	screenColor = vec4( tot, 1.0 );
  }
