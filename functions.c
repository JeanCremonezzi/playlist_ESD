#include "header.h"

musicsHeader* init() {
    musicsHeader* ptrHeader = malloc(sizeof(musicsHeader));

    ptrHeader->first = NULL;
    ptrHeader->last = NULL;
    ptrHeader->count = 0;

    return ptrHeader;
}

playlistsHeader* initPlaylists() {
    playlistsHeader* ptrHeader = malloc(sizeof(playlistsHeader));

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

lplaylists_node* newPlaylist(playlistsHeader* playlists, musicsHeader* musics) {
    lplaylists_node* playlist = malloc(sizeof(lplaylists_node));
    playlist->musicas = NULL;
    playlist->prox = NULL;

    printf("\nNew Playlist");

    printf("\nPlaylist name: ");
    fflush(stdin);
    fgets(playlist->nome, STRING_SIZE, stdin);

    printMusics(musics);

    playlist_node* lastMusicInserted;

    printf("\nMusics to insert in playlist: ");

    fflush(stdin);
    while (1) {
        int idSelected;

        scanf("%d", &idSelected);

        if (idSelected <= 0) {
            break;
        }

        musica* selectedMusic = getMusic(idSelected, musics);

        if (selectedMusic != NULL) {
            playlist_node* node = malloc(sizeof(playlist_node));
            node->musica = selectedMusic;

            if (playlist->musicas == NULL) {
                node->prox = node;
                playlist->musicas = node;
            } else {
                lastMusicInserted->prox = node;
                node->prox = playlist->musicas;
            }

            lastMusicInserted = node;
        }
    }

    playlist->id = playlists->count + 1;
    
    if (playlists->count == 0) {
        playlists->first = playlist;
        playlists->last = playlist;
    } else {
        playlists->last->prox = playlist;
        playlists->last = playlist;
    }

    playlists->last->prox = playlist;

    playlist->prox = NULL;

    playlists->count++;

    return playlist;
}

void printMusic(musica* music) {
    printf("\nTrack ID %d: %s - %s", music->id, music->titulo, music->artista);
    printf("\nAlbum: %s", music->album);

    int h = music->duracao / 3600;
    int m = (music->duracao / 60) % 60;
    int s = music->duracao % 60;

    printf("\nDuration: %02d:%02d:%02d\n", h, m, s);
}

void printMusics(musicsHeader* header) {
    if (header->count == 0) {
        printf("\nNo musics found!\n");

    } else {
        musica_node* node = header->first;

        printf("\n\nMusics list:\n");

        while (1) {
            printMusic(node->musica);
            
            if (node->prox == NULL) {
                break;
            }
            
            node = node->prox;
        }
    }

    printf("\n------------------------------------------------------");
};

void printPlayListById (playlistsHeader* playlists, int id) {
    if (playlists->count != 0) {
        lplaylists_node* actualNode = playlists->first;

        while (1) {
            if (actualNode->id == id) {
                printPlayList(actualNode);
                return;
            }

            if (actualNode->prox == NULL) {
                printf("\n\nPlaylist not found.");
                return;
            }

            actualNode = actualNode->prox;
        }
    }

    printf("\n\nNo playlists created.");
};

void printPlayList(lplaylists_node* playlist) {
    if (playlist->musicas != NULL) {
        printf("\ntracks from %s", playlist->nome);

        playlist_node* actualNode;
        actualNode = playlist->musicas;

        while (1) {
            printMusic(actualNode->musica);

            if (actualNode->prox == playlist->musicas || actualNode->prox == NULL) {
                break;
            }

            actualNode = actualNode->prox;
        }

        printf("\n------------------------------------------------------");
        return;
    }

    printf("\n\nPlaylist %d has no musics.", playlist->id);
}

void deleteFromPlaylists(musica* musicToDelete, playlistsHeader* playlists) {
    // Refatorar código - principalmente linhas com /***/ 

    if (playlists->count <= 0) {
        return;
    }

    // Percorre todas as playlists
    lplaylists_node* actualPlaylist = playlists->first;
    while (1) {

        // Percorre todas as músicas da playlist
        playlist_node* actualMusicNode = actualPlaylist->musicas;
        if (actualMusicNode != NULL) {

            playlist_node* prevMusicNode = actualPlaylist->musicas;
            while (1) {

                // Se encontrar a música
                if (actualMusicNode->musica == musicToDelete) {
                    
                    // Se for a única
                    if (actualMusicNode == actualPlaylist->musicas && actualMusicNode->prox == actualPlaylist->musicas) {
                        actualPlaylist->musicas = NULL;
                        break;
                    }

                    // Se for a primeira música
                    if (actualMusicNode == actualPlaylist->musicas) {

                        // Muda o prox do ultimo
                        playlist_node* lastNode = actualMusicNode;
                        while (1) {
                            if (lastNode->prox == actualPlaylist->musicas) {
                                lastNode->prox = actualPlaylist->musicas->prox;
                                break;
                            }

                            lastNode = lastNode->prox;
                        }

                        actualPlaylist->musicas = actualMusicNode->prox;
                        prevMusicNode = actualPlaylist->musicas;

                        free(actualMusicNode); /***/
                        actualMusicNode = prevMusicNode; /***/

                        continue; /***/
                    } else {
                        prevMusicNode->prox = actualMusicNode->prox;

                        free(actualMusicNode); /***/
                        actualMusicNode = prevMusicNode; /***/

                        continue; /***/
                    }
                    
                    //free(actualMusicNode);
                    //actualMusicNode = prevMusicNode;
                }

                if (actualMusicNode->prox == actualPlaylist->musicas) {
                    break;
                }

                prevMusicNode = actualMusicNode;
                actualMusicNode = actualMusicNode->prox;
            }
        }

        if (actualPlaylist->prox == NULL) {
            return;
        }

        actualPlaylist = actualPlaylist->prox;
    }
}

void deleteMusicById(musicsHeader* header, playlistsHeader* playlists, int id) {
    // Refatorar código - principalmente linhas com /***/ 

    if (id <= 0) {
        printf("\nInvalid Music or ID.");
        return;
    }

    musica* musicToDelete = getMusic(id, header);
    if (musicToDelete == NULL) {
        printf("\nMusic not found.");
        return;
    }

    musica_node* nodeMusicDelete = header->first;

    // Deleta de playlists
    deleteFromPlaylists(musicToDelete, playlists);

    while (1) {
        // Deleta da lista de músicas
        if (nodeMusicDelete->musica == musicToDelete) {
            header->count--;

            if (nodeMusicDelete == header->first && nodeMusicDelete == header->last) {
                header->first = NULL;
                header->last = NULL;

                free(nodeMusicDelete); /***/
                break; /***/
            }

            if (nodeMusicDelete == header->first) {
                nodeMusicDelete->prox->ant = NULL;
                header->first = nodeMusicDelete->prox;

                free(nodeMusicDelete); /***/
                break; /***/
            }
            
            if (nodeMusicDelete == header->last) {
                nodeMusicDelete->ant->prox = NULL;
                header->last = nodeMusicDelete->ant;

                free(nodeMusicDelete); /***/
                break; /***/
            }

            nodeMusicDelete->ant->prox = nodeMusicDelete->prox;
            nodeMusicDelete->prox->ant = nodeMusicDelete->ant;
            
            free(nodeMusicDelete); /***/
            break; /***/
        }

        if (nodeMusicDelete->prox == NULL) {
            return;
        }

        nodeMusicDelete = nodeMusicDelete->prox;
    }

    free(musicToDelete);
}

void deleteMusic(musicsHeader* header, playlistsHeader* playlists, musica* music) {
    deleteMusicById(header, playlists, music->id);
}

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