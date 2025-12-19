#ifndef PROJEKT_TYPES_H
#define PROJEKT_TYPES_H

typedef enum{
    creature_state_stable,
    creature_state_anxious,
    creature_state_aggressive,
    creature_state_dangerous,
    creature_state_quarantine
}CreatureState;

extern const char* const gc_creature_state_names[];

typedef struct Creature Creature;
struct Creature{
    char          name[101];         // unikatowe, identyfikator, nie można zmieniać po dodaniu do rejestru
    const char*   gatunek;           // gatunek - nazwa gatunku lub typu istoty, np. smok, gryf, feniks, pegaz, mantykora;
    float         magic_power;
    int           danger_level;      // 0 - 10
    char          last_feeding_date; // yyyy-mm-dd
    CreatureState state;             // odmowa usunięcia wpisu jeżeli dangerous
};

#endif
