#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct{
	char nome[100];
	int tempo;
}Jogador;

FILE* abrirArquivo(char *nome){
	FILE *arq = fopen(nome, "rb+");
	if (!arq)
		arq = fopen(nome, "wb+");
	if (!arq)
		printf("Abertura do Arquivo negada!\n");
	return arq;
}

int interface(char frase[]){
	int opc;
	printf("%s", frase);
	scanf(" %d", &opc);
	system("clear");
	return opc;
}

void erro(char frase[]){
	while(getchar() != '\n');
	system("clear");
	printf("%s", frase);
	printf("Tente novamente...\n");
}

void novoJogador(Jogador *dados, FILE *arq){
	char nome[100];
	do{
		int flag = 0;
		printf("Digite seu nome: ");
		scanf(" %[^\n]s", nome);
		for (int i = 0; i < strlen(nome); i++)
			nome[i] = toupper(nome[i]);
		fseek(arq, 0, SEEK_SET);
		while(fread(dados, sizeof(Jogador), 1, arq))
			if(!strcmp(nome, dados->nome)){
				flag = 1;
				break;
			}
		if(flag){
			printf("Nome já exite!\nTente novamente...\n");
			continue;
		}
		else break;
		
	} while (1);
	dados->tempo = 0;
	strcpy(dados->nome, nome);
	system("clear");
}

void buscarJogador(Jogador *dados, FILE *arq){
	char nome[100];
	do{
		int flag = 1;
		printf("Digite seu nome: ");
		scanf(" %[^\n]s", nome);
		for (int i = 0; i < strlen(nome); i++)
			nome[i] = toupper(nome[i]);
		fseek(arq, 0, SEEK_SET);
		while(fread(dados, sizeof(Jogador), 1, arq))
			if(!strcmp(nome, dados->nome)){
				flag = 0;
				break;
			}
		if(flag){
			printf("Nome não exite!\nTente novamente...\n");
			continue;
		}
		else break;
	} while (1);
	system("clear");
}

void loading(){
	printf("pressione 'ENTER' para iniciar!\n");
	getchar();
	while(getchar() != '\n');
	system("clear");
	for (int i = 0; i < 3; i++){
		printf("%d\n", 3 - i);
		system("sleep 1");
	}	
	printf("GO!!\n");
	system("sleep 1");
	system("clear");
}

void jogo(Jogador *dados){
	int i = 0, inicio, fim;
	inicio = time(NULL);
	do{
		int a = 1 + rand() % 100, b = 1 + rand() % 100, resultado;
		printf("Jogo da adição %d/2\n", i + 1); 
		printf("%d + %d = ", a, b);
		scanf(" %d", &resultado);
		while(getchar() != '\n');
		
		if (a + b == resultado){
			system("clear");
			printf("Acertou!\n");
			i++;
		}
		else{
			system("clear");
			printf("Errou!\n");
		}
		if (i==2)
			break;
	} while (1);
	
	i = 0;
	
	do{
		int a = 1 + rand() % 100, b = 1 + rand() % 100, resultado;
		printf("Jogo da subtração %d/2\n", i + 1); 
		printf("%d - %d = ", a, b);
		scanf(" %d", &resultado);
		while(getchar() != '\n');
		
		if (a - b == resultado){
			system("clear");
			printf("Acertou!\n");
			i++;
		}
		else{
			system("clear");
			printf("Errou!\n");
		}
		if (i==2)
			break;
	} while (1);
	
	i = 0;
	
	do{
		int a = 1 + rand() % 10, b = 1 + rand() % 10, resultado;
		printf("Jogo da multiplicação %d/2\n", i + 1); 
		printf("%d * %d = ", a, b);
		scanf(" %d", &resultado);
		while(getchar() != '\n');
		
		if (a * b == resultado){
			system("clear");
			printf("Acertou!\n");
			i++;
		}
		else{
			system("clear");
			printf("Errou!\n");
		}
		if (i==2)
			break;
	} while (1);
	
	i = 0;
	
	do{
		float a = 1 + rand() % 10, b = 1 + rand() % 10, resultado, verificador;
		printf("Jogo da divisão %d/2\n", i + 1); 
		printf("%0.f / %0.f = ", a, b);
		scanf(" %f", &resultado);
		verificador = (a / b) - resultado;
		if (verificador > -0.1 && verificador < 0.1){
			system("clear");
			printf("Acertou!\n");
			i++;
		}
		else{
			system("clear");
			printf("Errou!\n");
		}
		if (i==2)
			break;
	} while (1);
	
	i = 0;
	
	do{
		float a = 1 + rand() % 10, b = 1 + rand() % 100, resultado;
		printf("Jogo da porcentagem %d/2\n", i + 1); 
		printf("%0.f%% de %0.f = ", a, b);
		scanf(" %f", &resultado);
		while(getchar() != '\n');
		int verificador = ((a/100) * b) - resultado;
		if (verificador > -0.1 && verificador < 0.1){
			system("clear");
			printf("Acertou!\n");
			i++;
		}
		else{
			system("clear");
			printf("Errou!\n");
		}
		if (i==2)
			break;
	} while (1);
	
	fim = time(NULL);
	if(!dados->tempo)
		dados->tempo = fim - inicio;
	else if(fim - inicio < dados->tempo)
			dados->tempo = fim - inicio;
}

