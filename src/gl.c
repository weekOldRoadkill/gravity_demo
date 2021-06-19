// Headers
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "types.h"
#include "utils.h"


// Global Variables
void (*set_bg_color)(float r, float g, float b, float a);
float delta;


// File Variables
static uint8_t init = 0x00;
static char buff1[0x8000];

static size_t vertex_buff_size = 0x00;
static float vertex_buff[0x00040000];

static uint32_t vertex_coords_id;
static uint32_t vertex_color_id;
static GLFWwindow* window;
static uint32_t program;
static uint32_t vao;
static uint32_t vbo;

static char* vert_shader_src =
"#version 460 core\n"
"in vec2 vertex_coords;"
"in vec4 vertex_color;"
"out vec4 vert_color;"
"uniform float ratio;"
"void main() {"
"gl_Position.xy = vertex_coords*vec2(ratio, 1.0f);"
"vert_color = vertex_color;"
"}";

static char* frag_shader_src =
"#version 460 core\n"
"in vec4 vert_color;"
"out vec4 color;"
"void main() {"
"color = vert_color;"
"}";


// Compile Shader Function
static void compile_shader(uint32_t shader, char* src) {
	glShaderSource(shader, 0x01, (const char**) &src, 0x00);
	glCompileShader(shader);

	int32_t temp;
	buff1[0x00] = 0x00;
	glGetShaderInfoLog(shader, sizeof(buff1), 0x00, buff1);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &temp);

	if(temp) {
		info("Shader compiled successfully.");
		if(buff1[0x00]) {
			info("Compile Info:");
			puts(buff1);
		}
	} else {
		info("Compile Info:");
		puts(buff1);
		error("Shader failed to compile.");
	}
}


// Link Program Function
static void link_program(uint32_t program) {
	glLinkProgram(program);

	int32_t temp;
	buff1[0x00] = 0x00;
	glGetProgramInfoLog(program, sizeof(buff1), 0x00, buff1);
	glGetProgramiv(program, GL_LINK_STATUS, &temp);

	if(temp) {
		info("Program linked successfully.");
		if(buff1[0x00]) {
			info("Link Info:");
			puts(buff1);
		}
	} else {
		info("Link Info:");
		puts(buff1);
		error("Program failed to link.");
	}
}


// OpenGL Initialization Function
void gl_init(uint32_t width, uint32_t height, char* name, uint8_t visible) {
	// Setup
	if(init) {
		error("GL already initialized, cannot initialize again.");
	}

	
	// OpenGL Initialization
	if(!glfwInit()) error("GLFW failed to initialize.");

	glfwSwapInterval(0x01);
	glfwWindowHint(GLFW_SAMPLES, 0x08);
	glfwWindowHint(GLFW_RESIZABLE, 0x00);
	glfwWindowHint(GLFW_VISIBLE, visible);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0x04);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0x06);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, name, 0x00, 0x00);
	if(!window) error("GLFW failed to create an OpenGL context.");

	glfwMakeContextCurrent(window);
	if(!gladLoadGL()) error("Glad failed to initialize.");

	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(2.0f);
	glPointSize(4.0f);


	// Function Pointer Preperation
	set_bg_color = glClearColor;


	// Program Compilation
	program = glCreateProgram();
	uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);
	uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	compile_shader(vert_shader, vert_shader_src);
	compile_shader(frag_shader, frag_shader_src);
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	link_program(program);
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	glUseProgram(program);


	// Attrib & Uniform Setup
	vertex_coords_id = glGetAttribLocation(program, "vertex_coords");
	vertex_color_id = glGetAttribLocation(program, "vertex_color");
	glUniform1f(glGetUniformLocation(program, "ratio"), (float) height/width);


	// VAO Generation
	glGenVertexArrays(0x01, &vao);
	glBindVertexArray(vao);


	// VBO Generation
	glGenBuffers(0x01, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	// Vertex Formatting
	glVertexAttribPointer(
		vertex_coords_id,	// Attrib ID
		0x02,				// Amount of Floats per Vector
		GL_FLOAT,			// Type
		0x00,				// Normalized
		0x06*sizeof(float),	// Stride (bytes)
		0x00				// Offset (bytes)
	);

	glVertexAttribPointer(
		vertex_color_id,				// Attrib ID
		0x04,							// Amount of Floats per Vector
		GL_FLOAT,						// Type
		0x00,							// Normalized
		0x06*sizeof(float),				// Stride (bytes)
		(void*) (0x02*sizeof(float))	// Offset (bytes)
	);

	glEnableVertexAttribArray(vertex_coords_id);
	glEnableVertexAttribArray(vertex_color_id);


	// Data Buffering
	glBufferData(
		GL_ARRAY_BUFFER,		// Target Buffer
		sizeof(vertex_buff),	// Size of Data (bytes)
		0x00,					// Data (empty)
		GL_DYNAMIC_DRAW			// Usage
	);


	// De-initialization
	info("GL initialized successfully.");
	init = 0x01;
}


// OpenGL De-initialization Function
void gl_deinit() {
	// Setup
	if(!init) error("GL not initialized, cannot de-initialize.");


	// OpenGL De-initialization
	glfwTerminate();


	// OpenGL Resource Termination
	glDisableVertexAttribArray(vertex_coords_id);
	glDisableVertexAttribArray(vertex_color_id);
	glDeleteBuffers(0x01, &vbo);
	glDeleteVertexArrays(0x01, &vao);
	glDeleteProgram(program);


	// De-initialization
	info("GL de-initialized successfully.");
	init = 0x00;
}


// Should Close Function
uint8_t should_close() {
	glfwPollEvents();
	return glfwWindowShouldClose(window);
}


// Draw Background Function
void draw_bg() {
	glClear(GL_COLOR_BUFFER_BIT);
}


// Render Function
void render() {
	static float t1;
	float t2;

	glfwSwapBuffers(window);

	t2 = glfwGetTime();
	delta = t2-t1;
	// info("%.ffps", 0x01/delta);
	t1 = t2;
}


// Draw Buffer Function
void draw_buffer(uint32_t mode) {
	if(vertex_buff_size) {
		glBufferSubData(
			GL_ARRAY_BUFFER,				// Target Buffer
			0x00,							// Offset (bytes)
			vertex_buff_size*sizeof(float),	// Size of Data (bytes)
			vertex_buff						// Data
		);

		glDrawArrays(mode, 0x00, vertex_buff_size/0x06);

		vertex_buff_size = 0x00;
	}
}


// Buffer Vertex Function
void buffer_vertex(float x, float y, float r, float g, float b, float a) {
	vertex_buff[vertex_buff_size++] = x;
	vertex_buff[vertex_buff_size++] = y;
	vertex_buff[vertex_buff_size++] = r;
	vertex_buff[vertex_buff_size++] = g;
	vertex_buff[vertex_buff_size++] = b;
	vertex_buff[vertex_buff_size++] = a;

	if(vertex_buff_size > sizeof(vertex_buff)/sizeof(float)) {
		sprintf(
			buff1,
			"Vertex buffer overflow by %zX bytes.",
			vertex_buff_size-sizeof(vertex_buff)/sizeof(float)
		);
		error("%s", buff1);
	}
}