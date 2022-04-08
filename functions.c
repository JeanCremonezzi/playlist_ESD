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

musica* getMusic(int id, musicsHeader* header) {
    if (header->count > 0 && id > 0) {
        musica_node* actualNode = header->first;

        for (int i = 0; i < header->count; i++) {
            if (actualNode->musica->id == id) {
                return actualNode->musica;
            }

            actualNode = actualNode->prox;
        }
    }

    return NULL;
}

musica_node* insertMusic(musicsHeader* header, char* title, char* artist, char* album, int duration) {
    musica_node* musicNode = malloc(sizeof(musica_node));

    musicNode->musica = createMusic(title, artist, album, duration);

    if (header->count == 0) {
        musicNode->musica->id = 1;

        header->first = musicNode;
        musicNode->ant = NULL;

    } else {
        musicNode->musica->id = header->last->musica->id + 1;

        musicNode->ant = header->last;
        header->last->prox = musicNode;
    }

    header->last = musicNode;
    musicNode->prox = NULL;
    header->count++;

    return musicNode;
}

lplaylists_node* newPlaylist(playlistsHeader* playlists, musicsHeader* musics) {
    lplaylists_node* playlist = malloc(sizeof(lplaylists_node));
    playlist->musicas = NULL;
    playlist->prox = NULL;
    playlist->count = 0;
    playlist->id = playlists->count + 1;
    
    printf("\n-> Playlist name: ");
    fflush(stdin);
    fgets(playlist->nome, STRING_SIZE, stdin);

    printMusics(musics);
    printf("\n-> Select musics to insert in playlist: ");

    playlist_node* lastMusicInserted;

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

            if (playlist->count == 0) {
                node->prox = node;
                playlist->musicas = node;

            } else {
                lastMusicInserted->prox = node;
                node->prox = playlist->musicas;
            }

            lastMusicInserted = node;

            playlist->count++;
        }
    }
    
    if (playlists->count == 0) {
        playlists->first = playlist;
        playlists->last = playlist;
        
    } else {
        playlists->last->prox = playlist;
        playlists->last = playlist;
    }

    playlists->count++;

    return playlist;
}

lplaylists_node* getPlaylist(int id, playlistsHeader* playlists) {
    if (playlists->count > 0) {

        lplaylists_node* actualPlaylist = playlists->first;

        for (int i = 0; i < playlists->count; i++) {
            if (actualPlaylist->id == id) {
                return actualPlaylist;
            }

            actualPlaylist = actualPlaylist->prox;
        }
    }

    return NULL;
}

void printMusic(musica* music) {
    printf("\n--------------------");
    printf("\nTrack ID %d: %s", music->id, music->titulo);
    printf("\nArtist: %s", music->artista);
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

        for (int i = 0; i < header->count; i++) {
            printMusic(node->musica);
            
            node = node->prox;
        }
    }
};

void printPlayListById (playlistsHeader* playlists, int id) {
    lplaylists_node* playlist = getPlaylist(id, playlists);

    if (playlist == NULL) {
        printf("\n\nPlaylist not found.");
        return;
    }
    
    printPlayList(playlist);
};

void printPlayList(lplaylists_node* playlist) {
    if (playlist->count > 0) {
        printf("\n> Tracks from %s", playlist->nome);

        playlist_node* actualNode = playlist->musicas;

        for (int i = 0; i < playlist->count; i++) {
            printMusic(actualNode->musica);
            actualNode = actualNode->prox;
        }

        printf("\n-------------------");
        return;
    }

    printf("\n\nPlaylist #%d has no musics.", playlist->id);
}

void printPlayLists(playlistsHeader* playlists) {
    lplaylists_node* actualPlaylist;
    actualPlaylist = playlists->first;

    if (playlists->count == 0) {
        printf("\nNo playlists found");
        return;
    }

    for (int i = 0; i < playlists->count; i++) {
        printf("\n-------------------");
        printf("\n - Playlist #%d", actualPlaylist->id);
        printf("\n - Name: %s", actualPlaylist->nome);
        printf(" - Total musics: %d\n", actualPlaylist->count);

        actualPlaylist = actualPlaylist->prox;        
    }
}

