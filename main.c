#include "header.h"

int main() {
    musicsHeader* musics = init();
    playlistsHeader* playlists = initPlaylists();

    int flag = 1;
    while(flag) {
        printf("\n-------- MUSICS MENU --------\n");
        printf("\n> Menu:");
        printf("\n   1. Add new music");
        printf("\n   2. Show musics");
        printf("\n   3. Delete music");
        printf("\n   4. Create playlist");
        printf("\n   5. Print playlist");
        printf("\n   6. Shuffle playlist");
        printf("\n   0. Sair");

        printf("\n\n-> CHOOSE AN OPTION: ");
        char optionChar;
        fflush(stdin);
        scanf("%c", &optionChar);

        if (isdigit(optionChar) == 0) {
            printf("\n!!!!!!!!!! OPTION MUST BE A DIGIT !!!!!!!!!!\n");
            continue;
        }

        // Char to Int
        int option = optionChar - '0';
        switch (option) {
            case 0:
                flag = 0;
                break;

            case 1:
                printf("\n-> Music name: ");
                char music[STRING_SIZE];
                fflush(stdin);
                fgets(music, STRING_SIZE, stdin);

                printf("-> Album name: ");
                char album[STRING_SIZE];
                fflush(stdin);
                fgets(album, STRING_SIZE, stdin);

                printf("-> Artist name: ");
                char artist[STRING_SIZE];
                fflush(stdin);
                fgets(artist, STRING_SIZE, stdin);

                printf("-> Duration in seconds: ");
                int duration;
                scanf("%d", &duration);

                insertMusic(musics, music, artist, album, duration);
                break;

            case 2:
                printMusics(musics);
                break;

            case 3:
                printf("\n-> Music id: ");
                int id;
                scanf("%d", &id);

                deleteMusicById(musics, playlists, id);
                break;

            case 4:
                newPlaylist(playlists, musics);
                break;

            case 5:
                printPlayLists(playlists);

                printf("\n\n-> Playlist id: ");
                int playlistId;
                scanf("%d", &playlistId);

                printPlayListById(playlists, playlistId);
                break;

            case 6:
                printPlayLists(playlists);

                printf("\n\n-> Playlist id: ");
                int playlistToShuffle;
                scanf("%d", &playlistToShuffle);

                shuffleById(playlists, playlistToShuffle);
                break;
            
            default:
                printf("\n!!!!!!!!!! INVALID OPTION !!!!!!!!!!\n");
                break;
        }
    }
}