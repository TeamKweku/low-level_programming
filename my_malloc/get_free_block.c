#include "main.h"

/*
 * get_free_block - function that checks for free block 
 * of memory greater or equal to the requested
 * and returns memory block to be used by calling 
 * function
 * @size: size in bytes requested be calling function
 *
 * Return: free memory block is available or NULL
 */

header_t *get_free_block(size_t size)
{
	header_t *current = head;
	while (current)
	{
		if (current->s.is_free && current->s.size >= size)
			return (current);
		current = current->s.next;
	}

	return (NULL);
}
