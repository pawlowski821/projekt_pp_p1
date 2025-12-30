#ifndef PROJEKT_FILEIO_H
#define PROJEKT_FILEIO_H

#include <stdbool.h>
#include "types.h"

bool creatureList_loadFromFile(Creature** head, const char* path);
bool creatureList_writeToFile(Creature* head, const char* path);

#endif
