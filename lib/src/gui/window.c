/**
 * \file window.c
 * \brief Contains implementation of window functions.
 */

#include "gui/window.h"

#include <stdint.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "ccl/vector.h"
#include "ccl/list.h"

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
    const size2d_t size,
    const point2d_t position
) {
    /* Iterator of new window callbacks lists. */
    vector_iterator_t it;

    /* New window pointer. */
    window_t *window;

    glutInitWindowSize(size.w, size.h);
    glutInitWindowPosition(position.x, position.y);

    window = malloc(sizeof(window_t));

    *window = (window_t){
        .id = glutCreateWindow(title),
        .size = size,
        .callbacks = vector__create(CALLBACK_TYPES_NUMBER)
    };

    if (windows == NULL) {
        windows = vector__create(1);

        vector__set(windows, 0, NULL);
    }

    vector__set(windows, window->id, window);

    it = vector__begin(window->callbacks);
    while (!vector_iterator__ended(&it)) {
        vector_iterator__set(&it, list__create());

        vector_iterator__next(&it);
    }

    init_callbacks();

    add_display_callback(clear_frame);
    add_resize_callback(update_size);

    return window;
}

void window__destroy(window_t *window) {
    /* Iterator of `window` callbacks lists. */
    vector_iterator_t it;

    if (window == NULL || window->id == 0) {
        return;
    }

    glutDestroyWindow(window->id);

    it = vector__begin(window->callbacks);
    while (!vector_iterator__ended(&it)) {
        list__free(vector_iterator__get(&it));

        vector_iterator__next(&it);
    }

    vector__free(window->callbacks);

    free(window);
}
