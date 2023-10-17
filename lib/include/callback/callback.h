/**
 * \file callback.h
 * \brief Contains functions declarations to add different callbacks.
 */

#ifndef CALLBACK_H_INCLUDED_
#define CALLBACK_H_INCLUDED_

#include <GL/glut.h>

#include "geometry/point.h"
#include "geometry/size.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * \brief Mouse buttons enumeration.
 */
typedef enum mouse_button_code {
  LEFT_BUTTON = GLUT_LEFT_BUTTON,
  MIDDLE_BUTTON = GLUT_MIDDLE_BUTTON,
  RIGHT_BUTTON = GLUT_RIGHT_BUTTON,
} mouse_button_code_t;


typedef void (*display_callback_fn)(void);
typedef void (*resize_callback_fn)(size2d_t);

typedef void (*mouse_callback_fn)(mouse_button_code_t, point2d_t);
typedef void (*motion_callback_fn)(point2d_t);


/**
 * \brief Add current window display callback
 *        called when current window needs to be redisplayed.
 * 
 * \param callback callback function to add.
 */
void add_display_callback(display_callback_fn callback);

/**
 * \brief Add current window resize callback
 *        called when current window was resized.
 * 
 * \param callback callback function to add.
 */
void add_resize_callback(resize_callback_fn callback);

/**
 * \brief Add current window mouse down callback
 *        called when one of mouse buttons was pressed.
 * 
 * \param callback callback function to add.
 */
void add_mouse_down_callback(mouse_callback_fn callback);

/**
 * \brief Add current window mouse up callback
 *        called when one of mouse buttons was released.
 * 
 * \param callback callback function to add.
 */
void add_mouse_up_callback(mouse_callback_fn callback);

/**
 * \brief Add current window motion callback
 *        called when the mouse moves within the window
 *        while one or more mouse buttons are pressed.
 * 
 * \param callback callback function to add.
 */
void add_mouse_move_callback(motion_callback_fn callback);

/**
 * \brief Add current window  callback
 *        called when the mouse moves within the window
 *        while no mouse buttons are pressed.
 * 
 * \param callback callback function to add.
 */
void add_passive_mouse_move_callback(motion_callback_fn callback);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CALLBACK_H_INCLUDED_ */
