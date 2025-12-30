#include <stdio.h>
#include "types.h"
#include "display.h"

void creatureList_simplePrint(Creature* head){
    for(Creature* cr = head; cr != NULL; cr = cr->next){
        printf(
            "%s (%s)\n"
            "  ostatnio karmiony %s\n"
            "  moc %f, nieb %i, stan %s\n",
            cr->name, cr->gatunek,
            cr->last_feeding_date,
            cr->magic_power, cr->danger_level, gc_creature_state_names[cr->state]
        );
    }
}

