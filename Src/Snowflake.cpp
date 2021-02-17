#include "Snowflake.h"
#include "glm/gtc/random.hpp"


Snowflake::Snowflake(float halfHeight, float halfWidth):hW(halfWidth),hH(halfHeight)
{
	moveSpeed = glm::linearRand(-2.0f, 0.0f);
	scaleFactor = glm::linearRand(19.0f, 21.0f);
	rotateSpeed = glm::linearRand(-0.1f, 0.1f);

	float startX = glm::linearRand(-hW, hW);
	float startY = glm::linearRand(hH,2.0f * hH);


	
	translation = glm::translate(glm::mat4(1.0f), glm::vec3(startX, startY, 0.0f));
	rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	
	scaling = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, 1.0f));

	outOfBounds = -hH - 11;
}

Snowflake::~Snowflake()
{
}

glm::mat4 Snowflake::getModel()
{

	translation = glm::translate(translation, glm::vec3(0, moveSpeed, 0));

	if (translation[3][1] < outOfBounds) {
		moveSpeed = glm::linearRand(-2.0f, 0.0f);
		scaleFactor = glm::linearRand(19.0f, 21.0f);
		rotateSpeed = glm::linearRand(-0.1f, 0.1f);

		float startX = glm::linearRand(-hW, hW);
		float startY = -outOfBounds;
		translation = glm::translate(glm::mat4(1.0f), glm::vec3(startX, startY, 0.0f));

	}
		

	rotation = glm::rotate(rotation, rotateSpeed, glm::vec3(0, 0, 1));

	glm::mat4 model = translation * rotation * scaling;



	return model;
}
