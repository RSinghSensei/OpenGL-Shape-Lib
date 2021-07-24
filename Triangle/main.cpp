#include <stdio.h>
#include <iostream>
 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
	"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	cout << width << " " << height << endl;
	glViewport(0, 0, width, height);
}

void inputCheck(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cout << "Lol" << endl;
	}
}


int main() {
	//Initialization and window context setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	
	//Window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);

	if (window == NULL) {
		cout << "Window could not be created, try again" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to load GLAD" << endl;
		return -1;	
	}

	//Resize and color setting window context functions
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	//Graphics Pipeline Begins
	float triangle_verts[] = {
		-0.5f,-0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f
	};

	float quad_verts[] = {
		  0.5f, 0.5f, 0.0f,
		  0.4f,-0.3f, 0.0f,
		 -0.5f,-0.5f, 0.0f,
		 -0.5f, 0.5f, 0.0f
	};

	unsigned int quad_indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verts), quad_verts, GL_STATIC_DRAW);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), quad_indices, GL_STATIC_DRAW);

		
	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vShader);

	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragShaderSource, NULL);
	glCompileShader(fShader);

	unsigned int linkedS = glCreateProgram();
	glAttachShader(linkedS, vShader);	
	glAttachShader(linkedS, fShader);
	glLinkProgram(linkedS);


	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	
	glEnableVertexAttribArray(0);
	
	//Main game loop
	while (!glfwWindowShouldClose(window)) {
		inputCheck(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(linkedS);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;

 }