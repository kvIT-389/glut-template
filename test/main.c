#include <GL/glut.h>

#include "gui/window.h"


void display(void) {}


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

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
