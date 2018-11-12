#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lista.h"
#define GB 1073741824

/*typedef struct Corredor{
	int codigo;
	char name[8];
	int tempo[4];	//duracao da corrida tempo[0] = hora tempo[1] = min tempo[2] = seg tempo[3] = mm
	int data[3]; //data da corrida data[0] = dia data[1] = mes data[2] = ano 
}Corredor;

typedef struct No{
	struct No *proximo;
	struct No *anterior;
	Corredor c;
}No;

typedef struct Lista{
	No *primeiro;
	No *ultimo;
}Lista;*/
void nome(char* x);
int criaCodigo(void);
void criaTempo (int* tempo);
void criaData(int* data);
void escreveDado (FILE *fp, Corredor* maratonista);
void cria1GB (FILE* fp);
void leArquivo (FILE* fr, Lista* l);
/*Lista* cria();
void adiciona(Lista *f, Corredor c);
void adicionaInicio(Lista *f, Corredor c);
void adicionaPosicao(Lista *f, Corredor c, int n);
int vazia(Lista *f);
Corredor retira(Lista *f);
void percorre(Lista *f, int a, int b);
void percorreInvertido(Lista *l);
void limpa(Lista *f);*/

int main(int argc, char **argv)
{	
	int a=0,b=0; //variaveis para controlar o intervalo que será percorrido
	srand((unsigned)time(NULL));
	FILE *fp = NULL; 	//ponteiro para escrever
	FILE *fr = NULL;	//ponteiro para ler o arquivo
	Lista *l;
	fp = fopen("registro.txt", "wb");
	if(fp==NULL){
		printf("Erro na abertura do arquivo\n");
		system("pause");
		exit(1);
	}
	cria1GB(fp);
	fr = fopen("registro.txt","rb");
	if(fr==NULL){
		printf("Erro na abertura do arquivo\n");
		system("pause");
		exit(1);
	}
	l = cria();//cria o arquivo
	leArquivo(fr,l);
	fclose(fp);
	fclose(fr);
	printf("Escolha o intervalo de a até b que será percorrido nos registros\n");
	scanf("%d %d",&a,&b);
	percorre(l,a,b);
	limpa(l);
	printf("PERCORRENDO OS ARQUIVOS DEPOIS DA LIMPA\n");
	//percorre(l);
	//percorreInvertido(l);
	return 0;
	
}

void nome(char* x)
{
	
	int y=0,letra= 0; 
	char name[8];
	for(y=0;y<8;y++)
	{
		letra = 97+(rand()%26);
		name[y] = letra;
	}
	strcpy(x,name);
}

int criaCodigo(void)
{
	int x=0;
	x = rand()%150000;
	return x;
}

void criaTempo (int* tempo){
	int hora;
	int min;
	int mm;
	int seg;
		
	hora = rand()%59;
	min = rand()%59;
	seg = rand()%59;
	mm = rand()%99;
	tempo[0] = hora;
	tempo[1] = min;
	tempo[2] = seg;
	tempo[3] = mm;
	}

void criaData(int* data)
{
	struct tm *local;
	time_t t;
	t= time(NULL);
	local=localtime(&t);
	data[0] = local->tm_mday;
	data[1] = local->tm_mon;
	data[2] = local->tm_year;
}

void escreveDado (FILE *fp, Corredor* maratonista)
{
	fwrite(maratonista,sizeof(Corredor),1,fp);
}
void cria1GB (FILE* fp){
	int i=0;
	for(i=0; i< 10000/sizeof(Corredor); i++){
		Corredor* maratonista = malloc(sizeof(Corredor));
		maratonista->codigo = criaCodigo();
		criaData(maratonista->data);
		criaTempo(maratonista->tempo);
		nome(maratonista->name);
		escreveDado (fp, maratonista);
    }
}

//Objetivo: Transformar esse learquivo em um preenche a lista

