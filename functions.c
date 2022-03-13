#include "header.h"

musica_node* initMusics() {
    musica_node* ptrList = malloc(sizeof(musica_node));

    ptrList->ant = NULL;
    ptrList->prox = NULL;
    ptrList->musica = NULL;

    return ptrList;
}