#include <GL/glut.h>

#include "gui/window.h"

#include "callback/callback.h"
#include "callback/timer.h"


double hexagon_angle = 0.0;

void draw_hexagon(void) {
    glPushMatrix();

    double k = (double)(mainwindow->size.w) /
               (double)(mainwindow->size.h);

    if (k > 1.0) {
        glOrtho(-k, k, -1.0, 1.0, -1.0, 1.0);
    } else {
        glOrtho(-1.0, 1.0, -1.0/k, 1.0/k, -1.0, 1.0);
    }

    glRotated(hexagon_angle, 0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
        glColor3ub(0xff, 0x00, 0x00); glVertex2d( 1.0,  0.0);
        glColor3ub(0xff, 0xff, 0x00); glVertex2d( 0.5,  0.87);
        glColor3ub(0x00, 0xff, 0x00); glVertex2d(-0.5,  0.87);
        glColor3ub(0x00, 0xff, 0xff); glVertex2d(-1.0,  0.0);
        glColor3ub(0x00, 0x00, 0xff); glVertex2d(-0.5, -0.87);
        glColor3ub(0xff, 0x00, 0xff); glVertex2d( 0.5, -0.87);
    glEnd();

    glPopMatrix();
}

void rotate_hexagon(void) {
    hexagon_angle += 1.0;

    if (hexagon_angle >= 360.0) {
        hexagon_angle -= 360.0;
    }
}

void update(void) {
    glutPostWindowRedisplay(glutGetWindow());
}


timer_t_ *update_timer;
timer_t_ *rotate_timer;


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

    rotate_timer = timer__create(20);

    timer__add_callback(rotate_timer, rotate_hexagon);
    timer__enable(rotate_timer);

    add_display_callback(draw_hexagon);

    update_timer = timer__create(10);

    timer__add_callback(update_timer, update);
    timer__enable(update_timer);

    glutMainLoop();

    return 0;
}
