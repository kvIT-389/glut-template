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


/**
 * \brief Special keyboard keys enumeration.
 */
typedef enum special_key_code {
  KEY_F1 = GLUT_KEY_F1,
  KEY_F2 = GLUT_KEY_F2,
  KEY_F3 = GLUT_KEY_F3,
  KEY_F4 = GLUT_KEY_F4,
  KEY_F5 = GLUT_KEY_F5,
  KEY_F6 = GLUT_KEY_F6,
  KEY_F7 = GLUT_KEY_F7,
  KEY_F8 = GLUT_KEY_F8,
  KEY_F9 = GLUT_KEY_F9,
  KEY_F10 = GLUT_KEY_F10,
  KEY_F11 = GLUT_KEY_F11,
  KEY_F12 = GLUT_KEY_F12,
  KEY_LEFT = GLUT_KEY_LEFT,
  KEY_UP = GLUT_KEY_UP,
  KEY_RIGHT = GLUT_KEY_RIGHT,
  KEY_DOWN = GLUT_KEY_DOWN,
  KEY_PAGE_UP = GLUT_KEY_PAGE_UP,
  KEY_PAGE_DOWN = GLUT_KEY_PAGE_DOWN,
  KEY_HOME = GLUT_KEY_HOME,
  KEY_END = GLUT_KEY_END,
  KEY_INSERT = GLUT_KEY_INSERT,
} special_key_code_t;


typedef void (*display_callback_fn)(void);
typedef void (*resize_callback_fn)(size2d_t);

typedef void (*mouse_callback_fn)(
  mouse_button_code_t, point2d_t
);
typedef void (*motion_callback_fn)(point2d_t);

typedef void (*keyboard_callback_fn)(uint8_t, point2d_t);
typedef void (*special_keyboard_callback_fn)(
  special_key_code_t, point2d_t
);


/**
 * \brief Add current window display callback
 *        called when current window needs to be redisplayed.
 * 
 * \param callback callback function to add.
 */
void add_display_callback(
  display_callback_fn callback
);

/**
 * \brief Add current window resize callback
 *        called when current window was resized.
 * 
 * \param callback callback function to add.
 */
void add_resize_callback(
  resize_callback_fn callback
);

/**
 * \brief Add current window mouse down callback
 *        called when one of mouse buttons was pressed.
 * 
 * \param callback callback function to add.
 */
void add_mouse_down_callback(
  mouse_callback_fn callback
);

/**
 * \brief Add current window mouse up callback
 *        called when one of mouse buttons was released.
 * 
 * \param callback callback function to add.
 */
void add_mouse_up_callback(
  mouse_callback_fn callback
);

/**
 * \brief Add current window motion callback
 *        called when the mouse moves within the window
 *        while one or more mouse buttons are pressed.
 * 
 * \param callback callback function to add.
 */
void add_mouse_move_callback(
  motion_callback_fn callback
);

/**
 * \brief Add current window  callback
 *        called when the mouse moves within the window
 *        while no mouse buttons are pressed.
 * 
 * \param callback callback function to add.
 */
void add_passive_mouse_move_callback(
  motion_callback_fn callback
);

/**
 * \brief Add current window key down callback
 *        called when keyboard key generating ASCII character
 *        was pressed.
 * 
 * \param callback callback function to add.
 */
void add_keyboard_down_callback(
  keyboard_callback_fn callback
);

/**
 * \brief Add current window key down callback
 *        called when keyboard key generating ASCII character
 *        was released.
 * 
 * \param callback callback function to add.
 */
void add_keyboard_up_callback(
  keyboard_callback_fn callback
);

/**
 * \brief Add current window key down callback
 *        called when keyboard special key was pressed.
 * 
 * \param callback callback function to add.
 */
void add_special_keyboard_down_callback(
  special_keyboard_callback_fn callback
);

/**
 * \brief Add current window key down callback
 *        called when keyboard special key was released.
 * 
 * \param callback callback function to add.
 */
void add_special_keyboard_up_callback(
  special_keyboard_callback_fn callback
);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CALLBACK_H_INCLUDED_ */
