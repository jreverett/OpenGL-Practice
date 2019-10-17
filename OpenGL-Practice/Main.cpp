#include "Main.h"
#include "HelloWindow.h"
#include "HelloTriangle.h"
#include "HelloShaders.h"

int main()
{
	if (helloWindow() == 1)
		exit(EXIT_FAILURE);

	if (helloTriangle() == 1)
		exit(EXIT_FAILURE);

	if (helloShaders() == 1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}

// Callback function for window resize rendering
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// If the escape key is pressed, close the window
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}