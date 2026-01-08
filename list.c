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

bool creatureList_deleteByName(Creature** head, const char* name){
    if(head == NULL) return false;
    Creature** ptr = head;
    while(*ptr != NULL){
        if(!strcmp((*ptr)->name, name)){
            Creature* next = (*ptr)->next;
            free(*ptr);
            *ptr = next;
            return true;
        }
        ptr = &(*ptr)->next;
    }
    return false;
}

int creatureList_deleteByMagicPowerLessThan(Creature** head, float magic_power){
    if(head == NULL) return 0;
    Creature** ptr = head;
    int n = 0;
    while(true){
        while(*ptr != NULL && (*ptr)->magic_power < magic_power){
            Creature* next = (*ptr)->next;
            free(*ptr);
            *ptr = next;
            n++;
        }
        if(*ptr == NULL) break;
        ptr = &(*ptr)->next;
    }
    return n;
}

Creature* creatureList_filterBySpecies(const Creature* head, const char* species){
    Creature* new_head = NULL;
    Creature* new_tail = NULL;
    for(const Creature* cr = head; cr != NULL; cr = cr->next){
        if(!strcmp(cr->gatunek, species)){
            Creature* copy = calloc(1, sizeof(*copy));
            memcpy(copy, cr, sizeof(*copy));
            copy->next = NULL;
            if(new_head == NULL){
                new_head = copy;
                new_tail = copy;
            }
            else{
                new_tail->next = copy;
                new_tail = copy;
            }
        }
    }
    return new_head;
}

Creature* creatureList_filterBySpeciesPrefix(const Creature* head, const char* species_prefix){
    Creature* new_head = NULL;
    Creature* new_tail = NULL;
    size_t prefix_len = strlen(species_prefix);
    for(const Creature* cr = head; cr != NULL; cr = cr->next){
        if(strlen(cr->gatunek) >= prefix_len && !memcmp(cr->gatunek, species_prefix, prefix_len)){
            Creature* copy = calloc(1, sizeof(*copy));
            memcpy(copy, cr, sizeof(*copy));
            copy->next = NULL;
            if(new_head == NULL){
                new_head = copy;
                new_tail = copy;
            }
            else{
                new_tail->next = copy;
                new_tail = copy;
            }
        }
    }
    return new_head;
}

Creature* creatureList_filterByDangerLevel(const Creature* head, int danger_level){
    Creature* new_head = NULL;
    Creature* new_tail = NULL;
    for(const Creature* cr = head; cr != NULL; cr = cr->next){
        if(cr->danger_level == danger_level){
            Creature* copy = calloc(1, sizeof(*copy));
            memcpy(copy, cr, sizeof(*copy));
            copy->next = NULL;
            if(new_head == NULL){
                new_head = copy;
                new_tail = copy;
            }
            else{
                new_tail->next = copy;
                new_tail = copy;
            }
        }
    }
    return new_head;
}

void creatureList_sortByName(Creature** head){
    if(head == NULL || *head == NULL || (*head)->next == NULL) return;
    for(Creature* cr_prev = (*head); cr_prev != NULL && cr_prev->next != NULL;){
        Creature* cr = cr_prev->next;

        Creature** dest_ptr = head;
        while(*dest_ptr != NULL && *dest_ptr != cr){
            if(strcmp((*dest_ptr)->name, cr->name) > 0){
                // usuń element z listy
                cr_prev->next = cr->next;
                // wstaw element w nowe miejsce w liście
                cr->next = *dest_ptr;
                *dest_ptr = cr;
                // nie iteruj dalej w liste bo cr_prev->next się zmeinił
                cr = cr_prev;
                break;
            }
            dest_ptr = &(*dest_ptr)->next;
        }

        cr_prev = cr;
    }
}

void creatureList_sortByMagicPower(Creature** head){
    if(head == NULL || *head == NULL || (*head)->next == NULL) return;
    for(Creature* cr_prev = (*head); cr_prev != NULL && cr_prev->next != NULL;){
        Creature* cr = cr_prev->next;

        Creature** dest_ptr = head;
        while(*dest_ptr != NULL && *dest_ptr != cr){
            if((*dest_ptr)->magic_power > cr->magic_power){
                // usuń element z listy
                cr_prev->next = cr->next;
                // wstaw element w nowe miejsce w liście
                cr->next = *dest_ptr;
                *dest_ptr = cr;
                // nie iteruj dalej w liste bo cr_prev->next się zmeinił
                cr = cr_prev;
                break;
            }
            dest_ptr = &(*dest_ptr)->next;
        }

        cr_prev = cr;
    }    
}
