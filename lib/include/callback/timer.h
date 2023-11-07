/**
 * \file timer.h
 * \brief timer header file.
 */

#ifndef TIMER_H_INCLUDED_
#define TIMER_H_INCLUDED_

#include <stdint.h>

#include "ccl/list.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef void (*timer_callback_fn)(void);


typedef enum timer_state {
  TIMER_DISABLED,
  TIMER_ENABLED,
} timer_state_t;


/**
 * \brief Timer which defines set of callbacks called
 *        with some interval.
 */
typedef struct timer {
  int32_t id;

  uint32_t interval;
  timer_state_t state;

  list_t *callbacks;
} timer_t_;


/**
 * \brief Creates new timer.
 * 
 * \param interval time interval of new timer.
 * 
 * \return Pointer to created timer.
 */
timer_t_ *timer__create(const uint32_t interval);

/**
 * \brief Frees timer.
 * 
 * \param timer timer to free.
 */
void timer__free(timer_t_ *timer);

/**
 * \brief Gets timer state.
 * 
 * \param timer timer to get state from.
 * 
 * \return Timer state which is \ref `timer_state_t` member
 *         if `timer` is not `NULL`, otherwise `TIMER_DISABLED`.
 */
timer_state_t timer__state(const timer_t_ *timer);

/**
 * \brief Checks if timer is disabled or not.
 * 
 * \param timer timer to check.
 * 
 * \return `1` if timer is disabled, `0` otherwise.
 */
uint8_t timer__disabled(const timer_t_ *timer);

/**
 * \brief Checks if timer is enabled or not.
 * 
 * \param timer timer to check.
 * 
 * \return `1` if timer is enabled, `0` otherwise.
 */
uint8_t timer__enabled(const timer_t_ *timer);

/**
 * \brief Adds callback to timer callbacks list,
 *        if `callback` is not `NULL`,
 *        otherwise does nothing.
 * 
 * \param timer timer where to add callback.
 * \param callback callback to add.
 * 
 * \note Callback will be added if `timer` and `callback`
 *       is not `NULL`, otherwise nothing will happen.
 */
void timer__add_callback(
  timer_t_ *timer,
  timer_callback_fn callback
);

/**
 * \brief Disables timer with the given id.
 * 
 * \param timer timer to disable.
 */
void timer__disable(timer_t_ *timer);

/**
 * \brief Enables timer with the given id.
 * 
 * \param timer timer to enable.
 */
void timer__enable(timer_t_ *timer);

/**
 * \brief Toggles timer state, i.e. enables it if it is
 *        disabled, and disables if enabled.
 * 
 * \param timer timer to toggle state.
 */
void timer__toggle(timer_t_ *timer);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIMER_H_INCLUDED_ */
