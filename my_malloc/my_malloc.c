#include "main.h"

/*
 * _malloc - function that returns a size in bytes of memory
 * block
 * @size: size in bytes of memory to be allocated
 *
 * Return: pointer to allocated memory or NULL
 */
void *_malloc(size_t size)
{
	size_t total_size;

	void *block;
	header_t *allocated_header;
	if (!size)
		return (NULL);
	pthread_mutex_lock(&global_malloc_lock);
	allocated_header = get_free_block(size);
	if (allocated_header)
	{
		allocated_header>s.is_free = 0;
		pthread_mutex_unlock(&global_malloc_lock);
		return (void *)(allocated_header + 1);
	}

	total_size = sizeof(header_t) + size;
	block = sbrk(total_size);
	if (block == (void*) -1)
	{
		pthread_mutex_unlock(&global_malloc_lock);
		return (NULL);
	}

	allocated_header = block;
	allocated_header>s.size = size;
	allocated_header>s.is_free = 0;
	allocated_header>s.next = NULL;
	if (!head)
		head = allocated_header;
	if (tail)
		tail->s.next = allocated_header;
	tail = allocated_header;
	pthread_mutex_unlock(&global_malloc_lock);
	return (void*)(allocated_header + 1);
}
