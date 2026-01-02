#ifndef PROJEKT_VALIDATE_H
#define PROJEKT_VALIDATE_H

#include <stdbool.h>
#include "types.h"

bool isValidDate(const char* text);

bool isValidState(CreatureState state);

bool isValidDangerLevel(int danger_level);

bool isValidMagicPower(float magic_power);

#endif
