/**
 * \file point.h
 * \brief Contains different variants of point structures.
 */

#ifndef POINT_H_INCLUDED_
#define POINT_H_INCLUDED_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * \brief 2-dimensional point with integer components.
 */
typedef struct point2d {
  int32_t x;
  int32_t y;
} point2d_t;

/**
 * \brief 2-dimensional point with float components.
 */
typedef struct point2df {
  float x;
  float y;
} point2df_t;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* POINT_H_INCLUDED_ */
