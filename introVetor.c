#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void inicializar(int vetorAux[], int n){
	if(!n)
		return;
	inicializar(vetorAux + 1, n - 1);
	vetorAux[0] = 0;	
}

void gerarNumeros(int vetor[],  int vetorAux[], int n){
	for (int i = 0; i < n; i++){
		vetor[i] = rand() % n;
		vetorAux[vetor[i]] = 1;
	}
}

void printarNumeros(int vetor[], int n){
	if(!n)
		return;
	printf("[%d]", vetor[0]);
	printarNumeros(vetor + 1, n - 1);
}

void valoresIgualIndice(int vetor[], int n){
	int flag = 0;
	for (int i = 0; i < n; i++)
		if(vetor[i] == i){
			printf("[%d]", vetor[i]);
			flag = 1;
		}
	if(!flag)
		printf("Nenhum");
}

void valoresNaoSorteados(int vetorAux[], int n){
	int flag = 0;
	for (int i = 0; i < n; i++)
		if(!vetorAux[i]){
			printf("[%d]", i);
			flag = 1;
		}
	
	if(!flag)
		printf("Nenhum");
}

void valoresRepetidos(int vetor[], int n){
	int vetorAux[n];
	inicializar(vetorAux, n);
	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			if(vetor[i] == vetor[j])
				vetorAux[vetor[i]] = 1;	
		}
	}
	
	for (int i = 0; i < n; i++)
		if(vetorAux[i])
			printf("[%d]", i);

}

void menorMaior(int vetor[], int n){
	int maior = vetor[0], menor = vetor[0];
	for (int i = 0; i < n/2; i++)
		if (vetor[i] < menor)
			menor = vetor[i];
	for (int i = n/5; i < n; i++)
		if(vetor[i] > maior)
			maior = vetor[i];
	printf("\n\nMenor valor da primeira metade: %d\n", menor);
	printf("Maior valor da segunda metade: %d", maior);
}

void valoresDistintos(int vetorAux[], int n){
	for (int i = 0; i < n; i++)
		if(vetorAux[i])
			printf("[%d]", i);
}

void indice(int vetor[], int n){
	int maior = vetor[0], menor = vetor[0];
	int indiMaior = 0, indiMenor = 0;
	for (int i = 0; i < n; i++){
		if(vetor[i] > maior){
			maior = vetor[i];
			indiMaior = i;
		}
		if(vetor[i] < menor){
			menor = vetor[i];
			indiMenor = i;
		}
	}
	
	printf("\n\nPosição do maior número: [%d]\n", indiMaior);
	printf("Posição do menor número: [%d]\n", indiMenor);
}

void maisMenos(int vetor[], int n){
	int vetorAux[n];
	inicializar(vetorAux, n);
	for (int i = 0; i < n - 1; i++){
		if(!vetorAux[vetor[i]]){
			vetorAux[vetor[i]] = 1;
			for (int j = i + 1; j < n; j++)
				if(vetor[i] == vetor[j])
					vetorAux[vetor[i]]++;
		}
	}
	
	int maior = 0, menor = n;
	
	for (int i = 0; i < n; i++){
		if(vetorAux[i] && vetorAux[i] > maior)
			maior = vetorAux[i];
		if(vetorAux[i] && vetorAux[i] < menor)
			menor = vetorAux[i];
	}
	
	printf("\nValores mais vezes repetidos: %d vez(es)\n", maior);
	
	for (int i = 0; i < n; i++){
		if(maior == vetorAux[i])
			printf("[%d]", i);
	}
	
	printf("\n\nValores menos vezes repetidos: %d vez(es)\n", menor);
	
	for (int i = 0; i < n; i++){
		if(menor == vetorAux[i])
			printf("[%d]", i);
	}
}

int main(){
	srand(time(NULL));
	int n;
	printf("Digite o valor de N: ");
	scanf(" %d", &n);
	int vetor[n];
	int vetorAux[n];
	inicializar(vetorAux, n);
	gerarNumeros(vetor, vetorAux, n);
	printf("\nNúmeros aléatorios:\n");
	printarNumeros(vetor, n);
	printf("\n\nValores iguais ao índice:\n");
	valoresIgualIndice(vetor, n);
	printf("\n\nValores não sorteados:\n");
	valoresNaoSorteados(vetorAux, n);
	printf("\n\nValores repetidos:\n");
	valoresRepetidos(vetor, n);
	menorMaior(vetor, n);
	printf("\n\nValores distintos:\n");
	valoresDistintos(vetorAux, n);
	indice(vetor, n);
	maisMenos(vetor, n);
}
