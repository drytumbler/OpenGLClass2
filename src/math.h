#include <cmath>

#define PI 3.14159627
struct mat4{
    float entries[16];
};

struct vec3{
    float entries[3];
};

mat4 Translate(vec3 translation);
mat4 RotateZ(float angle);
mat4 TranslateRotZ(vec3 translation, float angle);