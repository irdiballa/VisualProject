#include "Polynomial.h"

#include "glm/gtx/quaternion.hpp"
#include <iostream>


Polynomial::Polynomial()
{

	chartSize = 20.0f;
	initializeData();
	
	reset();
}

Polynomial::~Polynomial()
{

}

void Polynomial::initializeData() {

	int indicesIndex = 0;
	int currentVertex = 0;


	for (int y = 0; y < Y_VERTICES; y++) {
		float yCoord = y * (chartSize / (float)Y_VERTICES);
		for (int x = 0; x < X_VERTICES; x++) {
			float xCoord = float(x) * (chartSize / (float)X_VERTICES);

			posVector.push_back(xCoord - (chartSize / 2.0f));
			posVector.push_back(yCoord - (chartSize / 2.0f));
			posVector.push_back(glm::sin(xCoord + yCoord));

			if (x < X_VERTICES - 1 && y < Y_VERTICES - 1) {

				indices.push_back(currentVertex);
				indices.push_back(currentVertex + 1);
				indices.push_back(currentVertex + 1 + X_VERTICES);

				indices.push_back(currentVertex + 1 + X_VERTICES);
				indices.push_back(currentVertex + X_VERTICES);
				indices.push_back(currentVertex);
				indicesIndex += 6;
				
			}
			currentVertex++;
		}
	}

}

glm::mat4 Polynomial::getModelMatrix()
{
	glm::mat4 translationMX = glm::translate(glm::mat4(1.0f), centerPosition);
	glm::mat4 scalingMX = glm::scale(glm::mat4(1.0f), glm::vec3(scalingFactor));
	glm::mat4 rotationMX = glm::mat4(rotationQuat);

	glm::mat4 model = translationMX * rotationMX * scalingMX;

	return model;
}

void Polynomial::translate(glm::vec3 translationVector)
{
	centerPosition += translationVector;
}

void Polynomial::scale(bool positiveScale)
{
	scalingFactor = positiveScale ? 1.1f * scalingFactor : (1.0f / 1.1f) * scalingFactor;

	if (scalingFactor > 100)
		scalingFactor = 100;
	if (scalingFactor < 0.1)
		scalingFactor = 0.1;
}

void Polynomial::rotate(glm::vec3 axis, float angleInRads)
{
	axis = glm::rotate(glm::inverse(rotationQuat), axis);
	glm::quat newRot = glm::quat(glm::degrees(angleInRads), axis);
	rotationQuat = glm::rotate(rotationQuat, angleInRads, axis);
}

void Polynomial::reset()
{
	scalingFactor = 20;
	centerPosition = glm::vec3(0, 0, 0);
	rotationQuat = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}