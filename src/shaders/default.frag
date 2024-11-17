#version 330 core

#define SHARPNESS 0.005
#define ITERATIONS 128
#define MIN_DIST 0.005
#define MAX_DIST 500.0
#define MAX_SHADOW_DIST 100.0

#define UP             vec3( 0.0, 1.0, 0.0 ) 


in vec3 fragmentColor;
in vec2 fragmentTexCoord;

in vec3 vertexNormal;
in vec3 crntPos;

out vec4 screenColor;

uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;
uniform sampler2D sandstone1;
uniform sampler2D sandstone2;
uniform sampler2D sandstone3;

uniform float scale;
uniform float time;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform vec3 camDir;

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
  vec3 ro = camPos;
  vec3 rd = camDir;
  vec3 ri = normalize(cross(camDir, UP));
  vec2 result = vec2( 0.0 );
  
  vec3 spherePos = vec3( 1.77 * sin( time * 0.5 + 0.5), 0.0, 0.0 );
  spherePos = flip(spherePos);
  float c = sdSphere(p*vec3(1.3,1.0,1.4), spherePos, 0.35 + (0.1 * (1.0 + sin(time))));


  vec3 boxDim = vec3(0.65);
  float b = sdBox(p, boxDim); 

  float v = sdPlane(p, vec3(0., 1., 0.), .5);
  float v2 = sdPlane(p, vec3(0., -1., 0.), 50.5);
  

  vec3 lhandPos = ro + rd * .5 + ri * .3 - UP * .25;
  vec3 rhandPos = ro + rd * .5 - ri * .3 - UP * .25;
  float lh = sdSphere(p, lhandPos, .1);
  float rh = sdSphere(p, rhandPos, .1);

  result.x = min(smin(.7 * c, b, 1.05), v );
  result.x = min(smin(.7 * c, b, 1.05), v );
  result.x = min(result.x, v2);
  result.x = min(result.x, lh);
  result.x = min(result.x, rh);
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
  if( d.x < length( posl - pos ) && d.x < MAX_SHADOW_DIST) dif *= 0.7; // shadows
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

    int n = 0;

void main() {
    vec2 newTex = fragmentTexCoord - vec2(0.,0.12);
    newTex *= 2.;
    vec3 baseColor = texture(sandstone1, newTex).rgb;
    float alpha = texture(mask, fragmentTexCoord).a;

    vec3 flatColor = texture(sandstone, newTex).rgb;

    // Calculate the light direction
    vec3 roughness = texture(sandstone2, newTex).rgb;
    vec3 normal = texture(sandstone3, newTex).rgb;
    vec3 toLight = normalize(lightPos - crntPos);

    vec2 t = ray(camPos, toLight);
    vec3 pos = camPos + camDir * t.x;
    float d = dlight(pos, lightPos);
    
    float diff = max(dot(vertexNormal, toLight), 0.0);
    /*
    if (fract(time*.1) > 0.25)
      diff = max(dot(vertexNormal, toLight * roughness), 0.0);
    if (fract(time*.1) > 0.5)
      diff = max(dot(vertexNormal * normal, toLight), 0.0);
    if (fract(time*.1) > 0.75)
    */
    diff = max(dot(vertexNormal * normal, toLight), 0.0);
    float diff0 = max(dot(vertexNormal, toLight), 0.0);

        
    // Ambient light
    float ambientStrength = 0.70;
    vec3 ambient = ambientStrength * lightColor.rgb;
    vec3 finalColor = baseColor * (ambient + (1.0 - ambientStrength) * diff*roughness.g);
    // Calculate the final color
    
      //if (fract(time*.1) > 0.5)
      //finalColor = baseColor * (ambient + (diff*roughness.r));
    

    //finalColor = vec3(t.x * 0.2) * diff;
    // Final output color
    //screenColor = vec4(baseColor * (ambient + diff), (1.0 - alpha) * (0.75 - alpha));
    screenColor = vec4(vec3(finalColor), 1.);
    // if(fract(0.1 * time) > 0.5 )
    //screenColor = vec4(vec3(flatColor) * (ambient + diff0), 1.);
}
