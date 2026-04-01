#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
typedef struct{
	char nome[100];
	int idade;
	float altura;
}Pessoa;

void cadastro(Pessoa p[], int cont){
	system("clear");
	printf("Cadastro\n\n");
	printf("Nome: ");
	scanf(" %[^\n]s", p[cont].nome);
	
	printf("Idade: ");
	scanf(" %d", &p[cont].idade);
	
	printf("Altura: ");
	scanf(" %f", &p[cont].altura);
	
	system("clear");
}

void ordena(Pessoa p[], int cont){
	system("clear");
	for (int i = 0; i < cont - 1; i++)
		for (int j = i + 1; j < cont; j++)
		if (strcmp(p[i].nome, p[j].nome) > 0)
		{
			Pessoa troca = p[i];
			p[i] = p[j];
			p[j] = troca;
		}
	printf("Ordenação realizada com sucesso!\n\n");
}

void lista(Pessoa p[], int cont){
	system("clear");
	if (!cont)
	{
		printf("Nenhum cadastro foi encontrado!\n");
	}
	else
	printf("Lista de cadastros\n\n");
	
	for (int i = 0; i < cont; i++)
	{
		printf("Cadastro %d\n", i + 1);
		printf("nome: %s\n", p[i].nome);
		printf("idade: %d\n", p[i].idade);
		printf("altura: %.2f\n\n", p[i].altura);
	}
}

int main(){
	
	Pessoa p[MAX];
	int cont = 0, op;
	
	do
	{	
		printf("1. Cadastrar\n");
		printf("2. Ordenar\n");
		printf("3. Listar\n");
		printf("4. Finalizar\n");
		scanf(" %d", &op);
		
		switch (op)
		{
			case 1:	cadastro(p, cont++);
				break;	
			case 2:	ordena(p, cont);
				break;
			case 3: lista(p, cont);
				break;
			case 4: system("clear"); 
				printf("Programa finalizado!");	
				break;
			default: printf("Opção selecionada não existe!!\n");
				printf("Tente novamente...\n");
				continue;
		}
		if (cont==MAX)
		{
			printf("Limite de cadastros excedido.");
			break;
		}
		if(op==4)
			break;
			
	} while (1);
	
	return 0;
}

