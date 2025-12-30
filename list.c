#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

Creature** creatureList_getLastNextPointer(Creature** head){
    if(*head == NULL) return head;
    Creature* last = *head;
    while(last->next != NULL) last = last->next;
    return &last->next;
}

bool creatureList_append(Creature** head, const Creature* src){
    if(creatureList_findByName(*head, src->name) != NULL){
        fprintf(stderr, "Nie mozna dodac stworzenia o imieniu \"%s\", tak nazwane stworzenie juz istnieje\n", src->name);
        return false;
    }

    Creature* new_creature = calloc(1, sizeof(*new_creature));
    if(new_creature == NULL){
        fprintf(stderr, "Alokacja pamieci sie nie powiodla");
        return false;
    }

    *new_creature = *src;

    Creature** last_next = creatureList_getLastNextPointer(head);
    *last_next = new_creature;
    return true;
}

void creatureList_free(Creature** head){
    Creature* cr = *head;
    while(cr != NULL){
        Creature* next = cr->next;
        free(cr);
        cr = next; 
    }
    *head = NULL;
}

Creature* creatureList_findByName(Creature* head, const char* name){
    for(Creature* cr = head; cr != NULL; cr = cr->next){
        if(!strcmp(cr->name, name)) return cr;
    }
    return NULL;
}
