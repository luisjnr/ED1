#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct{
	char placa[50];
	char modelo[50];
	char nome[100];
	int flag;
	int id;
}Estacionamento;

FILE* abrirArquivo(char nome[]){
	FILE *arquivo = fopen(nome, "rb+");
	if(!arquivo)
		arquivo = fopen(nome, "wb+");
	if(!arquivo)
		printf("Erro ao abrir arquivo!\n");
	return arquivo;
}

int interface(){
	int opc;
	printf("1 - Entrada de carro\n" "2 - Saída de carro\n" "3 - Utilização atual\n"
	"4 - Listar carros\n" "5 - Excluir carro\n" "6 - Encerrar\n");
	scanf(" %d", &opc);
	system("clear");
	return opc;
}

void verificador(char frase[]){
	printf("%s", frase);
	printf("Pressione 'ENTER' para prosseguir. ");
	getchar();
	while(getchar() != '\n');
	system("clear");
}

void cadastrarCarro(Estacionamento *dados, FILE *arquivo){
	int contador = 0;		
	fseek(arquivo, 0, SEEK_SET);	
	while(fread(dados, sizeof(Estacionamento), 1, arquivo))
		contador++;
	dados->id = contador + 1;
	printf("-----------------------------------------------------------------------------\n"
	"Cadastro de novo carro:\n" "Modelo/Cor: ");
	scanf(" %[^\n]s", dados->modelo);
	printf("Proprietário: ");
	scanf(" %[^\n]s", dados->nome);
}

void entradaCarro(Estacionamento *dados, FILE *arquivo){
	char placa[50];
	int flag = 0;
	printf("\t===== Entrada no Estacionamento =====\n\n" 
	"Placa do veículo: ");
	scanf(" %[^\n]s", placa);
	for (int i = 0; i < strlen(placa); i++)
		placa[i] = toupper(placa[i]);
	fseek(arquivo, 0, SEEK_SET);
	while(fread(dados, sizeof(Estacionamento), 1, arquivo))
		if(!strcmp(placa, dados->placa)){
			flag = 1;
			break;
		}	
	if(!flag){
		printf("Carro não encontrado na base de dados. Faça o Cadastro:\n\n");
		cadastrarCarro(dados, arquivo);
		strcpy(dados->placa, placa);
		dados->flag = 1;
		fseek(arquivo, 0, SEEK_END);
		fwrite(dados, sizeof(Estacionamento), 1, arquivo);
		fflush(arquivo);
		verificador("Veículo cadastrado e estacionado com sucesso!\n" 
		"-----------------------------------------------------------------------------\n");
	}
	else{
		printf("-----------------------------------------------------------------------------\n"
		"Veículo:\n" "Id: %02d\n" "Placa: %s\n" "Modelo/Cor: %s\n"
		"Proprietário: %s\n", dados->id, dados->placa, dados->modelo, dados->nome);
		if(!dados->flag){
			dados->flag = 1;
			fseek(arquivo, -sizeof(Estacionamento), SEEK_CUR);
			fwrite(dados, sizeof(Estacionamento), 1, arquivo);
			fflush(arquivo);
			verificador("Veículo estacionado com sucesso!\n"
			"-----------------------------------------------------------------------------\n");
		}	
		else
			verificador("Veículo já está estacionado!");
	}
}

void saidaCarro(Estacionamento *dados, FILE *arquivo){
	char placa[50];
	int flag = 0;
	printf("\t===== Saída do Estacionamento =====\n\n"
	"Placa do veículo: ");
	scanf(" %s", placa);
	for(int i = 0; i < strlen(placa); i++)
		placa[i] = toupper(placa[i]);
	fseek(arquivo, 0, SEEK_SET);
	while(fread(dados, sizeof(Estacionamento), 1, arquivo))
		if(!strcmp(placa, dados->placa)){
			flag = 1;
			break;
		}
	if(!flag)
		verificador("O Veículo não está devidamente cadastrado!\n");
	else{
		printf("-----------------------------------------------------------------------------\n"
		"Veículo:\n" "Id: %02d\n" "Placa: %s\n" "Modelo/Cor: %s\n"
		"Proprietário: %s\n", dados->id, dados->placa, dados->modelo, dados->nome);
		if (!dados->flag){
			verificador("Veículo não está estacionado!\n" 
			"-----------------------------------------------------------------------------\n");
		}	
		else{
			dados->flag = 0;
			fseek(arquivo, -sizeof(Estacionamento), SEEK_CUR);
			fwrite(dados, sizeof(Estacionamento), 1, arquivo);
			fflush(arquivo);
			verificador("Saída do veículo confirmada!\n" 
			"-----------------------------------------------------------------------------\n");
		}
	}
}

