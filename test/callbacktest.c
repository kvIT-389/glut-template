#include <stdio.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "gui/window.h"
#include "callback/callback.h"


void draw(void) {
    glColor3ub(0xff, 0xaa, 0x11);
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, -0.8);
        glVertex2d(0.8, 0.8);
        glVertex2d(-0.8, 0.8);
    glEnd();
}

void print_size(size2d_t size) {
    window_t *window = get_current_window();

    printf(
        "Main Window size: %dx%d\n\033[1A\r\033[K",
        window->size.w, window->size.h
    );
}

void print_mouse_down_coords(mouse_button_code_t button, point2d_t point) {
    printf(
        "Mouse down with %d button at (%d; %d)\n\033[1A\r\033[K",
        button, point.x, point.y
    );
}

void print_mouse_up_coords(mouse_button_code_t button, point2d_t point) {
    printf(
        "Mouse up with %d button at (%d; %d)\n\033[1A\r\033[K",
        button, point.x, point.y
    );
}

void print_mouse_move_coords(point2d_t point) {
    printf(
        "Mouse move to (%d; %d)\n\033[1A\r\033[K",
        point.x, point.y
    );
}

void print_passive_mouse_move_coords(point2d_t point) {
    printf(
        "Mouse passive move to (%d; %d)\n\033[1A\r\033[K",
        point.x, point.y
    );
}

void print_key_down(uint8_t key, point2d_t point) {
    printf(
        "Key %c pressed at (%d; %d)\n\033[1A\r\033[K",
        key, point.x, point.y
    );
}

void print_key_up(uint8_t key, point2d_t point) {
    printf(
        "Key %c released at (%d; %d)\n\033[1A\r\033[K",
        key, point.x, point.y
    );
}

const char special_keys_names[9][9] = {
    "Left", "Up", "Right", "Down",
    "PageUp", "PageDown", "Home", "End",
    "Insert"
};

void print_special_key_down(special_key_code_t key, point2d_t point) {
    if (key < 12) {
        printf(
            "F%d key pressed at (%d; %d)\n\033[1A\r\033[K",
            key + 1, point.x, point.y
        );
    } else {
        printf(
            "%s key pressed at (%d; %d)\n\033[1A\r\033[K",
            special_keys_names[key - KEY_LEFT], point.x, point.y
        );
    }
}

void print_special_key_up(special_key_code_t key, point2d_t point) {
    if (key < 12) {
        printf(
            "F%d key released at (%d; %d)\n\033[1A\r\033[K",
            key + 1, point.x, point.y
        );
    } else {
        printf(
            "%s key released at (%d; %d)\n\033[1A\r\033[K",
            special_keys_names[key - KEY_LEFT], point.x, point.y
        );
    }
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(
        GLUT_RGBA |
        GLUT_DOUBLE |
        GLUT_DEPTH |
        GLUT_MULTISAMPLE
    );

    mainwindow = window__create(
        "Main OpenGL Window",
        (size2d_t){480, 480},
        (point2d_t){200, 200}
    );

    add_display_callback(draw);
    add_resize_callback(print_size);

    add_mouse_down_callback(print_mouse_down_coords);
    add_mouse_up_callback(print_mouse_up_coords);

    add_mouse_move_callback(print_mouse_move_coords);
    add_passive_mouse_move_callback(print_passive_mouse_move_coords);

    add_keyboard_down_callback(print_key_down);
    add_keyboard_up_callback(print_key_up);

    add_special_keyboard_down_callback(print_special_key_down);
    add_special_keyboard_up_callback(print_special_key_up);

    glutMainLoop();

    return 0;
}
