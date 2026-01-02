#include <stdio.h>
#include <string.h>
#include "types.h"
#include "display.h"

void creatureList_print(Creature* head){
    if(head == NULL){
        printf("Pusta lista.");
        return;
    }

    int max_name_len    = 5;
    int max_species_len = 7;

    for(Creature* cr = head; cr != NULL; cr = cr->next){
        int name_len = strlen(cr->name);
        if(name_len > max_name_len) max_name_len = name_len;
        int species_len = strlen(cr->gatunek);
        if(species_len > max_species_len) max_species_len = species_len;
    }

    printf("%*s  %*s  karmiony    moc magiczna  niebezpieczenstwo  stan\n", -max_name_len, "nazwa", -max_species_len, "gatunek");
    for(Creature* cr = head; cr != NULL; cr = cr->next){
        printf(
            "%*s  %*s  %-10s  %12.2f  %17i  %s\n",
            -max_name_len, cr->name,
            -max_species_len, cr->gatunek,
            cr->last_feeding_date,
            cr->magic_power,
            cr->danger_level,
            gc_creature_state_names[cr->state]
        );
    }
}

