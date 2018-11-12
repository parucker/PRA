#ifndef ARVORE_H
#define ARVORE_H
#define ORDEM 10000
#define namefile "registro.bin"



/*typedef struct{
  int chave;
  char nome[20];
  int idade;
  int ApPage[2];
  int rank;
} Corredor;*/

typedef struct Corredor{
  int codigo;
  char name[8];
  int tempo[4]; //duracao da corrida tempo[0] = hora tempo[1] = min tempo[2] = seg tempo[3] = mm
  int data[3]; //data da corrida data[0] = dia data[1] = mes data[2] = ano
  int index;
}Corredor;

typedef struct Pagina_str *Apontador;

typedef struct Pagina_str{
  int n;
  int pageNum;
  int num;
  Corredor r[2*ORDEM];
  Apontador p[2*ORDEM+1];
} Pagina;

typedef struct Node{
    Corredor info;
    struct Node *prox;
}node;

typedef struct No{
	struct No *proximo;
	struct No *anterior;
	Corredor c;
}No;

typedef struct Lista{
	No *primeiro;
	No *ultimo;
}Lista;
Lista* cria();
void adiciona(Lista *f, Corredor c);
void adicionaInicio(Lista *f, Corredor c);
void adicionaPosicao(Lista *f, Corredor c, int n);
int vazia(Lista *f);
Corredor retira(Lista *f);
void percorre(Lista *f, int a, int b);
void percorreInvertido(Lista *l);
void limpa(Lista *f);



//##########################################################
void Antecessor(Apontador Ap, int Ind, Apontador ApPai, int *Diminuiu);
void InsertPosFile(Corredor Reg, Apontador *Ap);
//node *busca(Corredor info, node *LISTA);
void Ins(Corredor Reg, Apontador Ap, int *Cresceu, Corredor *RegRetorno, Apontador *ApRetorno, int escolha);
void Reconstitui(Apontador ApPag, Apontador ApPai, int PosPai, int *Diminuiu);
void saveAux(Apontador p, int Nivel);
void salvar(Apontador pagina, Corredor Reg[]);
void recuperarReg(Apontador *arv, node *LISTA);
void insereInicio(Corredor info, node *LISTA);
void Inicializa(Apontador *arv);
void inicia(node *LISTA);
void em_ordem(Apontador raiz, FILE *fp);
int file_exists(const char *filename);
int isleaf(Apontador a);
void InsereNaPagina(Apontador Ap, Corredor Reg, Apontador ApDir);
void Insere(Corredor Reg, Apontador *Ap, int escolha);
	





#endif
