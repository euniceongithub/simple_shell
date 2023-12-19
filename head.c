#include "shell.h"

/**
 * headToNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: index used by history
 *
 * Return: number of bytes of list.
 */
list_t *headToNode(list_t **head, const char *str, int num)
{
	list_t *newNodeHead;

	if (!head)
		return (NULL);
	newNodeHead = malloc(sizeof(list_t));
	if (!newNodeHead)
		return (NULL);
	fillMem((void *)newNodeHead, 0, sizeof(list_t));
	newNodeHead->num = num;
	if (str)
	{
		newNodeHead->str = stringDup(str);
		if (!newNodeHead->str)
		{
			free(newNodeHead);
			return (NULL);
		}
	}
	newNodeHead->next = *head;
	*head = newNodeHead;
	return (newNodeHead);
}

/**
 * tailToNode - adds a node to the end of the list
 * @head: address of pointer to head
 * @str: str field of node
 * @num: index used by history
 *
 * Return: number of bytes occupied by list.
 */
list_t *tailToNode(list_t **head, const char *str, int num)
{
	list_t *newNodeTail, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNodeTail = malloc(sizeof(list_t));
	if (!newNodeTail)
		return (NULL);
	fillMem((void *)newNodeTail, 0, sizeof(list_t));
	newNodeTail->num = num;
	if (str)
	{
		newNodeTail->str = stringDup(str);
		if (!newNodeTail->str)
		{
			free(newNodeTail);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNodeTail;
	}
	else
		*head = newNodeTail;
	return (newNodeTail);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i;

	i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deleteNode - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure.
 */
int deleteNode(list_t **head, unsigned int index)
{
	list_t *node, *formerNode;
	unsigned int i;

	i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			formerNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		formerNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * freeNodes - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: NULL.
 */
void freeNodes(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
