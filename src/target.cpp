#include <target.h>

unsigned Target::score = 0;

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

	dis = std::uniform_real_distribution<float>(0.6, 3.0);
	size = dis(rnd);

	maxHealth = std::ceil(size)*100;
	health = maxHealth;

	hbar = new HBar(glm::vec2(0.4f, 0.15f));
	hbar->size = 0.05f;
	hbar->visible = false;
	hbar->percent = 1.0f;

	SetTargetPoly();
	Update();
}

Target::~Target()
{
	hbar->isDead = true;
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
		ent->Damage(10);
		
		isDead = true;
	}

	if (rotation > 0) {
		rotation += 2 * delta;
	} else {
		rotation -= 2 * delta;
	}
	pos += movDir * delta * 0.25f;

	hbar->pos = pos + glm::vec2(0.0f, 0.04f * size);
	hbar->percent = health/100.0f;

	timer -= Entity::delta;
	if (timer <= 0.0f)
		hbar->visible = false;

	UpdateMatrix();
	UpdateVectors();
}

/* FIX: Function can cause seg faults */
void Target::Separate()
{
	if (size >= 1.2f) {
		Target* t1 = new Target(pos);
		Target* t2 = new Target(pos);

		t1->size = size/2.0f;
		t2->size = size/2.0f;	
		
		t1->health = std::ceil(t1->size)*100;
		t2->health = std::ceil(t2->size)*100;
	}
}

void Target::Damage(unsigned d)
{
	health -= d;

	hbar->visible = true;
	timer = 1.0f;

	if (health <= 0) {
		Separate();
		isDead = true;

		score += std::ceil(size) * 5;
	}
}
