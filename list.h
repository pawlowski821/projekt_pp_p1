#ifndef PROJEKT_LIST_H
#define PROJEKT_LIST_H

#include <stdbool.h>
#include "types.h"

Creature** creatureList_getLastNextPointer(Creature** head);

bool creatureList_append(Creature** head, const Creature* src);
void creatureList_free(Creature** head);

Creature* creatureList_findByName(Creature* head, const char* name);

#endif
