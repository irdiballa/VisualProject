#pragma once

/*!
 * Class: Snowflake
 * Contains the information that are needed to render the snowflakes.
 *
 */

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Snowflake
{
public:
	//halfHeight is window height/2, halfWidth is window width/2
	Snowflake(float halfHeight, float halfWidth);
	~Snowflake();

	//getModel - 3d transformation of the object
	glm::mat4 getModel();


private:
	glm::mat4 translation, rotation, scaling;
	float moveSpeed, rotateSpeed, scaleFactor;
	float hW, hH; //halfWidth and halfheight 

	float outOfBounds; //to check if snowflake went outside the screen

};
