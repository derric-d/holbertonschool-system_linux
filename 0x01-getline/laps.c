#include "laps.h"

/**
 * insert_node - add car (node) to linked list of cars
 * @head: start of the list
 * @id: new id value for car
 */
void insert_node(Car_l **head, int id)
{
	Car_l *new_c, *end;

	if (!*head || id < (*head)->id)
	{
		new_c = malloc(sizeof(Car_l));

		if (!new_c)
			/*cant use exit?*/
			fprintf(stderr, "malloc fail\n");

		new_c->id = id;
		new_c->laps = 0;
		new_c->next = *head;
		*head = new_c;
		printf("Car %d joined the race\n", id);
		return;
	}
	for (new_c = *head; new_c->next && new_c->next->id <= id; new_c = new_c->next)
		;
	if (new_c->id == id)
	{
		new_c->laps++;
		return;
	}
	end = malloc(sizeof(Car_l));
	if (!end)
		/*cant use exit*/
		fprintf(stderr, "malloc fail\n");

	end->id = id;
	end->laps = 0;
	end->next = new_c->next;
	new_c->next = end;
	printf("Car %d joined the race\n", id);
}

/**
 * race_state - accesses list and reads member data
 * @id: is of car we want to access
 * @size: size of list we are using
 */
void race_state(int *id, size_t size)
{
	static Car_l *head, *temp;
	size_t i;

	i = 0;
	temp = head;

	if (!size)
	{
		while (head)
		{
			temp = head;
			head = head->next;
			free(temp);
		}
		return;
	}

	for (i = 0; i < size; i++)
	{
		insert_node(&head, id[i]);
	}

	printf("Race state:\n");
	for (temp = head; temp; temp = temp->next)
	{
		printf("Car %d [%lu laps]\n", temp->id, temp->laps);
	}
}
