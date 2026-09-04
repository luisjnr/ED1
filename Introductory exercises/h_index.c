#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int n;
	
	printf("Digite a quantidade de artigos: ");
	scanf(" %d", &n);
	
	int art[n];
	
//GERAÇÃO DOS NÚMEROS ALÉATORIOS 
	printf("Artigos postados: ");
	
	for (int i = 0; i < n; i++)
	{
		art[i] = 1 + rand() % n;
		printf("%d ", art[i]);	
	}
	
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (art[i] < art[j])
			{
				int troca = art[i];
				art[i] = art[j];
				art[j] = troca;
			}	
		
	for (int i = 0; i < n; i++)
		if (art[i] < i + 1)
		{
			printf("\nH-INDEX: %d", art[i - 1]);
			break;
		}
		
	return 0;
}

