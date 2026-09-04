#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct{
	char nome_aluno[MAX];
	int matricula_aluno;	
}Aluno;

typedef struct{
	char nome_disciplina[MAX];
	int codigo_disciplina;
	int periodo;
	int matricula_disciplina[50];
	int cont_alunos_disciplina;
}Disciplina;

typedef struct{
	Aluno cad_aluno[MAX];
	Disciplina cad_disciplina[MAX];
	int cont_aluno;
	int cont_matricula;
	int cont_disciplina;
	int cont_codigo;
}Lista;

Lista contadorGeral();

int opcaoGeral(Lista *ptrlista){
	int opc;
	do{
		printf("1. Cadastrar aluno\n");
		printf("2. Cadastrar disciplina\n");
		printf("3. Matricular aluno à uma disciplina\n");
		printf("4. Excluir aluno de uma disciplina\n");
		printf("5. Fazer chamada\n");
		printf("6. Histórico do aluno\n");
		printf("7. Encerrar programa\n");
		scanf(" %d", &opc);
		if (opc > 2 && (!ptrlista->cont_aluno || !ptrlista->cont_disciplina)){
			system("clear");
			printf("Nenhuma disciplina ou aluno foi cadastrada!\n\n");
			continue;
		}
		if (opc < 1 || opc > 7){
			system("clear");
			printf("Opção inexistente!\n");
			printf("Tente novamente...\n\n");
			continue;
		}
		else return opc;
	} while (1);
}

Lista contadorGeral(){
	Lista contador;
	contador.cont_aluno = 0;
	contador.cont_matricula = 1;
	contador.cont_disciplina = 0;
	contador.cont_codigo = 1; 
	return contador;
}
	
int verificarAluno(Lista *ptrlista, Aluno dados_aluno){
	for (int i = 0; i < ptrlista->cont_aluno; i++)
		if (!strcmp(dados_aluno.nome_aluno, ptrlista->cad_aluno[i].nome_aluno))
			return 0;
	return 1;
}
	
Aluno dadosAluno(Lista *ptrlista){
	Aluno novo;
	system("clear");
	do{
		printf("CADASTRO DO ALUNO\n");
		printf("Nome: ");
		scanf(" %[^\n]s", novo.nome_aluno);
		if (!verificarAluno(ptrlista, novo))
		{
			system("clear");
			printf("Aluno já cadastrado!\n");
			printf("Tente novamente...\n\n");
			continue;
		}
		else break;
	}while(1);	
	novo.matricula_aluno = ptrlista->cont_matricula;
	system("clear");
	printf("Aluno cadastrado com sucesso!\n\n");
	return novo;
}

void listaAluno(Lista *ptrlista, Aluno dados){
	ptrlista->cad_aluno[ptrlista->cont_aluno] = dados;
	ptrlista->cont_aluno++;
	ptrlista->cont_matricula++;
}

int verificadorDisciplina(Lista *ptrlista, Disciplina dados_disciplina){
	for (int i = 0; i < ptrlista->cont_disciplina; i++)
		if (!strcmp(dados_disciplina.nome_disciplina, ptrlista->cad_disciplina[i].nome_disciplina))
			return 0;
	return 1;
}

Disciplina dadosDisciplina(Lista *ptrlista){
	Disciplina novo;
	system("clear");
	do{		
		printf("CADASTRO DA DISCIPLINA\n");
		printf("Nome: ");
		scanf(" %s", novo.nome_disciplina);
		if (!verificadorDisciplina(ptrlista, novo)){
			system("clear");
			printf("Disciplina já cadastrada!\n");
			printf("Tente novamente...\n\n");
			continue;
		}
		else break;
	}while(1);
	printf("Período: ");
	scanf(" %d", &novo.periodo);
	novo.codigo_disciplina = ptrlista->cont_codigo;
	system("clear");
	printf("Disciplina cadastrada com sucesso!\n\n");
	return novo;
}

void listaDisciplina(Lista *ptrlista, Disciplina dados){
	ptrlista->cad_disciplina[ptrlista->cont_disciplina] = dados;
	ptrlista->cad_disciplina[ptrlista->cont_disciplina].cont_alunos_disciplina = 0;
	ptrlista->cont_disciplina++;
	ptrlista->cont_codigo++; 
}

int buscarAluno(Lista *ptrlista, Aluno dados_aluno, int *posicao){
	for (int i = 0; i < ptrlista->cont_aluno; i++)
		if (!strcmp(dados_aluno.nome_aluno, ptrlista->cad_aluno[i].nome_aluno))
			*posicao = i;
	return *posicao;
}

int buscarDisciplina(Lista *ptrlista, Disciplina dados_disciplina, int *posicao){
	for (int i = 0; i < ptrlista->cont_disciplina; i++)
		if (!strcmp(dados_disciplina.nome_disciplina, ptrlista->cad_disciplina[i].nome_disciplina))
			*posicao = i;
	return *posicao;
}

