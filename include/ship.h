#ifndef SHiP_H
#define SHiP_H

#include <entity.h>
#include <projectile.h>
#include <hbar.h>

class Ship : public Entity
{
public:
	Ship(); 
	~Ship();

	std::string GetTypeString() { return "Ship"; }

	void Update();
private:
	HBar* hbar;
	bool fire;
	void SetShipPoly();
};

#endif