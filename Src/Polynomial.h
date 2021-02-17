#pragma once
/*!
 * Class: Polynomial
 * Contains the information that are needed to render the polynomial function.
 *
 */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>

//increase for smoothness
const int X_VERTICES = 50;
const int Y_VERTICES = 50;

class Polynomial
{
public:
    Polynomial();
    ~Polynomial();

    //inline getter functions to return the data for the polynomial
    //getPositions - pointer to array of verticesv
    //getIndices - pointer to array of indices
    //getNumberOfIndices - count of indices
    //getNumberOfVertices - count of vertices
    //getModelMatrix - 3d transformation of the object
    inline float* getPositions() { return &posVector[0];}
    inline unsigned int* getIndices() { return &indices[0]; };
    const inline int getNumberOfIndices() const { return ((X_VERTICES - 1) * (Y_VERTICES - 1) * 2 * 3); };
    const inline int getNumberOfVertices() const { return (X_VERTICES * Y_VERTICES * 3); };
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

    std::vector<float> posVector;// = std::vector<float>(X_VERTICES * Y_VERTICES * 3);
    std::vector<unsigned int> indices;// = std::vector<unsigned int>((X_VERTICES - 1) * (Y_VERTICES - 1) * 2 * 3);

    float scalingFactor;
    glm::vec3 centerPosition;
    glm::quat rotationQuat;

    float chartSize;

    //initializeData : calculate vertices and indices to create mesh of triangles
    void initializeData();

};
