/**
 * \file window.c
 * \brief Contains implementation of window functions.
 */

#include "gui/window.h"

#include <stdint.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "ccollections/vector.h"
#include "ccollections/list.h"

#include "geometry/size.h"
#include "geometry/point.h"

#include "callback/callback.h"
#include "callback/prv_callback.h"


window_t *mainwindow;


/**
 * \brief Hidden (private) array (vector) of all created windows.
 */
vector_t *windows;

window_t *get_current_window(void) {
    return vector__at(windows, glutGetWindow());
}


window_t *window__create(
    const char *title,
    size2d_t size,
    point2d_t position
) {
    window_t *window;

    window = malloc(sizeof(window_t *));

    glutInitWindowSize(size.w, size.h);
    glutInitWindowPosition(position.x, position.y);

    window->id = glutCreateWindow(title);
    window->size = size;
    window->callbacks = vector__create(2);

    if (windows == NULL) {
        windows = vector__create(0);
    }

    vector__set(windows, window->id, window);

    for (int i = 0; i < window->callbacks->size; ++i) {
        vector__set(window->callbacks, i, list__create());
    }

    init_callbacks();

    add_display_callback(clear_frame);
    add_resize_callback(update_size);

    return window;
}

void window__destroy(window_t *window) {
    vector_iterator_t iterator;

    if (window == NULL || window->id == 0) {
        return;
    }

    glutDestroyWindow(window->id);

    for (int i = 0; i < window->callbacks->size; ++i) {
        list__free(vector__at(window->callbacks, i));
    }

    free(window);
}
