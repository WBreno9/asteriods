#ifndef GAME_H
#define GAME_H

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

#include <entity.h>
#include <gutils.h>

#include <ship.h>
#include <target.h>

class Game 
{
public:
    Game();
    ~Game();

    void createWindow(unsigned w, unsigned h);

    void start();
    void restart();
private:
    GLFWwindow* window;
    float delta, currentTime, pastTime;

    void updateDelta();
    void mainLoop();
};

#endif