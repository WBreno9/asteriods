#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <gutils.h>

class Entity
{
public:
	static GLFWwindow* window;
	static float delta;
	static glm::vec2 playArea;
	
	bool isDead;
	float lifeTime;

	int health;
	int maxHealth;

	bool visible;

	std::vector<glm::vec2> vertices;

	glm::vec2 pos;
	glm::vec2 forward;
	float rotation;
	float size;

	float DeAccelMul;
	glm::vec2 accelDir;

	glm::vec2 BBoxMax;
	glm::vec2 BBoxMin;

	Entity();
	virtual ~Entity();

	static Entity* GetTail() { return tail; }
	static Entity* GetHead() { return head; }

	static void SetAllDead();
	static void ReapDeadEntities();
	static void UpdateAll();

	virtual std::string GetTypeString() = 0;

	virtual void Update() = 0;

	virtual void Damage(unsigned d);

	void Draw();
	void UpdateMatrix();
	void UpdateVectors();

	bool OutsideOfPlayArea(bool adjust);
	void CalculateBBox();
	bool TestBBoxCollision(Entity*);
	bool TestLineSegCollision(Entity*, glm::vec2&);

	Entity* FindByType(std::string);
	Entity* FindNearestByType(std::string);

 	Entity* GetNext() { return next; }
	Entity* GetPrev() { return prev; }

private:
	float realRotation;

	float lifeTimeCount;
	glm::mat4 model_matrix;

	Entity* prev;
	Entity* next;

	static Entity* tail;
	static Entity* head;  
	
	void DrawBoundingBox();
	static void DrawPlayArea();
};

#endif