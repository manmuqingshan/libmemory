/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stdlib.h>

/** Notes on Thread Safety
 *
 * Thread safety varies by implementation.
 *
 * RTOS-based implementations may or may not be thread-safe depending on the RTOS and chosen heap
 * configuration.
 *
 * The freelist implementation is not thread-safe by default. If you are using this version on a
 * threaded system, you need to define two functions within your program:
 *
 * @code
 * void malloc_lock();
 * void malloc_unlock();
 * @endcod
 *
 * These should lock and unlock a mutex that is associated with memory allocation.
 *
 * @code
 * mutex_t malloc_mutex;
 *
 * void malloc_lock()
 * {
 * 		mutex_lock(&malloc_mutex);
 * }
 *
 * void malloc_unlock()
 * {
 * 		mutex_unlock(&malloc_mutex);
 * }
 * @endcode
 *
 * These functions are defined as weakly linked in the library, so the default no-op condition will
 * not be used if your functions is found by the linker. If you're doubtful that your calls are
 * being included, check the disassembly for the functions - your version will not be no-ops!
 */

/**
 * @brief Assign blocks of memory for use by malloc().
 *
 * Initializes the malloc() backend with a memory address and memory pool size.
 *	This memory is assumed to be owned by malloc() and is vended out when memory is requested.
 * 	Multiple blocks can be added.
 *
 * NOTE: This API must be called before malloc() can be used. If you call malloc() before
 * 	allocating memory, malloc() will return NULL because there is no available memory
 *	to provide to the user.
 *
 * @param addr Pointer to the memory block address that you are providing to malloc()
 * @param size Size of the memory block that you are providing to malloc()
 */
void malloc_addblock(void* addr, size_t size);

/**
 * @brief Initialize Malloc
 *
 * Weakly linked, can be overridden based on your needs.
 * Each malloc implementation contains a different set of initialization requirements
 */
void malloc_init(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // MALLOC_H_
