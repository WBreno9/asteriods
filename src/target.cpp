#include <target.h>

Target::Target(glm::vec2 a)
{
	pos = a;
	visible = true;

	std::mt19937 rnd(std::random_device{}());
	std::uniform_real_distribution<float> dis(-1.0, 1.0);

	rotation = dis(rnd);

	movDir.x = dis(rnd);
	movDir.y = dis(rnd);

	movDir = glm::normalize(movDir);

	dis = std::uniform_real_distribution<float>(0.75, 2.0);
	size = dis(rnd);

	SetTargetPoly();
	Update();
}

void Target::SetTargetPoly()
{
	vertices.push_back(glm::vec2(0.0f, 0.5f) * 0.025f);
	vertices.push_back(glm::vec2(0.317784f, 0.868369f) * 0.025f);
	vertices.push_back(glm::vec2(0.707107f, 0.707107f) * 0.025f);
	vertices.push_back(glm::vec2(1.0f, 0.0f) * 0.025f);
	vertices.push_back(glm::vec2(0.707107f, -0.707107f) * 0.025f);
	vertices.push_back(glm::vec2(0.0f, -1.0f) * 0.025f);
	vertices.push_back(glm::vec2(-0.707107f, -0.707107f) * 0.025f);
	vertices.push_back(glm::vec2(-1.0f, 0.0f) * 0.025f);
	vertices.push_back(glm::vec2(-0.707107f, 0.707107f) * 0.025f);
	vertices.push_back(glm::vec2(-0.317784f, 0.868369f) * 0.025f);
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

	if (rotation > 0) {
		rotation += 2 * delta;
	} else {
		rotation -= 2 * delta;
	}
	pos += movDir * delta * 0.25f;

	UpdateMatrix();
	UpdateVectors();
}
