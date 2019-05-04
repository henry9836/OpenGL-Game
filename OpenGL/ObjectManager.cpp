#include "ObjectManager.h"

Input input1;

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Reset()
{
	objPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void ObjectManager::movement(AudioSystem& audio2, GLfloat deltaTime, float screenW, float screenH, bool isEnemy)
{
	glm::vec3 temp;
	temp = objPos;
	if (!isEnemy) {
		if (input1.CheckKeyDown('w') == true)
		{

			if (temp.y < ((screenH - 100) / 2))
			{
				temp.y += speedBaby * deltaTime;
				objPos = temp;
			}

		}
		if (input1.CheckKeyDown('a') == true)
		{
			if (temp.x > (0 - ((screenW + 240) / 2)))
			{
				temp.x -= speedBaby * deltaTime;
				objPos = temp;
			}
		}
		if (input1.CheckKeyDown('s') == true)
		{
			if (temp.y > (0 - ((screenH - 100) / 2)))
			{
				temp.y -= speedBaby * deltaTime;
				objPos = temp;
			}
		}
		if (input1.CheckKeyDown('d') == true)
		{
			if (temp.x < ((screenW - 450) / 2))
			{
				temp.x += speedBaby * deltaTime;
				objPos = temp;
			}
		}
	}
	else {
		if (objPos.x > (Target.x + 151)) {
			objPos.x -= speedFire * deltaTime;
			//go left
		}
		else if (objPos.x < (Target.x + 149)) {
			objPos.x += speedFire * deltaTime;
			//go right
		}
		if (objPos.y > Target.y) {
			objPos.y -= speedFire * deltaTime;
			//go down
		}
		else if (objPos.y < Target.y) {
			objPos.y += speedFire * deltaTime;
			//go up
		}
	}
}



