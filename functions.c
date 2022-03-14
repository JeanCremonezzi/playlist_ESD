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

        musicNode->ant = NULL;

    } else {
        newMusica->id = header->last->musica->id + 1;

        musicNode->ant = header->last;

        header->last->prox = musicNode;
        header->last = musicNode;
    }

    musicNode->prox = NULL;
    header->count++;

    return musicNode;
}

void printMusics(musicsHeader* header) {
    if (header->count == 0) {
        printf("\nNo musics found!\n");

    } else {
        musica_node* node = header->first;

        printf("\n\nMusics list:\n");

        while (1) {
            musica* music = node->musica;
            printf("\nTrack ID %d: %s - %s", music->id, music->titulo, music->artista);
            printf("\nAlbum: %s", music->album);

            int h = music->duracao / 3600;
            int m = (music->duracao / 60) % 60;
            int s = music->duracao % 60;

            printf("\nDuration: %02d:%02d:%02d\n", h, m, s);

            if (node->prox == NULL) {
                break;
            }

            node = node->prox;
        }
    }

    printf("\n------------------------------------------------------");
};

musica* getMusic(int id, musicsHeader* header) {

    if (header->count > 0 && id > 0) {
        musica_node* actualNode = header->first;

        while(1) {
            if (actualNode->musica->id == id) {
                return actualNode->musica;
            }

            if (actualNode->prox == NULL) {
                return NULL;
            }

            actualNode = actualNode->prox;
        }
    }

    return NULL;
}