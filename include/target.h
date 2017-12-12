#ifndef TARGET_H
#define TARGET_H

#include <entity.h>
#include <ship.h>
#include <hbar.h>

class Target : public Entity
{
public:
	static unsigned score;
	glm::vec2 movDir;
	
	Target(glm::vec2 a);
	~Target();
	
	std::string GetTypeString() { return "Target"; }

	void Update();
	void Damage(unsigned d);
	void Separate();
private:
	HBar* hbar;

	float timer;

	void SetTargetPoly();
};

#endif