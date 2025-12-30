#ifndef PROJEKT_TYPES_H
#define PROJEKT_TYPES_H

#define DANGER_LEVEL_MIN 0
#define DANGER_LEVEL_MAX 10

typedef enum{
    creature_State_first,
    creature_state_stable = creature_State_first,
    creature_state_anxious,
    creature_state_aggressive,
    creature_state_dangerous,
    creature_state_quarantine,
    creature_state_count
}CreatureState;

extern const char* const gc_creature_state_names[creature_state_count];

typedef struct Creature Creature;
struct Creature{
    Creature*     next;
    char          name[101];             // unikatowe, identyfikator, nie można zmieniać po dodaniu do rejestru
    char          gatunek[21];           // gatunek - nazwa gatunku lub typu istoty, np. smok, gryf, feniks, pegaz, mantykora;
    char          last_feeding_date[11]; // yyyy-mm-dd
    float         magic_power;
    int           danger_level;          // 0 - 10
    CreatureState state;                 // odmowa usunięcia wpisu jeżeli dangerous
};

#endif