Aluno listarAlunos(Lista *ptrlista){
	system("clear");
	Aluno dados;
	do{
		printf("LISTA DE ALUNOS\n\n");
		printf("MATRICULA\t\tNOME\n");
		for (int i = 0; i < ptrlista->cont_aluno; i++)
			printf("%02d\t\t\t%s\n", ptrlista->cad_aluno[i].matricula_aluno, 
			ptrlista->cad_aluno[i].nome_aluno);
		printf("\n");
		printf("Digite o nome do aluno: ");
		scanf(" %[^\n]s", dados.nome_aluno);
		if (verificarAluno(ptrlista, dados)){
			system("clear");
			printf("Aluno não encontrado!\n");
			printf("Tente novamente...\n\n");
			continue;
		}
		else return dados;
	}while(1);
}

Disciplina listarDisciplina(Lista *ptrlista){
	Disciplina dados;
	system("clear");
	do{
		printf("LISTA DE DISCIPLINAS\n\n");
		printf("PERIODO\t\tDISCIPLINA\n");
		for (int i = 0; i < ptrlista->cont_disciplina; i++)
			printf("%02d\t\t%s\n", ptrlista->cad_disciplina[i].periodo, 
			ptrlista->cad_disciplina[i].nome_disciplina);
		printf("\n");
		printf("Digite o nome da disciplina: ");
		scanf(" %[^\n]s", dados.nome_disciplina);
		if (verificadorDisciplina(ptrlista, dados)){
			system("clear");
			printf("Disciplina não encontrada!\n");
			printf("Tente novamente...\n\n");
			continue;
		}
		else 
		return dados;
	}while(1);
}

void matricularDisciplina(Lista *ptrlista, Aluno dados_aluno, Disciplina dados_disciplina){
	int posicao_aluno;	
	int posicao_disciplina;
	int flag = 0;
	buscarAluno(ptrlista, dados_aluno, &posicao_aluno);
	buscarDisciplina(ptrlista, dados_disciplina, &posicao_disciplina);
	for (int i = 0; i < ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina; i++)
		if (ptrlista->cad_aluno[posicao_aluno].matricula_aluno 
		== ptrlista->cad_disciplina[posicao_disciplina].matricula_disciplina[i])
			flag = 1;
	if (!flag){		
		ptrlista->cad_disciplina[posicao_disciplina].matricula_disciplina[ptrlista->
		cad_disciplina[posicao_disciplina].cont_alunos_disciplina] = ptrlista->cad_aluno[posicao_aluno].matricula_aluno;
		ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina++;
		system("clear");
		printf("Aluno matriculado com sucesso!\n\n");
	}
	else{
		system("clear");
		printf("O Aluno já possui matricula nessa disciplina!\n\n");
	}
}

int buscarAlunoCodigo(Lista *ptrlista, int codigo, int *posicao){
	for (int i = 0; i < ptrlista->cont_aluno; i++)
		if (codigo == ptrlista->cad_aluno[i].matricula_aluno)
			*posicao = i;
	return *posicao;
}

void excluirAluno(Lista *ptrlista, Disciplina dados_disciplina){
	int posicao_disciplina;
	Aluno dados_aluno;
	buscarDisciplina(ptrlista, dados_disciplina, &posicao_disciplina);
	int posicao_cod;
	if (!ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina){
		system("clear");
		printf("Não existem alunos nessa disciplina!\n\n");
		return;
	}
	system("clear");
	do{
		int posicao_aluno;
		int flag = 0;
		printf("LISTA DE ALUNOS\n\n");
		printf("MATRICULA\t\tNOME\n");
		for (int i = 0; i < ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina; i++){
			int codigo = ptrlista->cad_disciplina[posicao_disciplina].matricula_disciplina[i];
			buscarAlunoCodigo(ptrlista, codigo, &posicao_aluno);
			printf("%d\t\t\t%s\n", ptrlista->cad_aluno[posicao_aluno].matricula_aluno, 
			ptrlista->cad_aluno[posicao_aluno].nome_aluno);
		}
		printf("\nDigite o nome do aluno à ser excluido: ");
		scanf(" %[^\n]s", dados_aluno.nome_aluno);
		buscarAluno(ptrlista, dados_aluno, &posicao_aluno);
		for (int i = 0; i < ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina; i++)
			if (ptrlista->cad_aluno[posicao_aluno].matricula_aluno 
			== ptrlista->cad_disciplina[posicao_disciplina].matricula_disciplina[i]){
				flag = 1;
				posicao_cod = i;
				break;
			}
		if (!flag){
			system("clear");
			printf("Nome incorreto!\n");
			printf("Tente novamente...\n\n");
			continue;
		}
		else break;
	}while(1);
	for (int i = posicao_cod; i 
	< ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina; i++)
		ptrlista->cad_disciplina[posicao_disciplina].matricula_disciplina[i] =
		ptrlista->cad_disciplina[posicao_disciplina].matricula_disciplina[i + 1];
	ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina--;
	system("clear");
	printf("Aluno excluido com sucesso!\n\n");
}	