void salvarDados(Jogador *dados, FILE *arq){
	fseek(arq, 0, SEEK_END);
	int verificador = fwrite(dados, sizeof(Jogador), 1, arq);
	if (!verificador)
		printf("Falha na inserção de dados!");
	else fflush(arq);
}

void atualizacaoTempo(Jogador *dados, FILE *arq){
	fseek(arq, -sizeof(Jogador), SEEK_CUR);
	int verificador = fwrite(dados, sizeof(Jogador), 1, arq);
	if(!verificador)
		printf("Falha na atualização de dados!");
	else fflush(arq);	
}

void rankingJogadores(Jogador *dados, FILE *arq){
	fseek(arq, 0, SEEK_SET);
	while(fread(dados, sizeof(Jogador), 1, arq))
		printf("Nome -> %s\t\tTempo -> %ds\n", dados->nome, dados->tempo);
	printf("\nPressione 'ENTER' para prosseguir!\n");
	getchar();
	while(getchar() != '\n');
	system("clear");
}

void ordenacaoRanking(FILE *arq){
	fseek(arq, 0, SEEK_END);
	int p = ftell(arq) / sizeof(Jogador);
	fseek(arq, 0, SEEK_SET);
	Jogador lista[p];
	fread(lista, p * sizeof(Jogador), 1, arq);
	
	for (int i = 0; i < p; i++)	
		for (int j = i + 1; j < p; j++)
			if (lista[j].tempo < lista[i].tempo)
			{
				Jogador troca = lista[i];
				lista[i] = lista[j];
				lista[j] = troca;
			}
	fseek(arq, 0, SEEK_SET);		
	fwrite(lista, p * sizeof(Jogador), 1, arq);
	fflush(arq);
}

int main(){
	Jogador dados;
	FILE *arq = abrirArquivo("fonte.txt");
	srand(time(NULL));
	do{
		
		switch (interface("1 - Jogar\n2 - Ranking\n3 - Finaliza jogo\n")){
			case 1: int flag = 0;
				do{
					switch (interface("1 - Novo jogador\n2 - Jogador existente\n")){
						case 1: flag = 1;
							novoJogador(&dados, arq);
							loading();
							jogo(&dados);
							salvarDados(&dados, arq);
							break;
					
						case 2: flag = 1;
							buscarJogador(&dados, arq);
							loading();
							jogo(&dados);
							atualizacaoTempo(&dados, arq);
							break;
						
						default: erro("Opção digitada não exite!\n");
					}
			
				} while (!flag);
				break;
				
			case 2: ordenacaoRanking(arq);
				rankingJogadores(&dados, arq);
				break;
				
			case 3: system("clear"); 
					printf("Jogo encerrado!");
					return 0;
				break;
			default: erro("Opção digitada não exite!\n");
				
		}
		
	} while (1);
	
	fclose(arq);
}

