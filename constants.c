#include "types.h"

const char* const gc_creature_state_names[creature_state_count] = {
    [creature_state_stable]     = "stabilny",
    [creature_state_anxious]    = "niespokojny",
    [creature_state_aggressive] = "agresywny",
    [creature_state_dangerous]  = "niebezpieczny",
    [creature_state_quarantine] = "w kwarantannie",
};
