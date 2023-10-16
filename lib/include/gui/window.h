/**
 * \file window.h
 * \brief Contains declaration of window structure
 *        and associated functions to create and destroy windows.
 */

#ifndef WINDOW_H_INCLUDED_
#define WINDOW_H_INCLUDED_

#include <stdint.h>

#include "geometry/size.h"
#include "geometry/point.h"

#include "ccollections/vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * \brief Application window with GLUT unique identifier,
 *        current size and all event callbacks.
 * 
 * \note if `id` equals to `0` window is not associated
 *       with any application window.
 */
typedef struct window {
  /* Unique window identifier. */
  int32_t id;

  /* Current window size. */
  size2d_t size;

  /* All callbacks associated with window. */
  vector_t *callbacks;
} window_t;


/**
 * \brief Main application window. Used to get ease access to it.
 * 
 * \note This variable is not initialized anywhere,
 *       so it must be initialized by pointer
 *       returned from first `window__create(...)` call.
 */
extern window_t *mainwindow;


/**
 * \brief Gets the current window.
 * 
 * \return Pointer to the current window,
 *         if at least one exists, `NULL` otherwise.
 */
window_t *get_current_window(void);


/**
 * \brief Creates new window.
 * 
 * \param title title of new window.
 * \param size initial size of new window.
 * \param position initial position of new window.
 * 
 * \return Pointer to created window.
 */
window_t *window__create(
  const char *title,
  size2d_t size,
  point2d_t position
);

/**
 * \brief Destroys the window
 *        and associated with it OpenGL context.
 * 
 * \param window window to be destroyed.
 */
void window__destroy(window_t *window);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WINDOW_H_INCLUDED_ */
