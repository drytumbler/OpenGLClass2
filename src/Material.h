#include "config.h"

class Material{
    public:
        Material(const char* filename);
        ~Material();
        void use(int index);
    private:
    unsigned int texture;
};