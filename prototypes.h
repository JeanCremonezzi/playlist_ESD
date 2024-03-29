musicsHeader* init();
playlistsHeader* initPlaylists();
musica* createMusic(char* title, char* artist, char* album, int duration);
musica* getMusic(int id, musicsHeader* header);
musica_node* getMusicNode(int id, musicsHeader* header);
musica_node* insertMusic(musicsHeader* header, char* title, char* artist, char* album, int duration);
lplaylists_node* newPlaylist(playlistsHeader* playlists, musicsHeader* musics);
lplaylists_node* getPlaylist(int id, playlistsHeader* playlists);
void printMusic(musica* music);
void printMusics(musicsHeader* header);
bool printPlayListById (playlistsHeader* playlists, int id);
void printPlayList(lplaylists_node* playlist);
bool printPlayLists(playlistsHeader* playlists);
void deleteFromPlaylist(lplaylists_node* playlist, musica* music);
void deleteFromPlaylists(musica* musicToDelete, playlistsHeader* playlists);
bool deleteMusicById(musicsHeader* musics, playlistsHeader* playlists, int id);
void shuffle(lplaylists_node* playlist);
bool shuffleById(playlistsHeader* playlists, int id);