/**
 * \file callback.h
 * \brief Contains functions declarations to add different callbacks.
 */

#ifndef CALLBACK_H_INCLUDED_
#define CALLBACK_H_INCLUDED_

#include "geometry/size.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef void (*display_callback_fn)(void);
typedef void (*resize_callback_fn)(size2d_t);


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


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CALLBACK_H_INCLUDED_ */
