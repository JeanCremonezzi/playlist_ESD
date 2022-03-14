#include "header.h"

int main() {
    musicsHeader* musics = init();

    printMusics(musics);

    insertMusic(musics, "The Darkness at The Heart of My Love", "Ghost", "Impera", 300);
    insertMusic(musics, "Simple Man", "Lynyrd Skynyrd", "Pronounced 'Leh-'nerd 'Skin-'nerd", 356);
    insertMusic(musics, "Come Join the Murder", "The White Buffalo", "Come Join the Murder", 448);

    printMusics(musics);

    getMusic(2, musics);
}