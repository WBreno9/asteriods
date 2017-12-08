#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <entity.h>

class Projectile : public Entity
{
public:
	Projectile(glm::vec2 a, float b)
	{
		pos = a;
		rotation = b;	
		visible = true;
		lifeTime = 1.0f;

		SetProjPoly();
		CalculateBBox();
		Update();
	}

	std::string GetTypeString() { return "Projectile"; }
	
	void Update();
private:
	void SetProjPoly();
};

#endif