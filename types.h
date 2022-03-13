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