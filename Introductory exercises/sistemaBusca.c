#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10000

int main(){
	srand(time(NULL));
	int n[N];

	for (int i = 0; i < N; i++)
		n[i] = 1 + rand() % 100;

	for (int i = 0; i < N - 1; i++)
	{
		int troca;
		for (int j = i + 1; j < N; j++)
			if (n[i] > n[j])
			{
				troca = n[i];
				n[i] = n[j];
				n[j] = troca;
			}
	}

	int maior = N - 1;
	int menor = 0;
	int loc;
	int flag;
	
	printf("Digite o número desejado: ");
	scanf(" %d", &loc);
	
	for (int i = 0; i < N; i++)
	{
		flag = (maior + menor) / 2;	
		if (loc==n[flag])
		{
			printf("\nNúmero %d encontrado com %d tentativas!", n[flag], i + 1);
			break;
		}

		else if (flag < 1 || flag == N - 1)
		{
			printf("\nNúmero %d não encontrado em nosso banco de dados!", loc);
			break;
		}		
		
		else if (loc>n[flag])
			menor = flag + 1;
		
		else if (loc<n[flag])
			maior = flag - 1;
	}
	
	return 0;
}

