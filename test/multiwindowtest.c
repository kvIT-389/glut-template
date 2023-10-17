#include <stdio.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "gui/window.h"
#include "callback/callback.h"


void draw_yellow(void) {
    glColor3ub(0xff, 0xaa, 0x11);
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, -0.8);
        glVertex2d(0.8, 0.8);
        glVertex2d(-0.8, 0.8);
    glEnd();
}

void draw_cyan(void) {
    glColor3ub(0x11, 0xff, 0xaa);
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, 0.8);
        glVertex2d(0.8, -0.8);
        glVertex2d(-0.8, -0.8);
    glEnd();
}

void print_size(size2d_t size) {
    window_t *window = get_current_window();

    printf(
        "Size of window with id = %d: %dx%d\n\033[1A\r\033[K",
        window->id, window->size.w, window->size.h
    );
}


window_t *second_window;


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

    add_display_callback(draw_yellow);
    add_resize_callback(print_size);

    second_window = window__create(
        "Second OpenGL Window",
        (size2d_t){480, 480},
        (point2d_t){700, 200}
    );

    add_display_callback(draw_cyan);
    add_resize_callback(print_size);

    glutMainLoop();

    return 0;
}
