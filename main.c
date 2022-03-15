#include "header.h"

int main() {
    musicsHeader* musics = init();
    playlistsHeader* playlists = initPlaylists();

    printMusics(musics);

    insertMusic(musics, "The Darkness at The Heart of My Love", "Ghost", "Impera", 300);
    insertMusic(musics, "Simple Man", "Lynyrd Skynyrd", "Pronounced 'Leh-'nerd 'Skin-'nerd", 356);
    insertMusic(musics, "Kill Each Other / Live Forever", "Scars on Broadway", "Scars on Broadway", 180);
    insertMusic(musics, "Come Join the Murder", "The White Buffalo", "Come Join the Murder", 448);
    insertMusic(musics, "Black", "Pearl Jam", "Ten", 345);
    insertMusic(musics, "City of Angels", "The Distillers", "Sing Sing Death House", 210);

    printMusics(musics);

    newPlaylist(playlists, musics);
    newPlaylist(playlists, musics);
}