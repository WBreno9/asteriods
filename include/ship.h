#ifndef SHiP_H
#define SHiP_H

#include <entity.h>
#include <projectile.h>

class Ship : public Entity
{
public:
	Ship(); 

	std::string GetTypeString() { return "Ship"; }

	void Update();
private:
	bool fire;
	void SetShipPoly();
};

#endif