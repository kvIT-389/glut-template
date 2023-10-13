/**
 * \file size.h
 * \brief Contains different variants of size structures.
 */

#ifndef SIZE_H_INCLUDED_
#define SIZE_H_INCLUDED_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * \brief 2-dimensional size with integer size components.
 */
typedef struct size2d {
  /* Width (horizontal) component. */
  int32_t w;

  /* Height (vertical) component. */
  int32_t h;
} size2d_t;

/**
 * \brief 2-dimensional size with float size components.
 */
typedef struct size2df {
  /* Width (horizontal) component. */
  float w;

  /* Height (vertical) component. */
  float h;
} size2df_t;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SIZE_H_INCLUDED_ */
