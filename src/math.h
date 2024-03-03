#include <cmath>


struct mat4{
    float entries[16];
};

struct vec3{
    float entries[3];
};

mat4 Translate(vec3 translation);
mat4 RotateZ(float angle);
mat4 TranslateRotZ(vec3 translation, float angle);
mat4 Viewpoint(vec3 from, vec3 to);
mat4 Project(float fovy, float aspect, float near, float far);

float dot(vec3 u, vec3 v);
vec3 cross(vec3 u, vec3 v);
vec3 normalize(vec3 v);