void deleteFromPlaylists(musica* musicToDelete, playlistsHeader* playlists) {
    if (playlists->count <= 0) {
        return;
    }

    lplaylists_node* actualPlaylistNode = playlists->first;
    for (int i = 1; i <= playlists->count; i++) {
        
        playlist_node* actualMusicNode = actualPlaylistNode->musicas;
        playlist_node* prevMusicNode = actualPlaylistNode->musicas;
        while (1 && actualMusicNode != NULL) {

            if (actualMusicNode->musica == musicToDelete) {
                
                actualPlaylistNode->count--;

                if (actualMusicNode->prox == actualMusicNode) { // É a única
                    actualPlaylistNode->musicas = NULL;

                    free(actualMusicNode);
                    break;

                } else if (actualMusicNode == actualPlaylistNode->musicas) { // É a primeira

                    playlist_node* lastMusicNode = actualMusicNode;
                    while (lastMusicNode->prox != actualPlaylistNode->musicas) { // Altera prox da última
                        lastMusicNode = lastMusicNode->prox;
                    }
                    lastMusicNode->prox = actualMusicNode->prox;
                    actualPlaylistNode->musicas = actualMusicNode->prox;

                    free(actualMusicNode);

                    actualMusicNode = actualPlaylistNode->musicas;
                    prevMusicNode = actualPlaylistNode->musicas;

                    continue;

                } else {
                    prevMusicNode->prox = actualMusicNode->prox;
                    free(actualMusicNode);
                    actualMusicNode = prevMusicNode;
                }

            } else if (actualMusicNode->prox == actualPlaylistNode->musicas) {
                break;
            }

            prevMusicNode = actualMusicNode;
            actualMusicNode = actualMusicNode->prox;
        }

        actualPlaylistNode = actualPlaylistNode->prox;
    }
}

void deleteMusicById(musicsHeader* musics, playlistsHeader* playlists, int id) {
    if (id <= 0) {
        printf("\nInvalid music.");
        return;
    }

    musica_node* actualMusicNode = musics->first;
    for (int i = 1; i <= musics->count; i++) {
        if (actualMusicNode->musica->id == id) {
            deleteFromPlaylists(actualMusicNode->musica, playlists);

            // Se for a primeira música
            if (i == 1) {
                musics->first = actualMusicNode->prox;

                // Se for a única
                if (i == musics->count) {
                    musics->last = NULL;
                } else {
                    musics->first->ant = NULL;
                }

            } else {
                actualMusicNode->ant->prox = actualMusicNode->prox;

                // Se não for a última
                if (actualMusicNode->prox != NULL) {
                    actualMusicNode->prox->ant = actualMusicNode->ant;
                } else {
                    musics->last = actualMusicNode->ant;
                }
            }

            free(actualMusicNode->musica);
            free(actualMusicNode);

            musics->count--;

            printf("\nMusic ID %d was deleted.", id);
            return;
        }

        if (actualMusicNode->prox == NULL) {
            break;
        }

        actualMusicNode = actualMusicNode->prox;
    }

    printf("\nMusic not found.");
}

void shuffle(lplaylists_node* playlist) {
    // Troca somente a música, não os nós da playlist
    if (playlist->count > 1) {

        playlist_node* actualNode = playlist->musicas;
        for (int i = 1; i <= playlist->count; i++) {
            int switchTo = rand() % (playlist->count + 1); //rand() % (max + min)

            playlist_node* nodeToSwitch = playlist->musicas;
            for (int j = 1; j <= switchTo; j++) {
                if (j == switchTo) {

                    musica* auxMusicSwitch = nodeToSwitch->musica;
                    musica* auxMusicActual = actualNode->musica;

                    nodeToSwitch->musica = auxMusicActual;
                    actualNode->musica = auxMusicSwitch;

                } else {
                    nodeToSwitch = nodeToSwitch->prox;
                }
            }
            
            actualNode = actualNode->prox;
        }
    }
}

void shuffleById(playlistsHeader* playlists, int id) {
    lplaylists_node* playlist = getPlaylist(id, playlists);

    if (playlist == NULL) {
        printf("\n> Playlist not found!");
        return;
    }

    shuffle(playlist);
    printf("\n> Playlist #%d was shuffled", playlist->id);
}