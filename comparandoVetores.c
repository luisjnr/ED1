#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int x, y;
	
	printf("Digite dois números consecutivos: ");
	scanf(" %d %d", &x, &y);
	
	int xis[x], ips[y];

//SORTEIO X	
	for (int i = 0; i < x; i++)
	{
		xis[i] = rand() % ((x + y) + 1);
		for (int j = i - 1; j >= 0; j--)
			if (xis[i] == xis[j])
			{
				i--;
				break;
			}
	}

//SORTEIO Y		
	for (int i = 0; i < y; i++)
	{
		ips[i] = rand() % ((x + y) + 1);
		for (int j = i - 1; j >= 0; j--)
			if (ips[i] == ips[j])
			{
				i--;
				break;
			}
	}
	
//NUMEROS DE X	
	printf("Números do vetor x: ");
	
	for (int i = 0; i < x; i++)
		printf("%d ", xis[i]);

//NUMEROS DE Y
	printf("\nNúmeros do vetor y: ");
		
	for (int i = 0; i < y; i++)
		printf("%d ", ips[i]);	
	
//NUMEROS EXCLUSIVOS DE X
	printf("\nNúmeros exclusivos do vetor x: ");
	
	for (int i = 0; i < x; i++)
	{
		int test = 0;
		for (int j = 0; j < y; j++)
		{
			if (xis[i] == ips[j])
			test = 1;
		}
		if (!test)
			printf("%d ", xis[i]);
	}
	
//NUMEROS EXCLUSIVOS DE y
	printf("\nNúmeros exclusivos do vetor y: ");
	
	for (int i = 0; i < y; i++)
	{
		int test = 0;
		for (int j = 0; j < x; j++)
		{
			if (ips[i] == xis[j])
			test = 1;
		}
		if (!test)
			printf("%d ", ips[i]);
	}
	
	printf("\nVetor x: %d", x);
	printf("\nVetor y: %d", y);

	return 0;
}

