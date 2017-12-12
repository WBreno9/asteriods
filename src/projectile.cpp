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
	if (OutsideOfPlayArea(false))
		isDead = true;
	
	Entity* ent = FindNearestByType("Target");
	if (TestBBoxCollision(ent)) {
		ent->Damage(200);

		isDead = true;
		
		return;
	}
	pos += forward * 3.0f * delta;
	UpdateMatrix();
	UpdateVectors();
}