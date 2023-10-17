/**
 * \file prv_callback.h
 * \brief Contains private functions needed for internal
 *        implementation of callbacks adding mechanism.
 */

#ifndef PRV_CALLBACK_H_INCLUDED_
#define PRV_CALLBACK_H_INCLUDED_

#include "ccollections/list.h"

#include "geometry/size.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * \brief Number of different callbacks.
 */
#define CALLBACK_TYPES_NUMBER 10


/**
 * \brief Callback code enumeration.
 */
typedef enum callback_code {
  DISPLAY_CALLBACK,
  RESIZE_CALLBACK,
  MOUSE_DOWN_CALLBACK,
  MOUSE_UP_CALLBACK,
  MOUSE_MOVE_CALLBACK,
  MOUSE_PASSIVE_MOVE_CALLBACK,
  KEYBOARD_DOWN_CALLBACK,
  KEYBOARD_UP_CALLBACK,
  SPECIAL_KEYBOARD_DOWN_CALLBACK,
  SPECIAL_KEYBOARD_UP_CALLBACK,
} callback_code_t;


/**
 * \brief Initiates callbacks for the current window.
 * 
 * \note This function called during `window__create(...)` call
 *       from `window.h` header, so you should not call it
 *       anywhere else.
 */
void init_callbacks(void);


/**
 * \brief Get callbacks list of the current window
 *        of the specific type.
 * 
 * \param callback_code \ref `callback_code_t` member.
 * \return List of specific callbacks of the current window
 *         if it exists, `NULL` otherwise.
 */
list_t *get_callbacks(callback_code_t callback_code);

/**
 * \brief Add current window callback of the specified type.
 * 
 * \param callback callback function to add.
 * \param callback_code \ref `callback_code_t` member.
 */
void add_callback(void *callback, callback_code_t callback_code);


/**
 * \brief Wrapper callback functions which call specific
 *        callbacks of the current window.
 */

void display_wrapper(void);
void reshape_wrapper(int width, int height);

void mouse_wrapper(int button, int state, int x, int y);
void motion_wrapper(int x, int y);
void passive_motion_wrapper(int x, int y);

void keyboard_wrapper(unsigned char key, int x, int y);
void keyboard_up_wrapper(unsigned char key, int x, int y);

void special_wrapper(int key, int x, int y);
void special_up_wrapper(int key, int x, int y);


/**
 * \brief Display callback which clears screen and
 *        resets previous applied transformations.
 */
void clear_frame(void);

/**
 * \brief Resize callback which updates size of current
 *        window and OpenGL viewport.
 */
void update_size(size2d_t size);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PRV_CALLBACK_H_INCLUDED_ */
