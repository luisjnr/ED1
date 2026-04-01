#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STR " %[^\n]s"
#define INT " %d"
#define FLOAT " %f"
#define CHAR " %c"
#define MAX 100

typedef struct{
	char titulo[100];
	char artista[100];
	int tempo;
	int id;
}Musica;

typedef struct{
	Musica cad[MAX];
	int cont_musica;
	int cont_id;
}Lista;

Lista inicializador(){
	Lista c;
	c.cont_musica = 0;
	c.cont_id = 1;
	return c;	
}

int interface(){
	int opc;
	int verificador;
	printf("1. Adicionar Música\n" "2. Excluir Música\n" 
	"3. Tocar Playlist\n" "4. Tocar por Artista\n" 
	"5. Tocar Aleatório\n" "6. Finalizar Programa\n");
	verificador = scanf(" %d", &opc);
	system("clear");
	if (!verificador)
		return -1;
	return opc;	
}

void input(char *tipo, char frase[], void *var){
	printf("%s", frase);
	scanf(tipo, var);
}

Musica cadastroMusica(Lista *ptrlista){
	Musica p;
	if (ptrlista->cont_musica < MAX){
		printf("Cadastro\n\n");
		input(STR, "Título: ", p.titulo);
		input(STR, "Artista: ", p.artista);
		input(INT, "Tempo: ", &p.tempo);
		p.id = ptrlista->cont_id;
	}
	else printf("Número de cadastros excedido!\n");
	return p;
}

void listaMusica(Lista *ptrlista, Musica cad){
	if (ptrlista->cont_musica < MAX){	
		ptrlista->cad[ptrlista->cont_musica] = cad;
		ptrlista->cont_id++;
		ptrlista->cont_musica++;
	}
}

void listarPlaylist(Lista *ptrlista, char frase[]){
	if (ptrlista->cont_musica > 0){
		int min = 0, seg = 0, acumulador = 0;
		printf("%s\n\n", frase);
		printf("ID\tTÍTULO\t\t\t\t\tARTISTA\t\t\t\t\tTEMPO\n");
		for (int i = 0; i < ptrlista->cont_musica; i++){
			if (ptrlista->cad[i].id > 0){
				min = ptrlista->cad[i].tempo / 60;
				seg = ptrlista->cad[i].tempo % 60;
				acumulador += ptrlista->cad[i].tempo;
				printf("%02d\t", ptrlista->cad[i].id);
				printf("%s", ptrlista->cad[i].titulo);
				for (int j = 0; j < (40 - 
				strlen(ptrlista->cad[i].titulo)); j++)
					printf(" ");
				printf("%s", ptrlista->cad[i].artista);
				for (int j = 0; j < (40 - 
				strlen(ptrlista->cad[i].artista)); j++)
					printf(" ");
				printf("%d:%02d\n", min, seg);
			}
		}
		min = acumulador / 60;
		seg = acumulador % 60;
		printf("\nTEMPO TOTAL DA PLAYLIST:\t\t\t\t\t\t\t\t%d:%02d\n\n", 
		min, seg);
	}
	else printf("Nenhuma música foi cadastrada!\n\n");
}

int buscarPosicao(Lista *ptrlista, char frase[]){
	int id;
	int posicao;
		printf("%s", frase);
		scanf(" %d", &id);
	for (int i = 0; i < ptrlista->cont_musica; i++)
		if (id == ptrlista->cad[i].id)
			return posicao = i;
	return posicao = -1;
}

void excluirMusica(Lista *ptrlista){
	if (ptrlista->cont_musica > 0){
		int posicao = buscarPosicao(ptrlista, 
		"Digite o id da música que deseja excluir: ");
		if (posicao != -1){
			for (int i = posicao; i < ptrlista->cont_musica; i++)
				ptrlista->cad[i] = ptrlista->cad[i + 1];
			ptrlista->cont_musica--;
		} 
		else printf("id não exite!\n\n");
	}
}

void prosseguirInterface(char frase[]){
	while(getchar() != '\n');
	printf("%s ", frase);
	getchar();
	system("clear");
}

void ordenarArtista(Lista *ptrlista){
	Lista temporaria = *ptrlista;
	for (int i = 0; i < ptrlista->cont_musica - 1; i++)
		for (int j = i + 1; j < ptrlista->cont_musica; j++)
			if (strcmp(temporaria.cad[i].artista, 
			temporaria.cad[j].artista) > 0){
				Musica troca = temporaria.cad[i];
				temporaria.cad[i] = temporaria.cad[j];
				temporaria.cad[j] = troca;
			}
	listarPlaylist(&temporaria, "TOCAR POR ARTISTA");	
}

void ordenarAleatorio(Lista *ptrlista){
	Lista temporaria = *ptrlista;
	for (int i = 0; i < ptrlista->cont_musica; i++){
		int j = rand() % ptrlista->cont_musica;
		Musica troca = temporaria.cad[i];
		temporaria.cad[i] = temporaria.cad[j];
		temporaria.cad[j] = troca;
	}
	listarPlaylist(&temporaria, "TOCAR ALEATÓRIO");	
}

int main(){
	srand(time(NULL));
	Lista dados = inicializador();
	Musica cad;
	do{
		switch (interface()){
			case 1:	cad = cadastroMusica(&dados);
				listaMusica(&dados, cad);
				prosseguirInterface("Pressione ENTER para finalizar!");
				break;
			case 2:	listarPlaylist(&dados, "EXCLUSÃO DE MÚSICA");
				excluirMusica(&dados);
				prosseguirInterface("Pressione ENTER para finalizar!");
				break;
			case 3:	listarPlaylist(&dados, "TOCAR PLAYLIST");
				prosseguirInterface("Pressione ENTER para finalizar!");
				break;
			case 4: ordenarArtista(&dados);
				prosseguirInterface("Pressione ENTER para finalizar!");
				break;
			case 5: ordenarAleatorio(&dados);
				prosseguirInterface("Pressione ENTER para finalizar!");
				break;
			case 6: printf("Programa finalizado!");
				return 0;
				break;
			default: prosseguirInterface("Opção não existe!\n"
			"Tente novamente...\n" "Pressione ENTER para prosseguir\n");
		}
	} while (1);
}