void leArquivo (FILE* fr, Lista *l){
	while (!feof(fr)){
		//int i;
		Corredor corredor; //vai guardar as informações
		fread(&corredor, sizeof(Corredor),1,fr);
		adiciona(l,corredor);
   }    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////PARTE DAS FILAS//////////////////////////////////////////////////////////////////////////////////////////


/*Lista* cria()
{
	Lista *f;
	f = malloc(sizeof(Lista));
	f->primeiro = f->ultimo = NULL; // esta vazia
	return f;
}

void adiciona(Lista *f, Corredor c)
{
	No *no = malloc(sizeof(No));
	no->c = c;
	no->proximo=NULL;
	no->anterior=NULL;
	if(f->ultimo!=NULL)
	{
		no->anterior = f->ultimo;
		f->ultimo->proximo = no;
	}
	f->ultimo = no;
	if(f->primeiro == NULL) f->primeiro = no;
}

void adicionaInicio(Lista *f, Corredor c)
{
	No *no = malloc(sizeof(No));
	no->c = c;
	no->proximo = f->primeiro;
	no->anterior = NULL;
	f->primeiro->anterior = no;
	f->primeiro=no;
	if (f->ultimo==NULL) f->ultimo = no;
}

void adicionaPosicao(Lista *f, Corredor c, int n) //trabalhar com ponteiro, depois do no com valor 10
{
	No *no = malloc(sizeof(No));
	No *aux = NULL;
	int cont=0;
	no->c = c;
	for (aux = f->primeiro;aux!=NULL;aux = aux->proximo)
	{
		cont++;
		if(cont==n-1)
		{
			no->proximo = aux->proximo;
			aux->proximo->anterior = no;
			no->anterior = aux;
			aux->proximo = no;
			if(no->proximo==NULL) f->ultimo=no;
		}
		if(n==1) adicionaInicio(f,c);
	}
}

int vazia(Lista *f)
{
	return f->primeiro == NULL && f->ultimo == NULL;
}

Corredor retira(Lista *f)
{
	Corredor c;
	No* no;
	if(vazia(f))
	{
		printf("Fila vazia!\n");
		exit(-1);
	}
	c = f->primeiro->c;
	no = f->primeiro;
	f->primeiro = f->primeiro->proximo;
	f->primeiro->anterior = NULL;
	free(no);
	if(f->primeiro == NULL) f->ultimo = NULL;
	return c;
}

void percorre(Lista *f, int a, int b)
{
	int contador=0;
	No* atual;
	for (atual = f->primeiro; atual!= NULL; atual = atual->proximo)
	{
		contador++;
		if(contador>=a && contador<=b)
		{
			printf("Nome: %s\n",atual->c.name);
			printf("Codigo: %d\n",atual->c.codigo);
			printf("Tempo: %d:%d:%d:%d\n",atual->c.tempo[0],atual->c.tempo[1],atual->c.tempo[2],atual->c.tempo[3]);
			printf("Data: %d/%d/%d\n",atual->c.data[0],atual->c.data[1],atual->c.data[2]);
			printf("\n");
		}
	}
}

void percorreInvertido(Lista *l)
{
	No *atual;
	for (atual = l->ultimo; atual!=NULL; atual = atual->anterior)
	{
		printf("Nome: %s\n",atual->c.name);
		printf("Codigo: %d\n",atual->c.codigo);
		printf("Tempo: %d:%d:%d:%d\n",atual->c.tempo[0],atual->c.tempo[1],atual->c.tempo[2],atual->c.tempo[3]);
		printf("Data: %d/%d/%d\n",atual->c.data[0],atual->c.data[1],atual->c.data[2]);
		printf("\n");
	}
}

void limpa(Lista *f)
{
	No *atual;
	atual=f->primeiro;
	f->primeiro = f->primeiro->proximo;
	free(atual);
	if(f->primeiro!=NULL) limpa(f);
	f->ultimo = NULL;
}*/
