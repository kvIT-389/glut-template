/**
 * \file timer.c
 * \brief Contains timer functions implementation.
 */

#include "callback/timer.h"
#include "callback/prv_timer.h"

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>

#include "ccl/vector.h"
#include "ccl/list.h"


/**
 * \brief Hidden (private) array (vector) of all created timers.
 */
vector_t *timers;


timer_t_ *timer__create(const uint32_t interval) {
    /* New timer pointer. */
    timer_t_ *timer;

    timer = malloc(sizeof(timer_t_));

    *timer = (timer_t_){
        vector__size(timers),
        interval,
        TIMER_DISABLED,
        list__create()
    };

    if (timers == NULL) {
        timers = vector__create(0);
    }

    vector__push_back(timers, timer);

    return timer;
}

void timer__free(timer_t_ *timer) {
    if (timer == NULL) {
        return;
    }

    list__free(timer->callbacks);
    vector__set(timers, timer->id, NULL);
}


timer_state_t timer__state(const timer_t_ *timer) {
    return (timer == NULL) ? (TIMER_DISABLED) : (timer->state);
}

uint8_t timer__disabled(const timer_t_ *timer) {
    return timer__state(timer) == TIMER_DISABLED;
}

uint8_t timer__enabled(const timer_t_ *timer) {
    return timer__state(timer) == TIMER_ENABLED;
}


void timer__add_callback(
    timer_t_ *timer,
    timer_callback_fn callback
) {
    if (timer == NULL || callback == NULL) {
        return;
    }

    list__push_back(timer->callbacks, callback);
}


void timer__disable(timer_t_ *timer) {
    if (timer__disabled(timer)) {
        return;
    }

    timer->state = TIMER_DISABLED;
}

void timer__enable(timer_t_ *timer) {
    if (timer == NULL || timer__enabled(timer)) {
        return;
    }

    timer->state = TIMER_ENABLED;
    timer_wrapper(timer->id);
}

void timer__toggle(timer_t_ *timer) {
    if (timer__disabled(timer)) {
        timer__enable(timer);
    } else {
        timer__disable(timer);
    }
}


void timer_wrapper(int32_t timer_id) {
    /* Timer callbacks iterator. */
    list_iterator_t it;

    /* Timer with id equals to `timer_id` if exists. */
    timer_t_ *timer;

    timer = vector__at(timers, timer_id);

    if (timer__disabled(timer)) {
        return;
    }

    glutTimerFunc(timer->interval, timer_wrapper, timer->id);

    it = list__begin(timer->callbacks);
    while (!list_iterator__ended(&it)) {
        ((timer_callback_fn)list_iterator__get(&it))();

        list_iterator__next(&it);
    }
}
