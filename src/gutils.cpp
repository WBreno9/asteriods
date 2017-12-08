#include <gutils.h>

void GUtils::drawLineSegDebug()
{
	glm::vec2 temp, temp2;

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);

	temp = p1_debug + (p1_debug - p2_debug) * 100.0f;
	temp2 = p2_debug + (p2_debug - p1_debug) * 100.0f;

	glVertex3f(temp.x, temp.y, 0.0f);
	glVertex3f(temp2.x, temp2.y, 0.0f);

	temp = q1_debug + (q1_debug - q2_debug) * 100.0f;
	temp2 = q2_debug + (q2_debug - q1_debug) * 100.0f;

	glVertex3f(temp.x, temp.y, 0.0f);
	glVertex3f(temp2.x, temp2.y, 0.0f);

	glLineWidth(2);

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(p1_debug.x, p1_debug.y, 0.0f);
	glVertex3f(p2_debug.x, p2_debug.y, 0.0f);
	glVertex3f(q1_debug.x, q1_debug.y, 0.0f);
	glVertex3f(q2_debug.x, q2_debug.y, 0.0f);

	glLineWidth(1);

	glEnd();

	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(res_debug.x, res_debug.y, 0.0f);
	glEnd();
	glPointSize(1);
}

bool GUtils::lineSegIntersection(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1,
				glm::vec2 q2, glm::vec2& res)
{
	glm::vec2 r = p2 - p1;
	glm::vec2 s = q2 - q1;

	glm::vec2 qmp = q1 - p1;
	float qmpxs = (qmp.x * s.y) - (qmp.y * s.x);
	float rxs = (r.x * s.y) - (r.y * s.x);

	if (rxs == 0.0f)
		return false;

	if ((qmpxs == 0.0f) && (rxs == 0.0f)) {

		if (p1 == q1) {
			res = p1;
			return true; 
		} else if (p1 == q2) {
			res = p1;
			return true; 
		} else if (p2 == q1) {
			res = p2;
			return true; 
		} else if (p2 == q2) {
			res = p2;
			return true; 
		} else {
			return false;
		}

		if (((q1.x - p1.x < 0) != (q1.x - p2.x < 0)) &&
			((q2.x - p1.x < 0) != (q2.x - p2.x < 0)) &&
			((q1.y - p1.y < 0) != (q1.y - p2.y < 0)) &&
			((q2.y - p1.y < 0) != (q2.y - p2.y < 0))) {
			
			res = (p1 + p2 + q1 + q2) / 4.0f;
			return true;
		}
	}	

	float qmpxr = (qmp.x * r.y) - (qmp.y * r.x);
	float t  = qmpxs / rxs;
	float u  = qmpxr / rxs;

	if ((t >= 0.0f) && (t <= 1.0f) && (u >= 0.0f) && (u <= 1.0f)) {
		res = p1 + (t * r);

		p1_debug = p1;
		p2_debug = p2;
		q1_debug = q1;
		q2_debug = q2;
		res_debug = res;

		return true;
	}

	return false;
}
