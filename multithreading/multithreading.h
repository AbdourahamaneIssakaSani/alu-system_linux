#ifndef MULTITHREADING_H
#define MULTITHREADING_H
#include <pthread.h> /* pthread_t, pthread_create, pthread_join */
#include <stdint.h> /* uint32_t */
#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */
#include "list.h"

pthread_mutex_t tprintf_mutex;
pthread_mutex_t tasks_mutex;

/**
* struct pixel_s - RGB pixel
*
* @r: Red component
* @g: Green component
* @b: Blue component
*/
typedef struct pixel_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

/**
* struct img_s - Image
*
* @w:      Image width
* @h:      Image height
* @pixels: Array of pixels
*/
typedef struct img_s
{
	size_t w;
	size_t h;
	pixel_t *pixels;
} img_t;

/**
* struct kernel_s - Convolution kernel
*
* @size:   Size of the matrix (both width and height)
* @matrix: Kernel matrix
*/
typedef struct kernel_s
{
	size_t size;
	float **matrix;

} kernel_t;

/**
* struct blur_portion_s - Information needed to blur a portion of an image
*
* @img:      Source image
* @img_blur: Destination image
* @x:        X position of the portion in the image
* @y:        Y position of the portion in the image
* @w:        Width of the portion
* @h:        Height of the portion
* @kernel:   Convolution kernel to use
*/
typedef struct blur_portion_s
{
	img_t const *img;

	img_t *img_blur;
	size_t x;
	size_t y;
	size_t w;
	size_t h;
	kernel_t const *kernel;

} blur_portion_t;

typedef void *(*task_entry_t)(void *);

/**
* enum task_status_e - Task status
*
* @PENDING: Task is pending
* @STARTED: Task has started
* @SUCCESS: Task has completed successfully
* @FAILURE: Task has completed with issues
*/
typedef enum task_status_e
{
	PENDING = 0,
	STARTED,
	SUCCESS,
	FAILURE,
	TASK_STATUS_MAX /* Number of task statuses */
} task_status_t;

/**
* struct task_s - Executable task structure
*
* @entry:  Pointer to a function to serve as the task entry
* @param:  Address to a custom content to be passed to the entry function
* @status: Task status, default to PENDING
* @result: Stores the return value of the entry function
* @lock:   Task mutex
*/
typedef struct task_s
{
	task_entry_t entry;
	void *param;

	task_status_t status;
	void *result;

	pthread_mutex_t lock;
	unsigned int id;

} task_t;

/*Functions prototypes*/
void *thread_entry(void *arg);
int tprintf(char const *format, ...);
void blur_portion(blur_portion_t const *portion);
#endif /*MULTITHREADING_H*/

