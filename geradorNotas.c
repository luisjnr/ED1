#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int alunos, provas;
	
	//QUANTIDADE DE ALUNOS E PROVAS
	printf("Digite a quantidade de alunos: ");
	scanf(" %d", &alunos);
	printf("Digite a quantidade de provas: ");
	scanf(" %d", &provas);
	system("clear");
	
	//NOTAS DOS ALUNOS	
	int quadro[alunos][provas];
	
	for (int i = 0; i < alunos; i++)
		for (int j = 0; j < provas; j++)
			quadro[i][j] = rand() % (100 / provas) + 1;
		
	//NOMES DOS ALUNOS
	char nome[alunos][100];
	
	for (int i = 0; i < alunos; i++)
	{
		printf("Digite o nome do %dº aluno: ", i + 1);
		scanf(" %[^\n]s", nome[i]);
		system("clear");
	}
	
	//TURMA
	printf("\t\t----TURMA----\n\n");	
	printf("ALUNOS\n");
	
	for (int i = 0; i < alunos; i++)
		printf("%d. %s\n", i + 1, nome[i]);
	
	printf("\n\n\n");
	
	//QUADRO DE NOTAS
	printf("\t\t----QUADRO DE NOTAS----\n\n");
	printf("ALUNOS\t\t");
	
	//ORGANIZAÇÃO DO QUADRO DE NOTAS
	for (int i = 0; i < provas; i++)
		printf("NOTA %d\t\t", i + 1);
		
		
	for (int i = 0; i < alunos; i++)
	{
		printf("\n");
		printf("%d. %.4s", i + 1, nome[i]);
		for (int j = 0; j < provas; j++)
			printf("\t\t%d", quadro[i][j]);
	}
	
	printf("\n\n\n\n");
	printf("\t\t----QUADRO DE APROVAÇÃO----\n\n");
	
	//NOTA FINAL, QUEM FOI APROVADO E QUEM FOI REPROVADO 
	printf("ALUNOS\t\t\tRESULTADO\t\t\tTOTAL");
	
	for (int i = 0; i < alunos; i++)
	{
		int soma = 0;
		printf("\n");
		printf("%d. %.4s\t\t\t", i + 1, nome[i]);
		for (int j = 0; j < provas; j++)
			soma += quadro[i][j]; 		
		if (soma >= 60)
				printf("APROVADO\t\t\t");
				else if (soma >= 40 && soma < 60)
					printf("PROVA FINAL\t\t\t");
					else if (soma < 40)
						printf("REPROVADO\t\t\t");
		printf("%d", soma);
	}
		
	//ALUNOS ACIMA DA MÉDIA
	printf("\n\n\n");
	printf("\t----ALUNOS QUE FICARAM ACIMA DA MÉDIA----\n\n");
	printf("ALUNOS");
	
	for (int i = 0; i < alunos; i++)
	{
		int soma; 
		for (int j = 0; j < provas; j++)
		{
			soma += quadro[i][j];	
		}
		if (soma > 60)
			printf("\n%d. %s\t\t\t", i + 1, nome[i]);
		soma = 0;
	}	
	return 0;
}

