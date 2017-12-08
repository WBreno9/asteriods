#include <projectile.h>

void Projectile::SetProjPoly()
{
	vertices.push_back(glm::vec2(0.0f, 0.01f));
	vertices.push_back(glm::vec2(-0.01f, -0.01f));
	vertices.push_back(glm::vec2(0.01f, -0.01f));
	vertices.push_back(vertices[0]);
}

void Projectile::Update()
{
	Entity* ent = FindNearestByType("Target");
	glm::vec2 k;
	if (TestLineSegCollision(ent, k)) {
		ent->isDead = true;
		isDead = true;
		
		return;
	}
	pos += forward * 3.0f * delta;
	UpdateMatrix();
	UpdateVectors();
}