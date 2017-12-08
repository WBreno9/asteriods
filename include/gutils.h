#ifndef GUTILS_H
#define GUTILS_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace {
	glm::vec2 p1_debug , p2_debug, q1_debug, q2_debug, res_debug;
}

namespace GUtils {
	void drawLineSegDebug();
	bool lineSegIntersection(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1,
				glm::vec2 q2, glm::vec2& res);
}

#endif 