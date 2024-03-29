#include "Main.h"
#include "HelloTriangle.h"

// Window params
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *htVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *htFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
"}\n";

int helloTriangle()
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
	// Load OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::FAILED_TO_INIT_GLAD" << std::endl;
		glfwTerminate();
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Create and Compile the shader program
	// vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &htVertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILE::VERTEX_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
		glfwTerminate();
		return 1;
	}

	// fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &htFragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "\ERROR::SHADER::COMPILE::FRAGMENT_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
		glfwTerminate();
		return 1;
	}

	// link shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK::SHADER_PROGRAM_LINK_FAILED\n" << infoLog << std::endl;
		glfwTerminate();
		return 1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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
		//  triangle 1
	   -0.9f, -0.5f, 0.0f, // left
		0.0f, -0.5f, 0.0f, // right
	   -0.4f,  0.5f, 0.0f,  // top
		// triangle 2
		0.0f, -0.7f, 0.5f, // left
		0.9f, -0.7f, 0.5f, // right
		0.45f, 0.3f, 0.5f  // top
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//////////////////////////////////////////////////////////////////////////////////
	// Render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// draw the triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}