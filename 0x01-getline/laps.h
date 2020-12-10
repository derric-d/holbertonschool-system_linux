#ifndef LAPS_H
#define LAPS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct car_l - list of car enitities
 * @id: id of car instance
 * @laps: laps car has driven
 * @next: pointer to next car
 */
typedef struct car_l
{
	int id;
	size_t laps;
	struct car_l *next;
} Car_l;

void race_state(int *id, size_t size);

#endif