void utilizacaoAtual(Estacionamento *dados, FILE *arquivo){
	int contador = 0;
	printf("\t===== Utilização do Estacionamento =====\n\n");
	fseek(arquivo, 0, SEEK_SET);
	while(fread(dados, sizeof(Estacionamento), 1, arquivo))
		if(dados->flag){
			contador++;
			printf("-----------------------------------------------------------------------------\n"
			"Id: %d - Placa: %s - Modelo/Cor: %s - Proprietário: %s\n"
			, dados->id, dados->placa, dados->modelo, dados->nome);
		}
		
	printf("-----------------------------------------------------------------------------\n"
	"%d veículo(s) estacionado(s)\n", contador);
	verificador("\n");
}

void ordenarEstacionamento(Estacionamento *dados, int n){
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if(dados[i].id > dados[j].id){
				Estacionamento troca = dados[i];
				dados[i] = dados[j];
				dados[j] = troca;
			}
}

void listarCarro(FILE *arquivo){
	fseek(arquivo, 0, SEEK_END);
	int n = ftell(arquivo) / sizeof(Estacionamento);
	fseek(arquivo, 0, SEEK_SET);
	Estacionamento dados[n];
	fread(dados, n * sizeof(Estacionamento), 1, arquivo);
	ordenarEstacionamento(dados, n);
	fseek(arquivo, 0, SEEK_SET);
	fwrite(dados, n * sizeof(Estacionamento), 1, arquivo);
	fflush(arquivo);
	fseek(arquivo, 0, SEEK_SET);
	while(fread(dados, sizeof(Estacionamento), 1, arquivo)){
			printf("-----------------------------------------------------------------------------\n"
			"Id: %02d - Placa: %s - Modelo/Cor %s - Proprietário: %s\n" 
			"-----------------------------------------------------------------------------\n"
			, dados->id, dados->placa, dados->modelo, dados->nome);
	}
	verificador("\n");
}

void excluirCarro(FILE *arquivo, char frase[]){
	char placa[50];
	printf("===== Exclusão do Estacionamento =====\n\n"
	"Placa: ");
	scanf(" %s", placa);
	for (int i = 0; i < strlen(placa); i++)
		placa[i] = toupper(placa[i]);
	int posicao = 0, flag = 0;
	fseek(arquivo, 0, SEEK_END);
	int n = ftell(arquivo) / sizeof(Estacionamento);
	fseek(arquivo, 0, SEEK_SET);
	Estacionamento dados[n];
	fread(dados, n * sizeof(Estacionamento), 1, arquivo);
	for (int i = 0; i < n; i++)
		if(!strcmp(placa, dados[i].placa)){
			posicao = i;
			flag = 1;
			break;
		}
	if (!flag){
		printf("Placa não encontrada em nosso banco de dados!\n");
		verificador("\n");
	}
	else{	
		for (int i = posicao; i < n; i++){
			dados[i] = dados[i + 1];
			dados[i].id--;
		}	
		fclose(arquivo);
		arquivo = fopen(frase, "wb+");
		fwrite(dados, (n - 1) * sizeof(Estacionamento), 1, arquivo);
		fflush(arquivo);
		printf("Veículo excluido com sucesso!\n");
		verificador("\n");
	}
}

int main(){
	FILE *arquivo = abrirArquivo("estacionamento.txt");
	Estacionamento dados;
	do{
		switch (interface())
		{
			case 1: entradaCarro(&dados, arquivo);
				break;
			
			case 2: saidaCarro(&dados, arquivo);	
				break;
				
			case 3: utilizacaoAtual(&dados, arquivo);
				break;
				
			case 4: listarCarro(arquivo);
				break;
				
			case 5: excluirCarro(arquivo, "estacionamento.txt");
				break;
				
			case 6: printf("Programa finalizado!\n");
				fclose(arquivo);
				return 0;
				break;
			default: verificador("Opção inválida!\nTente novamente...\n");
				
		}
		
	} while (1);
}

