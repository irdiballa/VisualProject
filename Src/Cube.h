#pragma once

/*!
 * Class: Cube
 * Contains the information that are needed to render the cube.
 *
 */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

const int NR_INDICES = 36;
const int NR_VERTICES = 24;

class Cube
{
public:

	Cube();
	~Cube();

    //inline getter functions to return the data for the cube
    //getPositions - pointer to array of verticesv
    //getIndices - pointer to array of indices
    //getNumberOfIndices - count of indices
    //getNumberOfVertices - count of vertices
    //getModelMatrix - 3d transformation of the object
    inline float *getPositions() { return positions; };
    inline unsigned int* getIndices() { return indices; };
    const inline int getNumberOfIndices() const { return NR_INDICES; };
    const inline int getNumberOfVertices() const { return NR_VERTICES; };
    glm::mat4 getModelMatrix();

    //translate : move the object by translation vector
    void translate(glm::vec3 translationVector);
    //scale : enlarge the object for positiveScale == true, shrink otherwise
    void scale(bool positiveScale);
    //rotate : rotate the object angleInRads around axis
    void rotate(glm::vec3 axis, float angleInRads);

    // reset : reset all data to initial values
    void reset();


private:

    float positions[NR_VERTICES] = {
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    };
    unsigned int indices[NR_INDICES] = {
        0, 1, 2, //FRONT
        2, 3, 0, //FRONT
        7, 1, 5, //RIGHT
        1, 2, 5, //RIGHT
        6, 4, 3, //LEFT
        3, 0, 6, //LEFT
        6, 7, 1, //BOTTOM
        1, 0, 6, //BOTTOM
        7, 6, 4, //BACK
        4, 5, 7, //BACK
        2, 5, 3, //TOP
        5, 4, 3  //TOP
    };

    float scalingFactor;
    glm::vec3 centerPosition;
    glm::quat rotationQuat;

};

