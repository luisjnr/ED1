#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char origem[30];
	char destino[30];
	int distancia;
	int tempo;
}Rota;

typedef struct{
	Rota lista[100];
	int cont;
	int cont_rota;
	int amc_tempo;
	int acm_distancia;
}Lista;

int opcao(){
	int opc;
	do
	{		
		printf("1. Cadastrar rota\n");
		printf("2. Consultar rota\n");
		printf("3. Finalizar programa\n");
		scanf(" %d", &opc);
		if (opc < 1 || opc > 3)
		{
			system("clear");
			printf("Opção inválida!\nTente novamente...\n");
			continue;
		}
		else return opc;	
	} while (1);
}

Lista contagemRota(){
	Lista contagem;
	contagem.cont = 0;
	contagem.cont_rota = 0;
	contagem.acm_distancia = 0;
	contagem.amc_tempo = 0;
	return contagem;
}

Rota novaRota(Lista *ptr){
	Rota nova;
	system("clear");
	printf("Cadastro da Rota\n");
	do
	{
		int flag = 1;
		printf("Origem: ");
		scanf(" %[^\n]s", nova.origem);
		for (int i = 0; i < ptr->cont; i++)
			if (strcmp(ptr->lista[i].origem, nova.origem) == 0)
			{
				flag = 0;
				break;
			}
		if (!flag)
		{
			system("clear");
			printf("Origem digita já existe!\n");
			printf("Tente novamente...\n");
			continue;
		}
		else break;
	} while (1);
	printf("Destino: ");
	scanf(" %[^\n]s", nova.destino);
	printf("Distância: ");
	scanf(" %d", &nova.distancia);
	printf("Tempo: ");
	scanf(" %d", &nova.tempo);
	system("clear");
	return nova;
}

void cadastroRota(Rota rota, Lista *ptr){
	ptr->lista[ptr->cont] = rota;
	ptr->cont++;
}

Rota selecionarRota(Lista *ptr){
	Rota rota;
	system("clear");
	printf("Buscar rota\n");
	do
	{	
		int flag = 1;	
		printf("Origem: ");
		scanf(" %[^\n]s", rota.origem);
		for (int i = 0; i < ptr->cont; i++)
			if (strcmp(rota.origem, ptr->lista[i].origem) == 0)
			{
				flag = 0;
				break;
			}
		if (!flag) 
			break;
		else
		{
			system("clear");
			printf("Origem não encontrada!\n");
			printf("Tente novamente...\n");
			continue;
		}
	} while (1);
	
	do
	{	
		int flag = 1;	
	printf("Destino: ");
	scanf(" %[^\n]s", rota.destino);
			for (int i = 0; i < ptr->cont; i++)
			if (strcmp(rota.destino, ptr->lista[i].destino) == 0)
			{
				flag = 0;
				break;
			}
		if (!flag) break;
		else
		{
			system("clear");
			printf("Destino não encontrado!\n");
			printf("Tente novamente...\n");
			continue;
		}
	} while (1);
	return rota;
}

void buscarRota(Rota rota, Lista *ptr){
	do
	{
		int indice;
		int verificador = 0;
		for (int i = 0; i < ptr->cont; i++)
			if (strcmp(rota.origem, ptr->lista[i].origem) == 0)
			{
				indice = i;
				verificador = 1;
				break;
			}
		if (!verificador)
		{
			printf("Não existem rotas dispóniveis!\n");
			break;
		}
		else
		{
			ptr->cont_rota++;
			ptr->acm_distancia += ptr->lista[indice].distancia;
			ptr->amc_tempo += ptr->lista[indice].tempo;
		}
		if (strcmp(rota.destino, ptr->lista[indice].destino) == 0)
		{
			system("clear");
			printf("Rota localizada\n");
			printf("Distância: %d\n", ptr->acm_distancia);
			printf("Tempo: %d\n", ptr->amc_tempo);
			printf("Rotas necessárias: %d\n\n", ptr->cont_rota);
			ptr->cont_rota = 0;
			ptr->acm_distancia = 0;
			ptr->amc_tempo = 0;
			break;
		}
		else 
			strcpy(rota.origem, ptr->lista[indice].destino);
	} while (1);
}

int main(){
	Lista ptr = contagemRota();
	do
	{
		switch (opcao())
		{
			case 1: Rota rota = novaRota(&ptr);
				cadastroRota(rota, &ptr);
				break;
			case 2: rota = selecionarRota(&ptr);
				buscarRota(rota ,&ptr);
				break;
			case 3: printf("Programa finalizado!");
				return 0;
		}
	} while (1);
}
