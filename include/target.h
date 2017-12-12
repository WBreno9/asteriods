#ifndef TARGET_H
#define TARGET_H

#include <entity.h>

class Target : public Entity
{
public:
	glm::vec2 movDir;
	
	Target(glm::vec2 a);
	
	std::string GetTypeString() { return "Target"; }

	void Update();
private:
	void SetTargetPoly();
};

#endif