#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "validate.h"

bool isValidDate(const char* text){
    // yyyy-mm-dd
    // 0123456789
    if(strlen(text) < 10) return false;
    if(text[4] != '-' || text[7] != '-') return false;
    if(!isdigit(text[0]) || !isdigit(text[1]) || !isdigit(text[2]) || !isdigit(text[3])) return false;
    if((text[5] != '0' && text[5] != '1') || !isdigit(text[6])) return false;
    if(text[5] == '1' && text[6] > '2') return false;
    if(text[5] == '0' && text[6] == '0') return false;
    if(!isdigit(text[8]) || !isdigit(text[9])) return false;
    return true;
}

bool isValidState(CreatureState state){
    return state >= creature_state_first && state < creature_state_count;
}

bool isValidDangerLevel(int danger_level){
    return danger_level >= DANGER_LEVEL_MIN && danger_level <= DANGER_LEVEL_MAX;
}

bool isValidMagicPower(float magic_power){
    return magic_power >= 0.0f;
}
