#include <entity.h>

namespace {
	bool line_seg_debug = false;
	bool debug_bb = false;
	bool debug_play_area = false;
}

Entity* Entity::tail = nullptr;
Entity* Entity::head = nullptr;
GLFWwindow* Entity::window = nullptr;
float Entity::delta = 0;
glm::vec2 Entity::playArea = glm::vec2(1.0f);

Entity::Entity() 
{
	lifeTime = 0.0f;
	lifeTimeCount = 0.0f;
	isDead = false;

	if (head == nullptr) {
		tail = head = this;
		next = prev = nullptr;
	} else {
		tail->next = this;
		prev = tail;
		tail = this;
		next = nullptr;
	}
}

Entity::~Entity()
{
	if (next != nullptr)
		next->prev = prev;
	if (prev != nullptr)
		prev->next = next;
	if (this == tail)
		tail = prev;
	if (this == head)
		head = next;
}

void Entity::SetAllDead()
{
	for (Entity* ent = Entity::GetHead(); ent != nullptr;
		ent = ent->GetNext()) 
			ent->isDead = true;
}

void Entity::ReapDeadEntities()
{
	Entity* ent = head;
	Entity* tmp;

	while (ent != nullptr) {
		tmp = ent->next;

		if (ent->isDead)
			delete ent;

		ent = tmp;
	}
}

void Entity::UpdateAll()
{
	for (Entity* ent = Entity::GetHead(); ent != nullptr;
		ent = ent->GetNext()) 
	{	
		if (ent->lifeTime > 0.0f) {	
			ent->lifeTimeCount += delta;

			if (ent->lifeTimeCount > ent->lifeTime) 
				ent->isDead = true;
		}

		ent->CalculateBBox();
		if (debug_bb) ent->DrawBoundingBox();

		ent->OutsideOfPlayArea(true);
		if (debug_play_area) DrawPlayArea();

		ent->Update();
	}
	ReapDeadEntities();

	for (Entity* ent = Entity::GetHead(); ent != nullptr;
		ent = ent->GetNext()) 
		ent->Draw();
}

void Entity::UpdateMatrix()
{
	model_matrix = glm::translate(glm::mat4(1.0f), 
					glm::vec3(pos, 0.0f));
	model_matrix = glm::rotate(model_matrix, rotation, 
					glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(size));
}

void Entity::UpdateVectors()
{
	glm::vec4 temp = glm::rotate(glm::mat4(1.0f),
					rotation,
					glm::vec3(0.0f, 0.0f, 1.0f)) *
		 glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	forward = glm::vec2(temp.x, temp.y);
}


void Entity::Draw()
{	
	if (!visible)
		return;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(model_matrix));
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < vertices.size(); i++) 
		glVertex3f(vertices[i].x, vertices[i].y, 0.0f);

	glEnd();

	glLoadIdentity();

	if (line_seg_debug)
		GUtils::drawLineSegDebug();
}

void Entity::Damage(unsigned d)
{
	health -= d;

	if (health <= 0) 
		isDead = true;
}

void Entity::CalculateBBox()
{
	if (vertices.empty())
		return;

	glm::vec2 bbma(0.0f);
	glm::vec2 bbmi(0.0f);
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec4 temp = model_matrix * 
				glm::vec4(vertices[i], 0.0f, 0.0f);

		if (temp.x >= bbma.x)
			bbma.x = temp.x;
		if (temp.y >= bbma.y)
			bbma.y = temp.y;

		if (temp.x <= bbmi.x)
			bbmi.x = temp.x;
		if (temp.y <= bbmi.y)
			bbmi.y = temp.y;
	}

	BBoxMax = bbma;
	BBoxMin = bbmi;
}

bool Entity::OutsideOfPlayArea(bool adjust)
{
	if (BBoxMin.x + pos.x > playArea.x) {	
		if (adjust) pos.x = -(BBoxMin.x + pos.x + BBoxMax.x);
	} else if (BBoxMax.x + pos.x < -playArea.x) {	
		if (adjust) pos.x = -(BBoxMax.x + pos.x + BBoxMin.x);
	} else if (BBoxMin.y + pos.y > playArea.y) {	
		if (adjust) pos.y = -(BBoxMin.y + pos.y + BBoxMax.y);
	} else if (BBoxMax.y + pos.y < -playArea.y) {	
		if (adjust) pos.y = -(BBoxMax.y + pos.y + BBoxMin.y);
	} else {
		return false;
	}

	return true;
	
}

bool Entity::TestBBoxCollision(Entity* ent)
{
	if (ent == nullptr)
		return false;

	if ((BBoxMax.x + pos.x >= ent->BBoxMin.x + ent->pos.x) &&
		(BBoxMin.x + pos.x <= ent->BBoxMax.x + ent->pos.x) &&
		(BBoxMin.y + pos.y <= ent->BBoxMax.x + ent->pos.y) &&
		(BBoxMax.y + pos.y >= ent->BBoxMin.x + ent->pos.y))
		return true;

	return false;
}

bool Entity::TestLineSegCollision(Entity* ent, glm::vec2& p)
{
	if (!TestBBoxCollision(ent) || vertices.empty() || 
						ent->vertices.empty())
		return false;


	/* TODO */
	/* Fix line segment intersection */

	glm::vec2 p1, p2, q1, q2;
	for (int i = 0; i < vertices.size() - 1; i++) {

		p1 = glm::rotate(vertices[i] * size, rotation) + pos;
		p2 = glm::rotate(vertices[i+1] * size, rotation) + pos;

		for (int j = 0; j < ent->vertices.size() - 1; j++) {

			q1 = glm::rotate(ent->vertices[j], ent->rotation) 
							+ ent->pos;
			q2 = glm::rotate(ent->vertices[j+1], ent->rotation)
							+ ent->pos;

			if (GUtils::lineSegIntersection(p1, p2, q1, q2, p))
				return true;
		}

	}

	return false;
}				

Entity* Entity::FindByType(std::string arg)
{
	for (Entity* ent = Entity::GetHead(); ent != nullptr;
		ent = ent->GetNext()) 
	{
		if (ent->GetTypeString() == arg && ent != this)
			return ent;
	}

	return nullptr;
}
	
Entity* Entity::FindNearestByType(std::string arg)
{
	float tmp, dist = -1.0f;
	Entity* nearest = nullptr;
	for (Entity* ent = Entity::GetHead(); ent != nullptr;
		ent = ent->GetNext()) 
	{
		if (ent->GetTypeString() == arg) {
			if (dist < 0.0f) {
				dist = glm::distance(pos, ent->pos);
				nearest = ent;
			}

			if ((tmp = glm::distance(pos, ent->pos)) < dist) {
				dist = tmp;
				nearest = ent;
			}
		}
	}

	return nearest;
}

void Entity::DrawBoundingBox()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(BBoxMax.x + pos.x, BBoxMax.y + pos.y, 0.0f);
	glVertex3f(BBoxMax.x + pos.x, BBoxMin.y + pos.y, 0.0f);
	glVertex3f(BBoxMin.x + pos.x, BBoxMin.y + pos.y, 0.0f);
	glVertex3f(BBoxMin.x + pos.x, BBoxMax.y + pos.y, 0.0f);
	glEnd();
}

void Entity::DrawPlayArea()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(playArea.x, playArea.y, 0.0f);
	glVertex3f(playArea.x, -playArea.y, 0.0f);
	glVertex3f(-playArea.x, -playArea.y, 0.0f);
	glVertex3f(-playArea.x, playArea.y, 0.0f);
	glEnd();
}