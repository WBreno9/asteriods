#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <game.h>

int main(int argc, char** argv)
{
	Game game;
	game.createWindow(800, 600);
	game.start();

	return 0;
}
