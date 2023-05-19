#ifndef MAIN_H
#define MAIN_H 

typedef char ALIGN[16];

union header
{
	struct
	{
		size_t size;
		unsigned is_free;
		union header *next;
	}s;
	ALIGN stub;
};

typedef union header_t;

/* pointers to keep track of the begining and 
 * end of list */
header_t *head, *tail;

/* variable to use to prevent more threads from concurrently
 * accessing memory */
pthread_mutex_t global_malloc_lock;

header_t *get_free_block(size_t);

#endif
