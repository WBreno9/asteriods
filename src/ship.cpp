#include <ship.h>

Ship::Ship()
{
	pos = glm::vec2(0.0f);
	forward = glm::vec2(0.0f, 1.0f);
	accelDir = glm::vec2(0.0f);
	size = 1.0f;
	
	rotation = 0.0f;
	SetShipPoly();
	CalculateBBox();
	visible = true;
}

void Ship::SetShipPoly()
{
	vertices.push_back(glm::vec2(0.0f, 0.05f));
	vertices.push_back(glm::vec2(-0.04f, -0.05f));
	vertices.push_back(glm::vec2(0.0f, -0.02f));
	vertices.push_back(glm::vec2(0.04f, -0.05f));
	vertices.push_back(vertices[0]);
}

void Ship::Update()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		accelDir += forward * 1.5f * delta;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		accelDir -= forward * 1.5f * delta;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		rotation -= -5.0f * delta;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		rotation += -5.0f * delta;

	if (glm::length(accelDir) > 0.05f)
		accelDir -= accelDir * (1.0f * delta);

	pos += accelDir * delta;

	UpdateMatrix();
	UpdateVectors();

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (fire) {
			glm::vec2 muzzle = pos + (forward * 0.07f);
			new Projectile(muzzle, rotation);
			fire = false;
		}
	} else {
		fire = true;
	}
}