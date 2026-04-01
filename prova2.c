#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define S 300

int main()
{
	srand(time(NULL));
	
	int n;
	int dias = 1; 
	int vld = 0;
	int cont2 = 0;
	
	do
	{
		if (!vld)
		{
			printf("Digite a quantidade de alunos: ");
			scanf(" %d", &n);
			printf("Para um grupo de %d pessoas terem probalidade inferior a 10%% de fazerem anivérsário no mesmo dia, serão necessários:\n", n);
		}
		
		if (n<=0)
		{
			system("clear");
			printf("Programa finalizado!");
			break;
		}
	
		int nasc[n];
		int cont = 0, test = 0; 
	
		for (int i = 0; i < S; i++)
			for (int j = 0; j < n; j++)
			{
				nasc[j] = 1 + rand() % dias;		
				for (int k = j - 1; k >= 0; k--)
				{
					if (nasc[j] == nasc[k])
					{
						test = 1;
						break;
					}
				}
				if (test)
				{
					test = 0;
					cont++;
					break;
				}
			}
	
		float porc = ((float)cont / S) * 100;
		
		if (porc < 10)
		{
			printf("%d dias!\n", dias);
			cont2++;
			dias = 1;
			if (cont2==10)
			{
				cont2 = 0;

				vld = 0;
				continue;
			}
		}	
		
		vld++;
		dias++;
		
	} while (1);
	
	return 0;
}

