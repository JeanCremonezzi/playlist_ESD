typedef struct musica {
    int id;
    char titulo[STRING_SIZE];
    char artista[STRING_SIZE];
    char album[STRING_SIZE];
    int duracao;
} musica;

typedef struct musica_node {
    musica *musica;
    struct musica_node *ant;
    struct musica_node *prox;
} musica_node;

typedef struct musicsHeader {
    struct musica_node *first;
    struct musica_node *last;
    int count;
} musicsHeader;

typedef struct playlist_node {
    musica *musica;
    struct playlist_node *prox;
} playlist_node;

typedef struct lplaylists_node {
    int id;
    char nome[STRING_SIZE];
    playlist_node *musicas;
    struct lplaylists_node *prox;
} lplaylists_node;

typedef struct playlistsHeader {
    struct lplaylists_node *first;
    struct lplaylists_node *last;
    int count;
} playlistsHeader;