musicsHeader* init();
musica* createMusic(char* title, char* artist, char* album, int duration);
musica_node* insertMusic(musicsHeader* header, char* title, char* artist, char* album, int duration);
void printMusics(musicsHeader* header);
musica* getMusic(int id, musicsHeader* header);