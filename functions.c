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

musica_node* getMusicNode(int id, musicsHeader* header) {
    musica_node* musicNode = header->first;
    for (int i = 0; i < header->count; i++) {
        if (musicNode->musica->id == id) {
            return musicNode;
        }

        musicNode = musicNode->prox;
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
    musica_node* node = header->first;

    printf("\n\nMusics list:\n");

    for (int i = 0; i < header->count; i++) {
        printMusic(node->musica);
            
        node = node->prox;
    }
};

bool printPlayListById (playlistsHeader* playlists, int id) {
    lplaylists_node* playlist = getPlaylist(id, playlists);

    if (playlist == NULL) {
        return 0;
    }
    
    printPlayList(playlist);
    return 1;
};

void printPlayList(lplaylists_node* playlist) {
    if (playlist->count > 0) {
        printf("\n-------------------");

        printf("\n> TRACKS FROM %s", playlist->nome);

        playlist_node* actualNode = playlist->musicas;

        for (int i = 0; i < playlist->count; i++) {
            printMusic(actualNode->musica);
            actualNode = actualNode->prox;
        }

        return;
    }

    printf("\n\nPlaylist #%d has no musics.", playlist->id);
}

bool printPlayLists(playlistsHeader* playlists) {
    lplaylists_node* actualPlaylist;
    actualPlaylist = playlists->first;

    if (playlists->count == 0) {
        return 0;
    }

    for (int i = 0; i < playlists->count; i++) {
        printf("\n-------------------");
        printf("\n - Playlist #%d", actualPlaylist->id);
        printf("\n - Name: %s", actualPlaylist->nome);
        printf(" - Total musics: %d\n", actualPlaylist->count);

        actualPlaylist = actualPlaylist->prox;        
    }

    return 1;
}

void deleteFromPlaylist(lplaylists_node* playlist, musica* music) {
    playlist_node* actualNode = playlist->musicas;
    playlist_node* aux = playlist->musicas;
    for (int i = 0; i <= playlist->count; i++) {

        if (actualNode->musica == music) {
            if (playlist->count == 1) { // Se for a unica
                playlist->musicas = NULL;

            } else if (actualNode == playlist->musicas) { // Se for a primeira
                playlist->musicas = actualNode->prox;
                aux = playlist->musicas;

            } else { // Se for qualquer outra
                aux->prox = actualNode->prox;
            }

            free(actualNode);
            actualNode = aux;

            playlist->count--;
            i--;

        } else {
            aux = actualNode;
            actualNode = actualNode->prox;
        }
    }
}

void deleteFromPlaylists(musica* musicToDelete, playlistsHeader* playlists) {
    
    lplaylists_node* actualPlaylist = playlists->first;
    for (int i = 0; i < playlists->count; i++) {
        if (actualPlaylist->count > 0) {
            deleteFromPlaylist(actualPlaylist, musicToDelete);
        }

        actualPlaylist = actualPlaylist->prox;
    }
}

bool deleteMusicById(musicsHeader* musics, playlistsHeader* playlists, int id) {

    musica_node* musicToDelete = getMusicNode(id, musics);

    if (musicToDelete != NULL) {
        deleteFromPlaylists(musicToDelete->musica, playlists);

        if (musics->count == 1 && musics->first == musicToDelete) { // Se for a unica
            musics->first = NULL;
            musics->last = NULL;

        } else if (musics->first == musicToDelete) { // Se for primeira
            musics->first = musicToDelete->prox;
            musics->first->ant = NULL;

        } else if (musics->last == musicToDelete) { // Se for ultima
            musics->last = musicToDelete->ant;
            musics->last->prox = NULL;

        } else { // Se for qualquer outra
            musicToDelete->ant->prox = musicToDelete->prox;
            musicToDelete->prox->ant = musicToDelete->ant;
        }

        musics->count--;
        free(musicToDelete->musica);
        free(musicToDelete);

        return 1;
    }

    return 0;
}

void shuffle(lplaylists_node* playlist) {
    // Troca somente a musica, nao os nos da playlist
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

bool shuffleById(playlistsHeader* playlists, int id) {
    lplaylists_node* playlist = getPlaylist(id, playlists);

    if (playlist == NULL) {
        return 0;
    }

    shuffle(playlist);
    return 1;
}