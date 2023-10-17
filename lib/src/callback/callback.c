/**
 * \file callback.c
 * \brief Contains implementations of callback manipulating functions.
 */

#include "callback/callback.h"
#include "callback/prv_callback.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include "ccollections/list.h"

#include "gui/window.h"


void add_display_callback(display_callback_fn callback) {
    list__add(
        get_callbacks(DISPLAY_CALLBACK),
        callback
    );
}

void add_resize_callback(resize_callback_fn callback) {
    list__add(
        get_callbacks(RESIZE_CALLBACK),
        callback
    );
}

void add_mouse_down_callback(mouse_callback_fn callback) {
    list__add(
        get_callbacks(MOUSE_DOWN_CALLBACK),
        callback
    );
}

void add_mouse_up_callback(mouse_callback_fn callback) {
    list__add(
        get_callbacks(MOUSE_UP_CALLBACK),
        callback
    );
}

void add_mouse_move_callback(motion_callback_fn callback) {
    list__add(
        get_callbacks(MOTION_CALLBACK),
        callback
    );
}

void add_passive_mouse_move_callback(motion_callback_fn callback) {
    list__add(
        get_callbacks(PASSIVE_MOTION_CALLBACK),
        callback
    );
}


void init_callbacks(void) {
    glutDisplayFunc(display_wrapper);
    glutReshapeFunc(reshape_wrapper);

    glutMouseFunc(mouse_wrapper);
    glutMotionFunc(motion_wrapper);
    glutPassiveMotionFunc(passive_motion_wrapper);
}


list_t *get_callbacks(callback_code_t callback_code) {
    return vector__at(
        get_current_window()->callbacks,
        callback_code
    );
}


void display_wrapper(void) {
    list_iterator_t iterator;
    display_callback_fn callback;

    iterator = list__get_iterator(
        get_callbacks(DISPLAY_CALLBACK)
    );

    callback = list_iterator__current(&iterator);
    while (!list_iterator__ended(&iterator)) {
        callback();
        callback = list_iterator__next(&iterator);
    }

    glutSwapBuffers();
    glFlush();
}

void reshape_wrapper(int width, int height) {
    list_iterator_t iterator;
    resize_callback_fn callback;

    iterator = list__get_iterator(
        get_callbacks(RESIZE_CALLBACK)
    );

    callback = list_iterator__current(&iterator);
    while (!list_iterator__ended(&iterator)) {
        callback((size2d_t){
            .w = width,
            .h = height
        });

        callback = list_iterator__next(&iterator);
    }
}

void mouse_wrapper(int button, int state, int x, int y) {
    list_iterator_t iterator;
    mouse_callback_fn callback;

    iterator = list__get_iterator(
        get_callbacks(state == GLUT_DOWN ?
                      MOUSE_DOWN_CALLBACK :
                      MOUSE_UP_CALLBACK)
    );

    callback = list_iterator__current(&iterator);
    while (!list_iterator__ended(&iterator)) {
        callback(
            (mouse_button_code_t)(button),
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&iterator);
    }
}

void motion_wrapper(int x, int y) {
    list_iterator_t iterator;
    motion_callback_fn callback;

    iterator = list__get_iterator(
        get_callbacks(MOTION_CALLBACK)
    );

    callback = list_iterator__current(&iterator);
    while (!list_iterator__ended(&iterator)) {
        callback((point2d_t){
            .x = x,
            .y = y
        });

        callback = list_iterator__next(&iterator);
    }
}

void passive_motion_wrapper(int x, int y) {
    list_iterator_t iterator;
    motion_callback_fn callback;

    iterator = list__get_iterator(
        get_callbacks(PASSIVE_MOTION_CALLBACK)
    );

    callback = list_iterator__current(&iterator);
    while (!list_iterator__ended(&iterator)) {
        callback((point2d_t){
            .x = x,
            .y = y
        });

        callback = list_iterator__next(&iterator);
    }
}


void update_size(size2d_t size) {
    get_current_window()->size = size;

    glViewport(0, 0, size.w, size.h);
}

void clear_frame(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}
