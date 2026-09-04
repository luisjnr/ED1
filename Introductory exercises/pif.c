#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 9

int main(){
	
	int cartas[N];
	int esc = 0 ;
	srand (time(NULL));
	
	printf("Cartas recebidas:\n");
		
	//Sorteando as cartas
	for (int i = 0; i < N; i++){
		cartas[i] = 1 + rand() % 10;
	}
	//Printando as cartas sorteadas
	for (int i = 0; i < N; i++){		
			printf ("[%02d] ", cartas[i]);
	}
		
	// Ordenando as cartas
	for (int i = 0; i < N - 1; i++){
		int troca; 
			
		for (int j = i + 1; j < N; j++)
			if (cartas[i] > cartas[j]){
				troca = cartas[i];
				cartas[i] = cartas[j];
				cartas[j] = troca;
			}
		}
		
	printf("\n\nCartas ordenadas:\n");
	
	//Printando as cartas de maneira ordenada
	for (int i = 0; i < N; i++)
		printf("[%02d] ", cartas[i]);
			
	printf("\n");	
		
	//Loop de repetição,para que o jogo rode mais de uma vez
	do{
	
	    //Verificação se tem 3 cartas iguais ou 3 cartas em sequẽncia
		for (int i = 0; i <= N; i++)
			if((cartas[i] == cartas[i+1] && cartas[i] == cartas[i+2]) 
				|| (cartas[i] == (cartas[i+1] - 1) && cartas[i+1] == 
				(cartas[i+2] - 1))){	
				cartas[i] = cartas[i + 1] = cartas[i + 2] = 0;
				i += 2;
			}
			
		//Print para quando o jogo acabar.
		if 
		(cartas[0] == 0 && cartas[1] == 0 && cartas[2] == 0 
		&& cartas[3] == 0 && cartas[4] == 0 && cartas[5] == 0 
		&& cartas[6] == 0 && cartas[7] == 0 && cartas[8] == 0){
			printf("\nParabéns você ganhou!!");
			break;
		}
					
		//Printando as cartas após substituição ou trinca feita
		printf("\nCartas após formar a trinca:\n");
			
		for (int i = 0; i < N; i++)		
			if (cartas[i] > 0)
				printf("[%02d] ", cartas[i]);
				
		printf("\n");	
		
		//Ordenação das cartas após substituição
		for (int i = 0; i < N - 1; i++){
			int troca;
	
			for (int j = i + 1; j < N; j++)
				if (cartas[i] > cartas[j]){		
					troca = cartas[i];
					cartas[i] = cartas[j];
					cartas[j] = troca;
			}
		}
			
		//Garantindo que a carta escolhida está entre 1 e 10
		int cont = 0;
		int maior = N - 1, menor = 0, flag;	

		do
		{
			printf("\nEscolha a carta que você deseja substituir: ");
			scanf(" %d", &esc);
			
			system("clear");
			
			for (int i = 0; i < N; i++)
			{
				flag = (maior + menor) / 2;
		
				if (cartas[flag]==esc)
				{
					cont = 1; 
					break;
				}
				
				else if (flag < 1 || flag == N - 1)
					break;
				
				else if (esc>cartas[flag])
					menor = flag + 1;
				
				else if (esc<cartas[flag])
					maior = flag - 1;
			}
			
			if (cont)
				break;
				
			if (!cont)
			{
				printf("\nO número escolhido não existe!\nTente novamente...\n\n");
				maior = N - 1;
				menor = 0;
				for (int i = 0; i < N; i++)			
					if (cartas[i] > 0)
						printf("[%02d] ", cartas[i]);
				
				printf("\n");
			}
				
		} while (1);
			
		//Substituição da carta escolhida e sorteando uma nova pra por no lugar
		
		for (int i = 0; i < N; i++)
			if (esc==cartas[i]){	
				cartas[i] = 1 + rand() % 10;
				break;
			}
	
		//Ordenação das cartas após substituição
		for (int i = 0; i < N - 1; i++){
			int troca;
					
			for (int j = i + 1; j < N; j++)
				if (cartas[i] > cartas[j]){		
					troca = cartas[i];
					cartas[i] = cartas[j];
					cartas[j] = troca;
				}
		}

		printf("Cartas recebidas:\n");
		
		//Printando as cartas recebidas
		for (int i = 0; i < N; i++)				
			if (cartas[i] > 0)
				printf("[%02d] ", cartas[i]);
		
		printf("\n");
	
	} while (1);
}
