#include "Main.h"
#include "HelloShaders.h"

// Window params
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int helloShaders()
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
	if (window == NULL) {
		std::cout << "ERROR::OPENGL::CREATE_WINDOW_FAILED" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//////////////////////////////////////////////////////////////////////////////////
	// Compile the shader program
	Shader theShader("hs_vs_shader.txt", "hs_fs_shader.txt");

	//////////////////////////////////////////////////////////////////////////////////
	// Load OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR::GLAD::FAILED_TO_INIT_GLAD" << std::endl;
		glfwTerminate();
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Setup vertex and buffer
	float vertices[] = {
		// positions		  // colours
	    0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  // bottom left
	   -0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  // bottom right
	    0.0f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f   // top
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// 1: bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2: bind and set vertex buffer(s)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3: configure vertex attribute(s)
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//////////////////////////////////////////////////////////////////////////////////
	// Render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw the triangle
		theShader.use();
				
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}