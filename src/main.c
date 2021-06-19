// Macros
#define BODY_COUNT	0x0200


// Headers
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl.h"
#include "types.h"
#include "utils.h"


// Types
typedef struct {
	vec2f_t pos;
	vec2f_t vel;
	float m;
} body_t;


// Square Distance Function
static float sq_dist(vec2f_t p1, vec2f_t p2) {
	float x_diff = p1.x-p2.x;
	float y_diff = p1.y-p2.y;
	return x_diff*x_diff+y_diff*y_diff;
}


// Main Function
int32_t main() {
	// Setup
	body_t bodies[BODY_COUNT];

	gl_init(1280, 720, "gravity_demo", 0x01);

	randoms(time(0x00));
	for(size_t i = 0x00; i < BODY_COUNT; i++) {
		bodies[i].pos.x = randomf()-0.5f;
		bodies[i].pos.y = randomf()-0.5f;

		bodies[i].vel.x = 0.0f;
		bodies[i].vel.y = 0.0f;

		bodies[i].m = randomf()*0.01f;
	}


	// Code
	while(!should_close()) {
		// Updating
		for(size_t i = 0x00; i < BODY_COUNT; i++) {
			for(size_t j = 0x00; j < BODY_COUNT; j++) {
				if(i != j) {
					float mag = sqrtf(sq_dist(bodies[i].pos, bodies[j].pos));
					mag = delta*bodies[j].m/mag;

					float a = atan2f(
						bodies[j].pos.y-bodies[i].pos.y,
						bodies[j].pos.x-bodies[i].pos.x
					);

					bodies[i].vel.x += cosf(a)*mag;
					bodies[i].vel.y += sinf(a)*mag;
				}
			}
		}

		for(size_t i = 0x00; i < BODY_COUNT; i++) {
			bodies[i].pos.x += bodies[i].vel.x*delta;
			bodies[i].pos.y += bodies[i].vel.y*delta;
		}


		// Rendering
		draw_bg();

		for(size_t i = 0x00; i < BODY_COUNT; i++) {
			buffer_vertex(
				bodies[i].pos.x, bodies[i].pos.y,
				1.0f, 1.0f, 1.0f, bodies[i].m*100
			);
		}
		draw_buffer(POINTS);

		render();
	}


	// De-initialization
	gl_deinit();
	return 0x00;
}