#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char rua[100];
	int numero;	
	char bairro[100];
	char cidade[100];
}Ende; 

typedef struct{
	char nome[100];
	char cpf[12];
	int idade;
	float altura, peso;
	Ende resid; 
}Pessoa;

#define N 10

int main(){
	Pessoa cad[N];
	int cont = 0;
	
	//COLETA DE DADOS
	for (int i = 0; i < N; i++)
	{
		printf("Cadastro da pessoa %d:\n", i + 1);
		printf("Digite 'exit' para finalizar o programa.\n");
		printf("Nome: ");
		scanf(" %[^\n]s", cad[i].nome);
		
		if (strcmp(cad[i].nome, "exit") == 0 || 
		strcmp(cad[i].nome, "EXIT") == 0){
			system("clear");
			printf("Programa finalizado!\n\n");
			break;
		}
		printf("CPF: ");
		scanf(" %[^\n]s", cad[i].cpf);
		
		printf("Idade: ");
		scanf(" %d", &cad[i].idade);
		
		printf("Altura: ");
		scanf(" %f", &cad[i].altura);
		
		printf("Peso: ");
		scanf(" %f", &cad[i].peso);
		
		printf("Rua: ");
		scanf(" %[^\n]s", cad[i].resid.rua);
		
		printf("Número: ");
		scanf(" %d", &cad[i].resid.numero);
		
		printf("Bairro: ");
		scanf(" %[^\n]s", cad[i].resid.bairro);
		
		printf("Cidade: ");
		scanf(" %[^\n]s", cad[i].resid.cidade);
	
		system("clear");
		cont++;
	}
	
	//ORDENAÇÃO DE DADOS
	for (int i = 0; i < cont - 1; i++)
		for (int j = i + 1; j < cont; j++){
			Pessoa troca;
			if (strcmp(cad[i].nome,cad[j].nome) > 0)
			{
				troca = cad[i];
				cad[i] = cad[j];
				cad[j] = troca;
			}
		}
		
	if (!cont)
		printf("Nenhuma pessoa foi cadastrada!");
		
	//IMPRESSÃO DE DADOS
	
	
	for (int i = 0; i < cont; i++)
	{
		printf("Cadastro %d:\n", i + 1);
		
		printf("Nome: %s\n", cad[i].nome);
	
		printf("Cpf: %s\n", cad[i].cpf);
	
		printf("Idade: %d\n", cad[i].idade);
	
		printf("Altura: %.2f\n", cad[i].altura);
	
		printf("Peso: %.2f\n", cad[i].peso);
	
		printf("Rua: %s\n", cad[i].resid.rua);
	
		printf("Número: %d\n", cad[i].resid.numero);
	
		printf("Bairro: %s\n", cad[i].resid.bairro);
	
		printf("Cidade: %s\n\n", cad[i].resid.cidade);
	}		
	return 0;
}
