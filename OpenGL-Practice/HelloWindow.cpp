#include "Main.h"
#include "HelloWindow.h"

// Window params
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int helloWindow()
{
	//////////////////////////////////////////////////////////////////////////////////
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//////////////////////////////////////////////////////////////////////////////////
	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Big Ol' Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR::OPENGL::CREATE_WINDOW_FAILED" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//////////////////////////////////////////////////////////////////////////////////
	// Load OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::FAILED_TO_INIT_GLAD" << std::endl;
		glfwTerminate();
		return 1;
	}
	
	//////////////////////////////////////////////////////////////////////////////////
	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// additional render commands
		glClearColor(0.0, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}