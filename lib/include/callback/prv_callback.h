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
#define CALLBACK_TYPES_NUMBER 2


/**
 * \brief Callback code enumeration.
 */
typedef enum callback_code {
  DISPLAY_CALLBACK,
  RESIZE_CALLBACK,
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
 * \brief Wrapper callback functions which call specific
 *        callbacks of the current window.
 */

void display_wrapper(void);
void reshape_wrapper(int width, int height);


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
