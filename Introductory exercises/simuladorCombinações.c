#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define S  100000

int main(){
	srand(time(NULL));
	int n;
	
	do
	{
	
		printf("Digite um número qualquer: ");
		scanf(" %d", &n);
	
		if (!n)
		{
			system("clear");
			printf("Parte 1 finalizada!\n");
			break;
		}
	
		int conj[n];
		int cont = 0, test = 1;
	
		for (int i = 0; i < S; i++)
		{	
			for (int j = 0; j < n; j++)
			{
				conj[j] = rand() % ((2 * n) + 1);
				for (int k = j - 1; k >= 0; k--)
					if (conj[j] == conj[k])
					{
						test = 0;
						break;
					}
				if (!test)
				{
					cont++;
					test = 1;	
					break;
				}							
			}
		}	
	
		float perc = ((float)(S - cont) * 100) / S;
	
		printf("Total de conjuntos não repetitivos formados por %d números: %f%%\n\n", n, perc); 
	
	} while (1);
	
	int enter;	
	printf("\nPressione 'ENTER' para prosseguir. ");
	getchar();
	while ((enter = getchar()) != '\n' && enter != EOF);
	
	n = 0;
		
	do
	{
		n++;
		int conj[n];
		int cont = 0, test = 1;
	
		for (int i = 0; i < S; i++)
		{	
			for (int j = 0; j < n; j++)
			{		
				conj[j] = rand() % ((n*2) + 1);
				for (int k = j - 1; k >= 0; k--)
					if (conj[j] == conj[k])
					{
						test = 0;
						break;
					}
					
				if (!test)
				{
					cont++;
					test = 1;	
					break;
				}							
			}
		}
	
	
		float perc = ((float)(S - cont) * 100) / S;
		
		printf("\nTotal de conjuntos não repetitivos formados por %d números: %f%%", n, perc); 
		
		if (perc == 0)
		{
			printf("\nPrograma finalizado!\n");
			break;
		}
		
		
	} while (1);	
	
	return 0;
}
