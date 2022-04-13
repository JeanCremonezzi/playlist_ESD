#include "header.h"

int main() {
    musicsHeader* musics = init();
    playlistsHeader* playlists = initPlaylists();
    
    while(1) {
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

        int option = atoi(&optionChar);
        switch (option) {
            case 0:
                return 0;
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
                printf("\n> Music Created!");
                break;

            case 2:
                musics->count > 0 ? printMusics(musics) : printf("\nNo musics found!\n");
                
                break;

            case 3:
                if (musics->count > 0) {
                    printf("\n-> Music id: ");
                    int id;
                    scanf("%d", &id);

                    if (id <= 0) {
                        printf("\nInvalid music ID.");

                    } else {
                        if (!deleteMusicById(musics, playlists, id)) {
                            printf("\nMusic not found.");

                        } else {
                            printf("\nMusic ID %d was deleted.", id);
                        }
                    }

                } else {
                    printf("\nNo musics found!\n");
                }

                break;

            case 4:
                if (musics->count > 0) {
                    newPlaylist(playlists, musics);
                    
                } else {
                    printf("\nNo musics found!\n");
                }
                
                break;

            case 5:
                if (!printPlayLists(playlists)) {
                    printf("\nNo playlists found\n");

                } else {
                    printf("\n\n-> Playlist id: ");
                    int playlistId;
                    scanf("%d", &playlistId);

                    if (!printPlayListById(playlists, playlistId)) {
                        printf("\n\nPlaylist not found.");
                    }
                }

                break;

            case 6:
                if (!printPlayLists(playlists)) {
                    printf("\nNo playlists found\n");

                } else {
                    printf("\n\n-> Playlist id: ");
                    int playlistToShuffle;
                    scanf("%d", &playlistToShuffle);

                    if (!shuffleById(playlists, playlistToShuffle)) {
                        printf("\n> Playlist not found!");

                    } else {
                        printf("\n> Playlist was shuffled");
                    }
                }
                break;
            
            default:
                printf("\n!!!!!!!!!! INVALID OPTION !!!!!!!!!!\n");
                break;
        }
    }
}