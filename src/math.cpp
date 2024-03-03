#include "math.h"

mat4 Translate(vec3 translation)
{
    mat4 matrix;

    matrix.entries[0] = 1.0f;
    matrix.entries[1] = 0.0f;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = 0.0f;
    matrix.entries[5] = 1.0f;
    matrix.entries[6] = 0.0f;
    matrix.entries[7] = 0.0f;
    
    matrix.entries[8]  = 0.0f;
    matrix.entries[9]  = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = translation.entries[0];
    matrix.entries[13] = translation.entries[1];
    matrix.entries[14] = translation.entries[2];
    matrix.entries[15] = 1.0f;

    return matrix;
}

mat4 RotateZ(float angle)
{
    mat4 matrix;

    float c = cosf(angle);
    float s = sinf(angle);

    matrix.entries[0] = c;
    matrix.entries[1] = s;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = -s;
    matrix.entries[5] =  c;
    matrix.entries[6] =  0.0f;
    matrix.entries[7] =  0.0f;
    
    matrix.entries[8]  = 0.0f;
    matrix.entries[9]  = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = 0.0f;
    matrix.entries[13] = 0.0f;
    matrix.entries[14] = 0.0f;
    matrix.entries[15] = 1.0f;


    return matrix;
}

mat4 TranslateRotZ(vec3 translation, float angle)
{
    mat4 matrix;

    float c = cosf(angle);
    float s = sinf(angle);

    matrix.entries[0] = c;
    matrix.entries[1] = s;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = -s;
    matrix.entries[5] =  c;
    matrix.entries[6] =  0.0f;
    matrix.entries[7] =  0.0f;
    
    matrix.entries[8]  = 0.0f;
    matrix.entries[9]  = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = translation.entries[0];
    matrix.entries[13] = translation.entries[1];
    matrix.entries[14] = translation.entries[2];
    matrix.entries[15] = 1.0f;

    return matrix;
}

mat4 Viewpoint(vec3 from, vec3 to)
{
//https://www.youtube.com/watch?v=g41jbelCGwg&list=PLn3eTxaOtL2PHxN8EHf-ktAcN-sGETKfw&index=8
    vec3 globalUp = {0.0f, 0.0f, 1.0f};

    vec3 f {
        to.entries[0] - from.entries[0],
        to.entries[1] - from.entries[1],
        to.entries[2] - from.entries[2]
    };
    f = normalize(f);

    vec3 r = normalize(cross(f, globalUp));
    vec3 u = normalize(cross(r,f));

    mat4 matrix;

    matrix.entries[0] =   r.entries[0];
    matrix.entries[1] =   u.entries[0];
    matrix.entries[2] = - f.entries[0]; //flip forward axis
    matrix.entries[3] =   0.0f;

    matrix.entries[4] =   r.entries[1];
    matrix.entries[5] =   u.entries[1];
    matrix.entries[6] = - f.entries[1];
    matrix.entries[7] =   0.0f;
    
    matrix.entries[8]  =   r.entries[2];
    matrix.entries[9]  =   u.entries[2];
    matrix.entries[10] = - f.entries[2];
    matrix.entries[11] =   0.0f;

    matrix.entries[12] = - dot(r, from);
    matrix.entries[13] = - dot(u, from);
    matrix.entries[14] =   dot(f, from);
    matrix.entries[15] =   1.0f;

    return matrix;
}

mat4 Project(float fov, float aspect, float far, float near)
{
    fov *= .5f;
    float t = tanf(fov);
    near *= -1; //forward is mirrored
    far *= -1;
    mat4 result;
    for (int i = 0; i < 16; i++){
        result.entries[i] = 0.0f;
    }
    result.entries[0] = 1.0f / (aspect / t);
    result.entries[5] = 1.0f / t;
    result.entries[10] = - (near + far) / (near - far);
    result.entries[11] = -1.0f; //flip forward 
    result.entries[14] = 2 * near * far / (near - far);
     
    return result;
}

float dot(vec3 u, vec3 v)
{
    return  u.entries[0] * v.entries[0] + 
            u.entries[1] * v.entries[1] + 
            u.entries[2] * v.entries[2];
}

vec3 cross(vec3 u, vec3 v)
{
    vec3 result;

    result.entries[0] =    u.entries[1] * v.entries[2] - u.entries[2] * v.entries[1];
    result.entries[1] = - (u.entries[0] * v.entries[2] - u.entries[2] * v.entries[0]);
    result.entries[2] =    u.entries[0] * v.entries[1] - u.entries[1] * v.entries[0];

    return result;
}

vec3 normalize(vec3 v)
{
    vec3 result;
    float magnitude = sqrt(dot(v, v));
    
    result.entries[0] = v.entries[0] / magnitude;    
    result.entries[1] = v.entries[1] / magnitude;    
    result.entries[2] = v.entries[2] / magnitude;

    return result;
}
