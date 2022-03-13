#include "header.h"

musicsHeader* init() {
    musicsHeader* ptrHeader = malloc(sizeof(musicsHeader));

    ptrHeader->first = NULL;
    ptrHeader->last = NULL;
    ptrHeader->count = 0;

    return ptrHeader;
}

musica* createMusic(char* title, char* artist, char* album, int duration) {
    musica* newMusic = malloc(sizeof(musica));

    strcpy(newMusic->titulo, title);
    strcpy(newMusic->artista, artist);
    strcpy(newMusic->album, album);
    newMusic->duracao = duration;

    return newMusic;
}

musica_node* insertMusic(musicsHeader* header, char* title, char* artist, char* album, int duration) {
    musica_node* musicNode = malloc(sizeof(musica_node));

    musica* newMusica = createMusic(title, artist, album, duration);
    musicNode->musica = newMusica;

    if (header->count == 0) {
        newMusica->id = 1;

        header->first = musicNode;
        header->last = musicNode;

    } else {
        newMusica->id = header->last->musica->id + 1;

        musicNode->prox = NULL;
        musicNode->ant = header->last;

        header->last->prox = musicNode;
        header->last = musicNode;
    }

    header->count++;

    return musicNode;
}

void printMusics(musicsHeader* header) {
    if (header->count == 0) {
        printf("\n No musics found!");

    } else {
        musica_node* node = header->first;

        printf("\n\n Musics list:\n");

        while (1) {
            printf("\n Track ID %d: %s - %s", node->musica->id, node->musica->titulo, node->musica->artista);
            printf("\n Album: %s\n", node->musica->album);

            if (node->prox == NULL) {
                break;
            }

            node = node->prox;
        }
    }
};