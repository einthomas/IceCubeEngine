#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "TextRenderer.h"

namespace ICE {
	typedef void(*KeyCallbackFunction) (GLint, GLint, GLint);
	typedef void(*CursorPosCallbackFunction) (GLdouble, GLdouble);
	typedef void(*MouseBtnCallbackFunction) (GLint, GLint, GLint);

	class Window {
	public:
		static GLboolean keys[1024];
		std::string title;
		GLuint width, height;

		Window(std::string title, GLuint width, GLuint height);
		void swapBuffers();
		void update();
		void toggleFPSDisplay();
		GLfloat getDeltaTime();
		GLboolean shouldClose();
		void pollEvents();
		void setKeyCallback(KeyCallbackFunction function);
		void setCursorPosCallback(CursorPosCallbackFunction function);
		void setMouseBtnCallback(MouseBtnCallbackFunction function);

	private:
		GLFWwindow* window;
		GLfloat lastFrame = 0.0f;
		GLfloat deltaTime;
		GLboolean displayFPS = false;
		static GLboolean keyCallbackIsSet;
		static GLboolean cursorPosCallbackIsSet;
		static GLboolean mouseBtnCallbackIsSet;

		static KeyCallbackFunction customKeyCallback;
		static CursorPosCallbackFunction customCursorPosCallback;
		static MouseBtnCallbackFunction customMouseBtnCallback;

		bool initGLFW();
		bool initGLEW();
		static void keyCallback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mode);
		static void cursorPosCallback(GLFWwindow *window, GLdouble posX, GLdouble posY);
		static void mouseBtnCallback(GLFWwindow *window, GLint key, GLint action, GLint mode);
	};
}
