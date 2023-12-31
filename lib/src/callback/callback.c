/**
 * \file callback.c
 * \brief Contains implementations of callback manipulating
 *        functions.
 */

#include "callback/callback.h"
#include "callback/prv_callback.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include "ccl/list.h"

#include "gui/window.h"


void add_display_callback(
    display_callback_fn callback
) {
    add_callback(callback, DISPLAY_CALLBACK);
}

void add_resize_callback(
    resize_callback_fn callback
) {
    add_callback(callback, RESIZE_CALLBACK);
}

void add_mouse_down_callback(
    mouse_callback_fn callback
) {
    add_callback(callback, MOUSE_DOWN_CALLBACK);
}

void add_mouse_up_callback(
    mouse_callback_fn callback
) {
    add_callback(callback, MOUSE_UP_CALLBACK);
}

void add_mouse_move_callback(
    motion_callback_fn callback
) {
    add_callback(callback, MOUSE_MOVE_CALLBACK);
}

void add_passive_mouse_move_callback(
    motion_callback_fn callback
) {
    add_callback(callback, MOUSE_PASSIVE_MOVE_CALLBACK);
}

void add_keyboard_down_callback(
    keyboard_callback_fn callback
) {
    add_callback(callback, KEYBOARD_DOWN_CALLBACK);
}

void add_keyboard_up_callback(
    keyboard_callback_fn callback
) {
    add_callback(callback, KEYBOARD_UP_CALLBACK);
}

void add_special_keyboard_down_callback(
  special_keyboard_callback_fn callback
) {
    add_callback(callback, SPECIAL_KEYBOARD_DOWN_CALLBACK);
}

void add_special_keyboard_up_callback(
  special_keyboard_callback_fn callback
) {
    add_callback(callback, SPECIAL_KEYBOARD_UP_CALLBACK);
}


void init_callbacks(void) {
    glutDisplayFunc(display_wrapper);
    glutReshapeFunc(reshape_wrapper);

    glutMouseFunc(mouse_wrapper);
    glutMotionFunc(motion_wrapper);
    glutPassiveMotionFunc(passive_motion_wrapper);

    glutKeyboardFunc(keyboard_wrapper);
    glutKeyboardUpFunc(keyboard_up_wrapper);

    glutSpecialFunc(special_wrapper);
    glutSpecialUpFunc(special_up_wrapper);
}


void add_callback(void *callback, callback_code_t callback_code) {
    if (callback != NULL) {
        list__push_back(get_callbacks(callback_code), callback);
    }
}


list_t *get_callbacks(callback_code_t callback_code) {
    return vector__at(
        get_current_window()->callbacks,
        callback_code
    );
}

list_iterator_t get_callbacks_iterator(
  callback_code_t callback_code
) {
    return list__begin(get_callbacks(callback_code));
}


void display_wrapper(void) {
    list_iterator_t it;
    display_callback_fn callback;

    it = get_callbacks_iterator(DISPLAY_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback();

        callback = list_iterator__next(&it);
    }

    glutSwapBuffers();
    glFlush();
}

void reshape_wrapper(int width, int height) {
    list_iterator_t it;
    resize_callback_fn callback;

    it = get_callbacks_iterator(RESIZE_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (size2d_t){
                .w = width,
                .h = height
            }
        );

        callback = list_iterator__next(&it);
    }
}

void mouse_wrapper(int button, int state, int x, int y) {
    list_iterator_t it;
    mouse_callback_fn callback;

    it = get_callbacks_iterator(
        (state == GLUT_DOWN) ?
        (MOUSE_DOWN_CALLBACK) :
        (MOUSE_UP_CALLBACK)
    );

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (mouse_button_code_t)(button),
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&it);
    }
}

void motion_wrapper(int x, int y) {
    list_iterator_t it;
    motion_callback_fn callback;

    it = get_callbacks_iterator(MOUSE_MOVE_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&it);
    }
}

void passive_motion_wrapper(int x, int y) {
    list_iterator_t it;
    motion_callback_fn callback;

    it = get_callbacks_iterator(MOUSE_PASSIVE_MOVE_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&it);
    }
}

void keyboard_wrapper(unsigned char key, int x, int y) {
    list_iterator_t it;
    keyboard_callback_fn callback;

    it = get_callbacks_iterator(KEYBOARD_DOWN_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (uint8_t)key,
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&it);
    }
}

void keyboard_up_wrapper(unsigned char key, int x, int y) {
    list_iterator_t it;
    keyboard_callback_fn callback;

    it = get_callbacks_iterator(KEYBOARD_UP_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (uint8_t)key,
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&it);
    }
}

void special_wrapper(int key, int x, int y) {
    list_iterator_t it;
    special_keyboard_callback_fn callback;

    it = get_callbacks_iterator(SPECIAL_KEYBOARD_DOWN_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (special_key_code_t)(key),
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&it);
    }
}

void special_up_wrapper(int key, int x, int y) {
    list_iterator_t it;
    special_keyboard_callback_fn callback;

    it = get_callbacks_iterator(SPECIAL_KEYBOARD_UP_CALLBACK);

    callback = list_iterator__get(&it);
    while (!list_iterator__ended(&it)) {
        callback(
            (special_key_code_t)(key),
            (point2d_t){
                .x = x,
                .y = y
            }
        );

        callback = list_iterator__next(&it);
    }
}


void update_size(const size2d_t size) {
    get_current_window()->size = size;

    glViewport(0, 0, size.w, size.h);
}

void clear_frame(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}
