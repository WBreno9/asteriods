#include <target.h>

Target::Target(glm::vec2 a)
{
	pos = a;
	visible = true;
	rotation = 0.0f;

	SetTargetPoly();
	Update();
}

void Target::SetTargetPoly()
{
	vertices.push_back(glm::vec2(0.025f, 0.025f));
	vertices.push_back(glm::vec2(0.025f, -0.025f));
	vertices.push_back(glm::vec2(-0.025f, -0.025f));
	vertices.push_back(glm::vec2(-0.025f, 0.025f));
	vertices.push_back(vertices[0]);
}

void Target::Update()
{
	Entity* ent = FindByType("Ship");
	glm::vec2 p;
	if (TestLineSegCollision(ent, p)) {
		ent->isDead = true;
		isDead = true;
	}

	UpdateMatrix();
	UpdateVectors();
}
