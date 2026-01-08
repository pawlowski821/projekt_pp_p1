#ifndef PROJEKT_LIST_H
#define PROJEKT_LIST_H

#include <stdbool.h>
#include "types.h"

Creature** creatureList_getLastNextPointer(Creature** head);

bool creatureList_append(Creature** head, const Creature* src);
void creatureList_free(Creature** head);

Creature* creatureList_findByName(Creature* head, const char* name);

bool creatureList_deleteByName(Creature** head, const char* name);
int creatureList_deleteByMagicPowerLessThan(Creature** head, float magic_power);

Creature* creatureList_filterBySpecies(const Creature* head, const char* species);
Creature* creatureList_filterBySpeciesPrefix(const Creature* head, const char* species_prefix);
Creature* creatureList_filterByDangerLevel(const Creature* head, int danger_level);

void creatureList_sortByName(Creature** head);
void creatureList_sortByMagicPower(Creature** head);

#endif