void ordenarAluno(Lista *ptrlista){
	for (int i = 0; i < ptrlista->cont_aluno - 1; i++)
		for (int j = i + 1; j < ptrlista->cont_aluno; j++)
			if (strcmp(ptrlista->cad_aluno[i].nome_aluno, 
			ptrlista->cad_aluno[j].nome_aluno) > 0){
				Aluno troca = ptrlista->cad_aluno[i];
				ptrlista->cad_aluno[i] = ptrlista->cad_aluno[j];
				ptrlista->cad_aluno[j] = troca;
			}
}

void chamadaDisciplina(Lista *ptrlista, Disciplina dados_disciplina){
int posicao_disciplina;
	buscarDisciplina(ptrlista, dados_disciplina, &posicao_disciplina);
	if (!ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina){
		system("clear");
		printf("Não existem alunos nessa disciplina!\n\n");
		return;
	}
	system("clear");
	int posicao_aluno;
		printf("LISTA DE CHAMADA DA DISCIPLINA: %s\n\n", dados_disciplina.nome_disciplina);
		printf("LISTA DE ALUNOS\n\n");
		printf("MATRICULA\t\tNOME\n");
		for (int i = 0; i < ptrlista->cad_disciplina[posicao_disciplina].cont_alunos_disciplina; i++){
			int codigo = ptrlista->cad_disciplina[posicao_disciplina].matricula_disciplina[i];
			buscarAlunoCodigo(ptrlista, codigo, &posicao_aluno);
			printf("%02d\t\t\t%s\n", ptrlista->cad_aluno[posicao_aluno].matricula_aluno, 
			ptrlista->cad_aluno[posicao_aluno].nome_aluno);
		}
	char enter;
	printf("\nPRESSIONE 'ENTER' PARA PROSSEGUIR. ");
	getchar();
	while((enter = getchar()) != '\n' && enter != EOF);
	system("clear");
}

void ordenarDisciplina(Lista *ptrlista){
	for (int i = 0; i < ptrlista->cont_disciplina - 1; i++)
		for (int j = i + 1; j < ptrlista->cont_disciplina; j++)
			if (ptrlista->cad_disciplina[i].periodo 
			> ptrlista->cad_disciplina[j].periodo){
				Disciplina troca = ptrlista->cad_disciplina[i];
				ptrlista->cad_disciplina[i] = ptrlista->cad_disciplina[j];
				ptrlista->cad_disciplina[j] = troca;
			}
}

void historicoAluno(Lista *ptrlista, Aluno dados_aluno){
	system("clear");
	int flag = 0;
	int posicao_aluno;
	buscarAluno(ptrlista, dados_aluno, &posicao_aluno);
	for (int i = 0; i < ptrlista->cont_disciplina; i++)
		for (int j = 0; j < ptrlista->cad_disciplina[i].cont_alunos_disciplina; j++)
			if (ptrlista->cad_aluno[posicao_aluno].matricula_aluno 
			== ptrlista->cad_disciplina[i].matricula_disciplina[j])
				flag = 1;
	if (!flag)
	{
		system("clear");
		printf("Esse aluno não possui histórico de disciplinas!\n\n");
		return;
	}
	printf("HISTÓRICO DO ALUNO: %s\n\n", dados_aluno.nome_aluno);
	printf("LISTA DE DISCIPLINAS\n\n");
	printf("PERIODO\t\tNOME\n");
	for (int i = 0; i < ptrlista->cont_disciplina; i++)
		for (int j = 0; j < ptrlista->cad_disciplina[i].cont_alunos_disciplina; j++)
			if (ptrlista->cad_aluno[posicao_aluno].matricula_aluno 
			== ptrlista->cad_disciplina[i].matricula_disciplina[j])
				printf("%02d\t\t%s\n", ptrlista->cad_disciplina[i].periodo, 
				ptrlista->cad_disciplina[i].nome_disciplina);
	char enter;
	printf("\nPRESSIONE 'ENTER' PARA PROSSEGUIR. ");
	getchar();
	while((enter = getchar()) != '\n' && enter != EOF);
	system("clear");
}

int main(){
	Lista listacad = contadorGeral();
	do{
		switch (opcaoGeral(&listacad)){
			case 1: Aluno dados_aluno = dadosAluno(&listacad); 
				listaAluno(&listacad, dados_aluno);
				ordenarAluno(&listacad);
				break;
			case 2: Disciplina dados_disciplina = dadosDisciplina(&listacad);
				listaDisciplina(&listacad, dados_disciplina);
				ordenarDisciplina(&listacad);
				break;
			case 3: dados_aluno = listarAlunos(&listacad);
				dados_disciplina = listarDisciplina(&listacad);
				matricularDisciplina(&listacad, dados_aluno, dados_disciplina);
				break;
			case 4: dados_disciplina = listarDisciplina(&listacad);
				excluirAluno(&listacad, dados_disciplina);
				break;
			case 5: dados_disciplina = listarDisciplina(&listacad);
				chamadaDisciplina(&listacad, dados_disciplina);
				break;
			case 6:dados_aluno = listarAlunos(&listacad);
				historicoAluno(&listacad, dados_aluno);
				break;
			case 7: system("clear"); 
				printf("Programa finalizado.");
				return 0;	 
		}
	} while (1);
}
