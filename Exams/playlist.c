#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct{
	int id;
	char titulo[MAX];
	char artista[MAX];
	int tempo;
}Dados;

typedef struct{
	Dados cad[MAX];
	int contmusica;
	int contid;
}Lista;
	
Lista contadorGeral(){
	Lista cont;
	cont.contmusica = 0;
	cont.contid = 0;
	return cont;
}

int interface(){
	int opc;
	do{
		printf("1. Adicionar Música\n");
		printf("2. Excluir Música\n");
		printf("3. Tocar Playlist\n");
		printf("4. Tocar por Artista\n");
		printf("5. Tocar Aleatório\n");
		printf("6. Finalizar Programa\n");
		scanf(" %d", &opc);
		if (opc < 1 || opc > 6)
		{
			system("clear");
			printf("Opção inválida!\nTente novamente...\n\n");
			continue;
		}
		else return opc;
	}while(1);
}

Dados adicionarMusica(){
	Dados novo;
	system("clear");
	printf("Adicionar nova música\n\n");
	printf("Título da Música: ");
	scanf(" %[^\n]s", novo.titulo);
	printf("Nome do Artista: ");
	scanf(" %[^\n]s", novo.artista);
	printf("Tempo em segundos: ");
	scanf(" %d", &novo.tempo);
	system("clear");
	return novo;
}

Lista listarDados(Lista *ptrlista, Dados novo){
	ptrlista->cad[ptrlista->contmusica] = novo;
	ptrlista->cad[ptrlista->contmusica].id = ptrlista->contid;
	ptrlista->cad[ptrlista->contmusica].id++;
	ptrlista->contmusica++;
	ptrlista->contid++;
	return *ptrlista;
}

void listarMusicas(Lista *ptrlista){
	system("clear");
	int acumulador = 0;
	int min, seg;
	printf("PLAYLIST\n\n");
	printf("ID\tTÍTULO\t\t\t\tARTISTA\t\t\t\tTEMPO\n");
	for (int i = 0; i < ptrlista->contmusica; i++)
	{
		if (ptrlista->cad[i].id > 0)
		{
			printf("%d\t", ptrlista->cad[i].id);
				printf("%s", ptrlista->cad[i].titulo);
			for (int j = 0; j < (32 - strlen(ptrlista->cad[i].titulo)); j++)
				printf(" ");
			printf("%s", ptrlista->cad[i].artista);
			for (int k = 0; k < (32 - strlen(ptrlista->cad[i].artista)); k++)
				printf(" ");
			acumulador += ptrlista->cad[i].tempo;
			min = ptrlista->cad[i].tempo / 60;
			seg = ptrlista->cad[i].tempo % 60;
			printf("%d:%02d\n", min, seg);
		}
		
	}
	min = acumulador / 60;
	seg = acumulador % 60; 
	printf("\nTEMPO TOTAL DA PLAYLIST:\t\t\t\t\t\t%d:%02d\n\n", min, seg);
}

int buscarMusica(Lista *ptrlista, int *posicao){
	int id;
	printf("DIGITE O ID DA MÚSICA QUE DESEJA EXCLUIR: ");
	scanf(" %d", &id);
	for (int i = 0; i < ptrlista->contmusica; i++)
		if (id == ptrlista->cad[i].id)
			*posicao = i;
	system("clear");
	return *posicao;	
}

void excluirMusica(Lista *ptrlista){
	int posicao = 0;
	buscarMusica(ptrlista, &posicao);
	for (int i = posicao; i < ptrlista->contmusica; i++)
		ptrlista->cad[i] = ptrlista->cad[i+1];
	ptrlista->contmusica--;
}

void ordenarInsercao(Lista *ptrlista){
	for (int i = 0; i < ptrlista->contmusica - 1; i++)
		for (int j = i + 1; j < ptrlista->contmusica; j++)
			if (ptrlista->cad[i].id > ptrlista->cad[j].id)
			{
				Dados troca = ptrlista->cad[i];
				ptrlista->cad[i] = ptrlista->cad[j];
				ptrlista->cad[j] = troca;
			}
}

void ordenarArtista(Lista *ptrlista){
	for (int i = 0; i < ptrlista->contmusica - 1; i++)
		for (int j = i + 1; j < ptrlista->contmusica; j++)
			if (strcmp(ptrlista->cad[i].artista, ptrlista->cad[j].artista) > 0)
			{
				Dados troca = ptrlista->cad[i];
				ptrlista->cad[i] = ptrlista->cad[j];
				ptrlista->cad[j] = troca;
			}
}

void ordenarAleatorio(Lista *ptrlista){
	int aleat = rand() % 100;
	for (int i = 0; i < aleat; i++)
		for (int j = 0; j < ptrlista->contmusica - 1; j++){
			Dados troca = ptrlista->cad[j];
			ptrlista->cad[j] = ptrlista->cad[j + 1];
			ptrlista->cad[j + 1] = troca;
	}
}

void prosseguirPlaylist(){
	char enter;
	printf("PRESIONE 'ENTER' PARA PROSSEGUIR! ");
	getchar();
	while((enter = getchar()) != '\n' && enter != EOF);
	system("clear");	
}

int main(){
	srand(time(NULL));
	Lista listadados = contadorGeral();
	Dados novo;
	do
	{
		switch (interface())
		{
			case 1:	novo = adicionarMusica();
				listarDados(&listadados, novo);
				break;
			case 2: ordenarInsercao(&listadados);
				listarMusicas(&listadados);
				excluirMusica(&listadados);
				prosseguirPlaylist();
				break;
			case 3:	ordenarInsercao(&listadados);
				listarMusicas(&listadados);
				prosseguirPlaylist();
				break;
			case 4: ordenarArtista(&listadados);
				listarMusicas(&listadados);
				prosseguirPlaylist();
			break;
			case 5: ordenarAleatorio(&listadados);
				listarMusicas(&listadados);
				prosseguirPlaylist();
				break;
			case 6: system("clear");
			printf("Programa finalizado!");
			return 0;		
		}
	} while (1);
}
