#include "Window.h"

GLboolean ICE::Window::keys[1024];
ICE::KeyCallbackFunction ICE::Window::customKeyCallback;
ICE::CursorPosCallbackFunction ICE::Window::customCursorPosCallback;
ICE::MouseBtnCallbackFunction ICE::Window::customMouseBtnCallback;
GLboolean ICE::Window::keyCallbackIsSet = false;
GLboolean ICE::Window::cursorPosCallbackIsSet = false;
GLboolean ICE::Window::mouseBtnCallbackIsSet = false;

ICE::Window::Window(std::string title, GLuint width, GLuint height) {
	this->title = title;
	this->width = width;
	this->height = height;

	if (!initGLFW()) return;

	// Set OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	if (!initGLEW()) return;

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseBtnCallback);
}

void ICE::Window::swapBuffers() {
	glfwSwapBuffers(window);
}

void ICE::Window::update() {
	if (displayFPS) {
		GLuint fps = (1.0f / deltaTime);
		std::string text = "FPS " + std::to_string(fps);
		glm::vec3 dimensions = TextRenderer::calcDimensions(text, 0.3f);
		TextRenderer::renderText("FPS " + std::to_string(fps), 0.0f, height - dimensions.y, 0.3f, glm::vec3(1.0f));
	}
}

void ICE::Window::toggleFPSDisplay() {
	displayFPS = !displayFPS;
}

GLfloat ICE::Window::getDeltaTime() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	return deltaTime;
}

GLboolean ICE::Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void ICE::Window::pollEvents() {
	glfwPollEvents();
}

bool ICE::Window::initGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

bool ICE::Window::initGLEW() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	return true;
}

void ICE::Window::keyCallback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mode) {
	if (action == GLFW_PRESS) {
		keys[key] = true;
	} else if (action == GLFW_RELEASE) {
		keys[key] = false;
	}

	if (keyCallbackIsSet) {
		customKeyCallback(key, action, mode);
	}
}

void ICE::Window::cursorPosCallback(GLFWwindow *window, GLdouble posX, GLdouble posY) {
	if (cursorPosCallbackIsSet) {
		customCursorPosCallback(posX, posY);
	}
}

void ICE::Window::mouseBtnCallback(GLFWwindow *window, GLint key, GLint action, GLint mode) {
	if (mouseBtnCallbackIsSet) {
		customMouseBtnCallback(key, action, mode);
	}
}

void ICE::Window::setKeyCallback(KeyCallbackFunction function) {
	keyCallbackIsSet = true;
	customKeyCallback = function;
}

void ICE::Window::setCursorPosCallback(CursorPosCallbackFunction function) {
	cursorPosCallbackIsSet = true;
	customCursorPosCallback = function;
}

void ICE::Window::setMouseBtnCallback(MouseBtnCallbackFunction function) {
	mouseBtnCallbackIsSet = true;
	customMouseBtnCallback = function;
}
