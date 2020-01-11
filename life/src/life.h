#ifndef LIFE_H
#define LIFE_H

#include "linked_list.h"

struct life_s;

struct life_s *life_begin(char matrix[], int width, int height);

void life_update(struct life_s* life);

void life_draw(struct life_s* life);

void life_end(struct life_s* life);

linked_list_t life_get_cells(struct life_s *life);

int life_count_neighbor(int x, int y, linked_list_t *cells);

#endif // LIFE_H
