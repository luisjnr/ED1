#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int cod;
	char desc[100];
	float val; 
	int est;
}Produto;

#define N 100

int main()
{
	Produto p[N];
	int cont = 0;
	
	//CADASTRO DE PRODUTOS
	do
	{
		//CADASTRO DO CÓDIGO
		int test;
		printf("----CADATRO DO PRODUTO %d----\n\n", cont + 1);
		printf("Digite o código do produto:\n0 - Finalizar cadastro. ");
		scanf(" %d", &test);
		
		//FINALIZA 
		if (test <= 0)
		{
			system("clear");
			printf("Cadastro finalizado!\n\n");
			break;
		}
	
		//ORDENAÇÃO DE PRODUTOS
		for (int i = 0; i < cont - 1; i++)
			for (int j = i + 1; j < cont; j++)
				if (p[i].cod > p[j].cod)
				{
					Produto troca = p[i];
					p[i] = p[j];
					p[j] = troca; 
				}
		
		//TESTE DO CÓDIGO
		int flag, maior = cont, menor = 0;
		
		do
		{
			flag = (maior + menor) / 2;
			
			if (test == p[flag].cod)
			{
				system("clear");
				printf("O código informado ja está cadastrado!\n");
				printf("Tente novamente...\n");
				printf("Digite o código do produto: ");
				scanf(" %d", &test);
				system("clear");
			}
			
			else if (flag == 0 || flag == cont - 1)
				break;
				
			else if (test < p[flag].cod)
				maior = flag - 1;
				
			else if (test > p[flag].cod)
				menor = flag + 1;
			
		} while (1);
		
		//FINALIZA 
		if (test <= 0)
		{
			system("clear");
			printf("Cadastro finalizado!\n\n");
			break;
		}
		
		//CADASTRO DA DESCRIÇÃO
		printf("Digite a descrição do produto: ");
		scanf(" %[^\n]s", p[cont].desc);
		
		//CADASTRO DO PREÇO
		printf("Digite o valor do produto: ");
		scanf(" %f", &p[cont].val);
		
		//CADASTRO DA QUANTIDADE
		printf("Digite a quantidade do produto em estoque: ");
		scanf(" %d", &p[cont].est);
		
		system("clear");
		
		p[cont].cod = test;
		cont++;
	
		//FINALIZA 	
		if (cont==100)
		{
			system("clear");
			printf("Limite de cadastros excedido!");
			break;
		}
		
	} while (1);
	
	float fat = 0;
	int vendas = 0;
	char enter;
	
	//CARRINHO
	
	if (cont > 0)
	{
		printf("Pressione 'ENTER' para prosseguir para o carrinho.");
		getchar();
		while ((enter = getchar()) != '\n' && enter != EOF);
		system("clear");
		
		do
		{
			
			float total = 0; 
			int cont2 = 1;

			//VENDA DE PRODUTOS
			do
			{
				
				//VENDA DO PRODUTO POR CÓDIGO
				int test;
				printf("----CARRINHO DE COMPRAS----\n\n");
				printf("Digite o código do produto %d\n", cont2);
				printf("0 - Finalizar carrinho. ");
				scanf(" %d", &test);
				
				//FINALIZA 
				if (test <= 0)
				{
					system("clear");
					printf("Carrinho finalizado!\n\n");
					break;
				}
					
				//BUSCA DO CÓDIGO
				int flag, maior = cont, menor = 0;
				
				do
				{
					flag = (maior + menor) / 2;
					
					if (test == p[flag].cod)
					{
						printf("\nProduto %d\n", cont2);
						printf("Código: %d\n", p[flag].cod);
						printf("Descrição: %s\n", p[flag].desc);
						printf("Valor: R$%.2f\n", p[flag].val);
						printf("Quantidade: %d\n\n", p[flag].est);
						//ATUALIZAÇÃO DE ESTOQUE E VALOR A PAGAR
						
						do
						{
							int quant;
							printf("Digite a quantidade desejada: ");
							scanf(" %d", &quant);
							system("clear");
							
							if (p[flag].est < quant || quant < 0)
							{
								system("clear");
								printf("Quandidade digitada indisponível!\n");
								printf("Tente novamente...\n\n");
								printf("Produto %d\n", cont2);
								printf("Código: %d\n", p[flag].cod);
								printf("Descrição: %s\n", p[flag].desc);
								printf("Valor: R$%.2f\n", p[flag].val);
								printf("Quantidade: %d\n\n", p[flag].est);
								continue;
							}
							else if (p[flag].est >= quant)
							{	
								p[flag].est = p[flag].est - quant;
								total += quant * p[flag].val;
								if (quant > 0)
									vendas++;
								break;
							}
								
						} while (1);
						
						break;
					}
					
					else if (flag == 0 || flag == cont)
					{
						system("clear");
						printf("O código informado não existe!\n");
						printf("Tente novamente...\n");
						printf("Digite o código do produto %d\n", cont2);
						printf("0 - Finalizar carrinho. ");
						scanf(" %d", &test);
						maior = cont;
						menor = 0;
						continue;
					}
						
					else if (test < p[flag].cod)
						maior = flag - 1;
						
					else if (test > p[flag].cod)
						menor = flag + 1;
					
				} while (1);
				
				//FINALIZA 
				if (test <= 0)
				{
					system("clear");
					printf("\nCarrinho finalizado!\n\n");
					break;
				}
				cont2++;
				
			} while (1);
			
			//TOTAL A SER PAGO E TROCO
			float pag;
		
			do
			{
			
				printf("Total a ser pago: R$%.2f\n", total);
				if (total > 0)
				{
					printf("Digite o valor recebido: ");
					scanf(" %f", &pag);
					if (pag < total)
					{
						system("clear");
						printf("Valor insuficiente para concluir pagamento!\n");
						printf("Tente Novamente...\n");
					}
					else
						break;
				}
	
			} while (1);
			
			printf("Troco: R$%.2f\n", pag - total);		
			fat += total;
			int op;
			
			do
			{
				printf("\nSeleciona uma das duas opções:\n");
				printf("1 - Novo carrinho.\n");
				printf("2 - Finalizar carrinho\n");
				scanf(" %d", &op);	
				
				if (op < 1 || op > 2)
				{
					printf("O número digitado não existe!/n");
					printf("Tente Novamente.../n/n");
				}
				else
					break;
					
			} while (1);
			
			system("clear");
			
			if (op == 2)
			{
				system("clear");
				printf("Carrinho finalizado!\n\n");
				printf("Pressione 'ENTER' para prosseguir para o relatório.");
				getchar();
				while ((enter = getchar()) != '\n' && enter != EOF);
				system("clear");
				
				printf("----RELATÓRIO----\n\n");
				for (int i = 0; i < cont; i++)
				{
					printf("\nProduto %d:\n", i + 1);
					printf("Código: %d\n", p[i].cod);
					printf("Descrição: %s\n", p[i].desc);
					printf("Valor: R$%.2f\n", p[i].val);
					printf("Quantidade: %d\n", p[i].est);
				}
				printf("\n");
				printf("Vendas totais: %d\n", vendas);
				printf("Faturamento: R$%.2f\n", fat);
				break;
			}
			
		} while (1);
	}
	else 
		printf("Nenhum produto foi cadastrado!");
		
	return 0;
}
