#ifndef GL_H
#define GL_H


// Macros
#define POINTS			0x00
#define LINES			0x01
#define LINE_LOOP		0x02
#define LINE_STRIP		0x03
#define TRIANGLES		0x04
#define TRIANGLE_STRIP	0x05
#define TRIANGLE_FAN	0x06


// Headers
#include "types.h"


// Global Variables
extern void (*set_bg_color)(float r, float g, float b, float a);
extern float delta;


// OpenGL Initialization Function
void gl_init(uint32_t width, uint32_t height, char* name, uint8_t visible);


// OpenGL De-initialization Function
void gl_deinit();


// Should Close Function
uint8_t should_close();


// Draw Background Function
void draw_bg();


// Render Function
void render();


// Draw Buffer Function
void draw_buffer(uint32_t mode);


// Buffer Vertex Function
void buffer_vertex(float x, float y, float r, float g, float b, float a);


#endif