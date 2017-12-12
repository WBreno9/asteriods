#include <game.h>

static void error_callback(int error, const char* desc)
{
	std::cout << desc << std::endl;
}

Game::Game() {
	window = nullptr;
}

Game::~Game() {
	Entity::SetAllDead();
	Entity::ReapDeadEntities();

    glfwDestroyWindow(window);
	glfwTerminate();
}

void Game::createWindow(unsigned w, unsigned h)
{
    glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_FLOATING, GL_FALSE);

	window = glfwCreateWindow(w, h, "DIS", 
							nullptr, nullptr);
		
	Entity::window = window;
	
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(error_callback);
	
	glfwSwapInterval(0);
}

void Game::start()
{
    if (window == nullptr) {
        std::cerr << "Failed to start game: no window" << std::endl;
        return;
    }

    delta = 0;
    pastTime = 0;
	currentTime = 0;

	Entity::playArea = glm::vec2(1.0f, 0.7f);
	
	restart();
    mainLoop();
}

void Game::updateDelta()
{
    currentTime = (float)glfwGetTime();
    delta = currentTime - pastTime;
	pastTime = currentTime;
	
	Entity::delta = delta;
}

void Game::restart()
{
	Entity::SetAllDead();
	Entity::ReapDeadEntities();

	new Ship();

	std::srand((int)(glfwGetTime() * 1000));
	for (int i = 0; i < 20; i++) {
		new Target(glm::vec2((std::rand() % 2666 - 1333) / (float)1000.0f, 
			(std::rand() % 1800 - 900) / (float)1000.0f));
	}
}

void Game::mainLoop()
{	
	float currentTime, pastTime;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	
		updateDelta();
	
		int height, width;
		glfwGetFramebufferSize(window, &width, &height);
		float ratio = width / (float)height;	

		Entity::playArea = glm::vec2(ratio, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width, height);		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	
		Entity::UpdateAll();
	
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			restart();
	
		
		glfwSwapBuffers(window);
		glfwSetWindowTitle(window, 
			std::to_string(1.0f / delta).c_str());
	
		}
}