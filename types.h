#ifndef PROJEKT_TYPES_H
#define PROJEKT_TYPES_H

#define DANGER_LEVEL_MIN 0
#define DANGER_LEVEL_MAX 10

#define DATE_TEXT_SIZE 11
#define GATUNEK_TEXT_SIZE 21
#define NAME_TEXT_SIZE 101

typedef enum{
    creature_state_first,
    creature_state_stable = creature_state_first,
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
    char          name[NAME_TEXT_SIZE];              // unikatowe, identyfikator, nie można zmieniać po dodaniu do rejestru
    char          gatunek[GATUNEK_TEXT_SIZE];        // gatunek - nazwa gatunku lub typu istoty, np. smok, gryf, feniks, pegaz, mantykora;
    char          last_feeding_date[DATE_TEXT_SIZE]; // yyyy-mm-dd
    float         magic_power;
    int           danger_level;                      // 0 - 10
    CreatureState state;                             // odmowa usunięcia wpisu jeżeli dangerous
};

#endif
