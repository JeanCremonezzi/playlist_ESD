typedef struct musica {
    int id;
    char titulo[200];
    char artista[200];
    char album[200];
    int duracao;
} musica;

typedef struct musica_node {
    musica *musica;
    struct musica_node *ant;
    struct musica_node *prox;
} musica_node;