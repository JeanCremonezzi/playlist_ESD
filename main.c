#include "header.h"

int main() {
    musicsHeader* musics = init();

    printMusics(musics);

    musica_node* newMusic = insertMusic(musics, "MUSIC 1", "ARTIST 1", "ALBUM 1", 180);
    musica_node* newMusic2 = insertMusic(musics, "MUSIC 2", "ARTIST 2", "ALBUM 2", 360);
    musica_node* newMusic3 = insertMusic(musics, "MUSIC 3", "ARTIST 3", "ALBUM 3", 540);

    printMusics(musics);
}