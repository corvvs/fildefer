#include "ff_alloc.h"

/*
 * returns new element
 */
t_ff_block	*ff_push_block(t_ff_block *sentinel, void *block)
{
	t_ff_block	*tail;

	if (!block)
		return (NULL);
	tail = ff_new_block_list(block);
	if (!tail)
	{
		free(block);
		return (NULL);
	}
	tail->next = sentinel;
	tail->prev = sentinel->prev;
	sentinel->prev->next = tail;
	sentinel->prev = tail;
	sentinel->size += 1;
	return (tail);
}

/*
 * returns new element
 */
t_ff_block	*ff_new_block_list(void *block)
{
	t_ff_block	*tail;

	tail = (t_ff_block *)malloc(sizeof(t_ff_block));
	if (tail)
	{
		if (block)
			tail->block = block;
		tail->next = tail;
		tail->prev = tail;
	}
	return (tail);
}

/*
 * alloc a block and push it back to block-list.
 */
void	*ff_malloc(t_ff_block *sentinel, size_t	n)
{
	void	*block;

	block = malloc(n);
	if (!block)
		return (NULL);
	if (!ff_push_block(sentinel, block))
		return (NULL);
	return (block);
}

/*
 * free all blocks and elements, WITHOUT sentinel.
 */
size_t	ff_free(t_ff_block *sentinel)
{
	size_t		freed;
	t_ff_block	*head;

	head = sentinel->next;
	while (head != sentinel)
	{
		head = head->next;
		free(head->prev->block);
		free(head->prev);
	}
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
	freed = sentinel->size;
	sentinel->size = 0;
	return (freed);
}
