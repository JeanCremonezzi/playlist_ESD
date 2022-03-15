musicsHeader* init();
playlistsHeader* initPlaylists();
musica* createMusic(char* title, char* artist, char* album, int duration);
musica_node* insertMusic(musicsHeader* header, char* title, char* artist, char* album, int duration);
lplaylists_node* newPlaylist(playlistsHeader* playlists, musicsHeader* musics);
void printMusic(musica* music);
void printMusics(musicsHeader* header);
musica* getMusic(int id, musicsHeader* header);