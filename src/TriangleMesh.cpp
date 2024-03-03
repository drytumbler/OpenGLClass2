#include "TriangleMesh.h"

TriangleMesh::TriangleMesh() {
    
    std::vector<float> vertices = {
        -1.0f, -1.0f, 0.0f,         // x, y, z
         1.0f, -1.0f, 0.0f,         //colors moved to shader
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    std::vector<unsigned int> colorIndices = {
        0, 1, 2, 3
    };

    std::vector<unsigned int> positionIndices = {
        0, 1, 2, 3, 1, 2
    };
    vertex_count = 6;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VBOs.resize(2); //sets the size of a vector

    glGenBuffers(2, VBOs.data()); //.data() returns pointer to data start

    //position (as vec3 VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(
            GL_ARRAY_BUFFER, 
            vertices.size() * sizeof(float),  
            vertices.data(), 
            GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,                      //index
        3,                      //#elements (float, vec2, vec3 ...)
        GL_FLOAT,               //data type elements
        GL_FALSE,               //normalize?
        3 * sizeof(float),      //vertex stride
        (void*)0);              //attribute start

    glEnableVertexAttribArray(0); //index

    //color (as int VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(
            GL_ARRAY_BUFFER, 
            colorIndices.size() * sizeof(unsigned int),  
            colorIndices.data(), 
            GL_STATIC_DRAW
    );
    glVertexAttribIPointer(
        1,
        1, 
        GL_UNSIGNED_INT, 
        1 * sizeof(unsigned int), 
        (void*)0);

    glEnableVertexAttribArray(1);

    //indexbuffer (as IBO)
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, 
            positionIndices.size() * sizeof(unsigned int),  
            positionIndices.data(), 
            GL_STATIC_DRAW
    );
    //no attributes to set here..

}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, vertex_count);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs.data());
    glDeleteBuffers(1, &IBO);
}