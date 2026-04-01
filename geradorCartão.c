#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int opc, vld, acm = 0, rsv;
	char card[17];
	
	//PROGRAMA
	do
	{
		printf("==========  OPÇÕES  ==========\n\n");
		printf("1. Gerar cartão de crédito\n");
		printf("2. Válidar cartão de crédito\n");
		printf("3. Finalizar programa\n");
		scanf(" %d", &opc);
	
	//VALIDAÇÃO DA OPÇÃO 
		if (opc == 3)
		{
			system("clear");
			printf("Programa finalizado!");
			break;
		}
			
		if (opc < 1 || opc > 3)
		{
			system("clear");
			printf("A opção não existe.\nTente Novamente...\n\n");
			continue; 
		}
		
	//GERAÇÃO E VALIDAÇÃO DA OPÇÃO 1
		if (opc == 1)
		{
			
			for (int i = 0; i < 15; i++)
			{
				card[i] = '0' + rand() % 10;
				vld = card[i] - '0';
				
				if (i%2==0)
				{
					vld = vld * 2;
					if (vld >= 10)
					{
						rsv = vld / 10;
						vld = vld % 10;
						vld = rsv + vld;
					}
					
				acm += vld;
				
				}
				else
				acm += vld;
			}
				
				card[16] = 0;
						
				for (int i = 0; i < 10; i++)
				{			
					card[15] = i + '0';
					vld = i;
					
					acm += vld;
					
					if (acm % 10 == 0)
					{
						system("clear");
						printf("Número de cartão válidado>>>> %s\n\n", card);
						break; 	
					}
					
					acm -= vld;
					
				}
				
			acm = 0;	
		
		}
		
	//VALIDADADOR DE NÚMERO DE CARTÃO
		if (opc == 2)
		{
			system("clear");
			
			do
			{
				for (int i = 0; i < 16; i++)
					card[i] = '.';
					
				card[16] = 0;
				printf("Digite o Número do cartão:\n");
				scanf(" %[^\n]s", card);
				
				if (card[16] != 0)
				{
					
					system("clear");
					printf("Limite de digitos atingido/Digite somente números.\nTente Novamente...\n\n");
					continue;
				}
				
				for (int i = 0; i < 16; i++)
				{	
					vld = card[i];
					if (vld < 48 || vld > 57)
					{
						system("clear");
						printf("Quantidade de digitos insuficientes/Digite somente números.\nTente Novamente...\n\n");
						continue;
					}
				}
					
				if (card[16] == 0)
					if (card[15] != '.')
						break;
							
			} while (1);
			
			
			for (int i = 0; i < 16; i++)
			{
				vld = card[i] - '0';
					if (i%2==0)
					{
						vld = vld * 2;
						if (vld >= 10)
						{
							rsv = vld / 10;
							vld = vld % 10;
							vld = rsv + vld;
						}
						acm += vld;
					}
					else
						acm += vld;
				}
				
			if (acm % 10 == 0)
			{
				system("clear");
				printf("Número de cartão válido>>>> %s\n\n", card); 	
			}	
							
			else
			{
				system("clear");
				printf("Número de cartão inválido>>>> %s\n\n", card);
			}
			
			acm = 0;
			
		}
		
	
	} while (1);		
	
	return 0;
}


