/**
 * \file vector.h
 * \brief Contains different variants of vector structures.
 */

#ifndef VECTOR_H_INCLUDED_
#define VECTOR_H_INCLUDED_

#include "geometry/point.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * \brief 2-dimensional vector with integer components.
 */
typedef point2d_t vector2d_t;

/**
 * \brief 2-dimensional vector with float components.
 */
typedef point2df_t vector2df_t;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VECTOR_H_INCLUDED_ */
