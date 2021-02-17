#include "Cube.h"

#include "glm/gtx/quaternion.hpp"

Cube::Cube()
{
	reset();
}

Cube::~Cube()
{
	
}

glm::mat4 Cube::getModelMatrix()
{
	glm::mat4 translationMX = glm::translate(glm::mat4(1.0f), centerPosition);
	glm::mat4 scalingMX = glm::scale(glm::mat4(1.0f), glm::vec3(scalingFactor));
	glm::mat4 rotationMX = glm::mat4(rotationQuat);

	glm::mat4 model = translationMX * rotationMX * scalingMX;

	return model;
}

void Cube::translate(glm::vec3 translationVector)
{
	centerPosition += translationVector;
}

void Cube::scale(bool positiveScale)
{
	scalingFactor = positiveScale ? 1.1f * scalingFactor : (1.0f / 1.1f) * scalingFactor;

	if (scalingFactor > 500)
		scalingFactor = 500;
	if (scalingFactor < 0.1)
		scalingFactor = 0.1;
}

void Cube::rotate(glm::vec3 axis, float angleInRads)
{
	axis = glm::rotate(glm::inverse(rotationQuat), axis);
	glm::quat newRot = glm::quat(glm::degrees(angleInRads), axis);
	rotationQuat = glm::rotate(rotationQuat, angleInRads, axis); 
}

void Cube::reset()
{
	scalingFactor = 20;
	centerPosition = glm::vec3(0, 0, 0);
	rotationQuat = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
