#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

	// Estrutura de um Funcionario

struct funcionario {
	char nome[40];
	char funcao[40];
	int idade;
	float salario;
};

FILE *arquivo; // Arquivo que contem os registros

struct funcionario *registros; // Array com os registros

int tamanho = 0; // Tamanho do array

	// Funcao que ira mostrar o atual registro de Funcionarios

void visualizarFuncionarios(){
	for (int c = 0; c < tamanho; c++){
		printf("\nFuncionario: %d\n",c+1);
		registros[c].nome[0] = toupper(registros[c].nome[0]); // Passa a primeira letra do nome para Maiscula
		printf("Nome: %s\nFunção: %s\nIdade: %d\nSalário: R$%.2f\n",registros[c].nome,registros[c].funcao,registros[c].idade,
			registros[c].salario);
	}
}

	/* 
		Funcao para adicionar novos funcionarios
		Estamos utilizando o metodo de alocacao dinamica.
		1 - Vamos criar outro array do struct funcionario com o mesmo tamanho - variavel aux
		2 - Vamos copiar os funcionarios do array registros para o outro array
		3 - Vamos recriar o array registros com o seu tamanho original + 1
		4 - Vamos copiar os dados do array aux para o array registros realocado
		5 - Apos, preencher o array registros novamente, vamos adicionar o novo funcionario na ultima posicao
	 */

void adicionarFuncionario(char nome[40], char funcao[40], int idade, float salario){
	
	if(tamanho == 0){
		registros = (struct funcionario *) calloc(1,sizeof(struct funcionario));
		strcpy(registros[0].nome,nome);
		strcpy(registros[0].funcao,funcao);
		registros[0].idade = idade;
		registros[0].salario = salario;
	} else {
		struct funcionario *aux = (struct funcionario *) calloc(tamanho,sizeof(struct funcionario));
		for (int c = 0; c < tamanho; c++){
			strcpy(aux[c].nome,registros[c].nome);
			strcpy(aux[c].funcao,registros[c].funcao);
			aux[c].idade = registros[c].idade;
			aux[c].salario = registros[c].salario;
		}
		
		
		registros = (struct funcionario *) calloc(tamanho+1, sizeof(struct funcionario));
		
		for (int c = 0; c < tamanho; c++){
			registros[c] = aux[c];
		}
		
		strcpy(registros[tamanho].nome,nome);
		strcpy(registros[tamanho].funcao,funcao);
		registros[tamanho].idade = idade;
		registros[tamanho].salario = salario;
	}
	
	tamanho++;	
	
}

	/* Funcao que vai procurar pelo nome do Funcionario no array registro e retornar a posicao caso encontre o nome 
		ou -1 se nao encontrar		
	*/

int localizarFuncionario(char nome[40]){
	strlwr(nome);
	for (int c = 0; c < tamanho; c++){
		strlwr(registros[c].nome);
		if (strcmp(registros[c].nome,nome) == 0){
			return c;
		}
	}
	return -1;
}

	/* 
		Funcao que ira remover Funcionario do Registros
		1 - Vamos criar outro array do struct funcionario com o mesmo tamanho - variavel aux
		2 - Vamos copiar os funcionarios do array registros para o outro array
		3 - Vamos recriar o array registros com o seu tamanho original - 1
		4 - Vamos copiar os dados do array aux para o array registros realocado pulando a posicao do registro que sera deletado
		fazendo 
		
		OBS: Se o Funcionario nao for encontrado a Funcao ira retornar -1
	*/

int removerFuncionarios(char nome[40]){
	int posicao = localizarFuncionario(nome);
	if(posicao < 0){
		return -1;
	}
	struct funcionario *aux = (struct funcionario *) calloc(tamanho,sizeof(struct funcionario));
	
	for (int c = 0; c < tamanho; c++){
		strcpy(aux[c].nome,registros[c].nome);
		strcpy(aux[c].funcao,registros[c].funcao);
		aux[c].idade = registros[c].idade;
		aux[c].salario = registros[c].salario;
	}
	
	registros = (struct funcionario *) calloc(tamanho-1,sizeof(struct funcionario));
	
	int j = 0;
	
	for (int c = 0; c < tamanho; c++){
		if (posicao == c){
			continue;
		}
		strcpy(registros[j].nome,aux[c].nome);
		strcpy(registros[j].funcao,aux[c].funcao);
		registros[j].idade = aux[c].idade;
		registros[j].salario = aux[c].salario;
		j++;
	}
	
	tamanho = tamanho - 1;
	return 1;
	
}

	/*
		Funcao que ira ordenar a lista de Funcionarios
		1 - A variavel opcao representa por qual atributo nos queremos ordenar a lista(Nome, idade, Salario, respectivamente)
		2 - A variavel ordem representa a ordem a lista (Crescente ou Decrescente, Respectivamente) 
	*/

void ordenarFuncionarios(int opcao,int ordem){
	switch(opcao){
		case 1:{
			if(ordem == 1){
				for (int c = 0; c < tamanho -1; c++){
					for (int j = c + 1; j < tamanho; j++){
						strlwr(registros[c].nome);
						strlwr(registros[j].nome);
						if (strcmp(registros[c].nome,registros[j].nome) == 1){
							char aux[40];
							strcpy(aux,registros[c].nome);
							strcpy(registros[c].nome,registros[j].nome);
							strcpy(registros[j].nome,aux);
							
							char aux2[40];
							strcpy(aux,registros[c].funcao);
							strcpy(registros[c].funcao,registros[j].funcao);
							strcpy(registros[j].funcao,aux);
							
							int aux3;
							aux3 = registros[c].idade;
							registros[c].idade = registros[j].idade;
							registros[j].idade = aux3;
							
							float aux4;
							aux4 = registros[c].salario;
							registros[c].salario = registros[j].salario;
							registros[j].salario = aux4;
						}
					}
				}
			} else {
				for (int c = 0; c < tamanho -1; c++){
					for (int j = c + 1; j < tamanho; j++){
						strlwr(registros[c].nome);
						strlwr(registros[j].nome);
						if (strcmp(registros[c].nome,registros[j].nome) == -1){
							char aux[40];
							strcpy(aux,registros[c].nome);
							strcpy(registros[c].nome,registros[j].nome);
							strcpy(registros[j].nome,aux);
							
							char aux2[40];
							strcpy(aux,registros[c].funcao);
							strcpy(registros[c].funcao,registros[j].funcao);
							strcpy(registros[j].funcao,aux);
							
							int aux3;
							aux3 = registros[c].idade;
							registros[c].idade = registros[j].idade;
							registros[j].idade = aux3;
							
							float aux4;
							aux4 = registros[c].salario;
							registros[c].salario = registros[j].salario;
							registros[j].salario = aux4;
						}
					}
				}	
			}
			break;
		}
		case 2:{
			if(ordem == 1){
				for (int c = 0; c < tamanho -1; c++){
					for (int j = c + 1; j < tamanho; j++){
						strlwr(registros[c].nome);
						strlwr(registros[j].nome);
						if (registros[c].idade >= registros[j].idade){
							char aux[40];
							strcpy(aux,registros[c].nome);
							strcpy(registros[c].nome,registros[j].nome);
							strcpy(registros[j].nome,aux);
							
							char aux2[40];
							strcpy(aux,registros[c].funcao);
							strcpy(registros[c].funcao,registros[j].funcao);
							strcpy(registros[j].funcao,aux);
							
							int aux3;
							aux3 = registros[c].idade;
							registros[c].idade = registros[j].idade;
							registros[j].idade = aux3;
							
							float aux4;
							aux4 = registros[c].salario;
							registros[c].salario = registros[j].salario;
							registros[j].salario = aux4;
						}
					}
				}
			} else {
				for (int c = 0; c < tamanho -1; c++){
					for (int j = c + 1; j < tamanho; j++){
						strlwr(registros[c].nome);
						strlwr(registros[j].nome);
						if (registros[c].idade < registros[j].idade){
							char aux[40];
							strcpy(aux,registros[c].nome);
							strcpy(registros[c].nome,registros[j].nome);
							strcpy(registros[j].nome,aux);
							
							char aux2[40];
							strcpy(aux,registros[c].funcao);
							strcpy(registros[c].funcao,registros[j].funcao);
							strcpy(registros[j].funcao,aux);
							
							int aux3;
							aux3 = registros[c].idade;
							registros[c].idade = registros[j].idade;
							registros[j].idade = aux3;
							
							float aux4;
							aux4 = registros[c].salario;
							registros[c].salario = registros[j].salario;
							registros[j].salario = aux4;
						}
					}
				}	
			}
			break;
		}
		case 3:{
			if(ordem == 1){
				for (int c = 0; c < tamanho -1; c++){
					for (int j = c + 1; j < tamanho; j++){
						strlwr(registros[c].nome);
						strlwr(registros[j].nome);
						if (registros[c].salario >= registros[j].salario){
							char aux[40];
							strcpy(aux,registros[c].nome);
							strcpy(registros[c].nome,registros[j].nome);
							strcpy(registros[j].nome,aux);
							
							char aux2[40];
							strcpy(aux,registros[c].funcao);
							strcpy(registros[c].funcao,registros[j].funcao);
							strcpy(registros[j].funcao,aux);
							
							int aux3;
							aux3 = registros[c].idade;
							registros[c].idade = registros[j].idade;
							registros[j].idade = aux3;
							
							float aux4;
							aux4 = registros[c].salario;
							registros[c].salario = registros[j].salario;
							registros[j].salario = aux4;
						}
					}
				}
			} else {
				for (int c = 0; c < tamanho -1; c++){
					for (int j = c + 1; j < tamanho; j++){
						strlwr(registros[c].nome);
						strlwr(registros[j].nome);
						if (registros[c].salario < registros[j].salario){
							char aux[40];
							strcpy(aux,registros[c].nome);
							strcpy(registros[c].nome,registros[j].nome);
							strcpy(registros[j].nome,aux);
							
							char aux2[40];
							strcpy(aux,registros[c].funcao);
							strcpy(registros[c].funcao,registros[j].funcao);
							strcpy(registros[j].funcao,aux);
							
							int aux3;
							aux3 = registros[c].idade;
							registros[c].idade = registros[j].idade;
							registros[j].idade = aux3;
							
							float aux4;
							aux4 = registros[c].salario;
							registros[c].salario = registros[j].salario;
							registros[j].salario = aux4;
						}
					}
				}	
			}
			break;
		}
	}
}

				/*   INICIO DO METODO MAIN */

int main(){
	
	arquivo = fopen("registros.txt","r");
	
	if(arquivo == NULL){
		printf("\nErro no abertura do arquivo!\n");
		system("pause");
		exit(1);
	}
	
	setlocale(LC_ALL,"");
	
		/* Inicio da Leitura dosRegistros */
		
	int result = fscanf(arquivo,"%d",&tamanho); // Quantidade de Registros	
	
	if(result >= 0){
		registros = (struct funcionario *) calloc(tamanho,sizeof(struct funcionario));	
	
		if(tamanho > 0){
			for(int c = 0; c < tamanho; c++){
				char nome[40],funcao[40];
				int idade;
				float salario;
				int resultado = fscanf(arquivo,"%s %s %d %f",nome,funcao,&idade,&salario);
				
				if(resultado >= 0){
					strcpy(registros[c].nome,nome);
					strcpy(registros[c].funcao,funcao);
					registros[c].idade = idade;
					registros[c].salario = salario;
				}
							
			}
			
		}	
	}
	
	fclose(arquivo);
	
		/* Fim da Leitura dosRegistros */
		
		
	
	int opcao = 0;
	
		/* Inicio do While */
	
	while (opcao != 6){
		
		printf("\n==============================================================\n");
		printf("                   REGISTRO DE FUNCIONÁRIOS                   ");
		printf("\n==============================================================\n");
		
		printf("\n[1] Para Visualizar Funcionários\n");
		printf("\n[2] Para Adicionar Funcionário\n");
		printf("\n[3] Para Localizar Funcionário\n");
		printf("\n[4] Para Remover Funcionário\n");
		printf("\n[5] Para Ordenar Lista\n");
		printf("\n[6] Sair\n");
		
		printf("Informe uma opção: ");
		scanf("%d",&opcao);
		
			
				/* Inicio do SWITCH */
		
		
		switch(opcao){
			case 1: {
				system("cls");
				if(tamanho >= 1){
					printf("Lista de Funcionários Cadastrados:\n");
					visualizarFuncionarios();		
				} else{
					printf("\nSem Funcionários Cadastrados\n");
				}
				
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				char nome[40],funcao[40];
				int idade;
				float salario;
				
				printf("\nInforme o nome do Funcionário: ");
				scanf(" %s",nome);
				printf("\nInforme a função do Funcionário: ");
				scanf(" %s",funcao);
				printf("\nInforme a idade do Funcionário: ");
				scanf("%d",&idade);
				printf("\nInforme o salário do Funcionário: ");
				scanf("%f",&salario);
				
				adicionarFuncionario(nome,funcao,idade,salario);
				
				system("cls");
				
				printf("\nFuncionário adicionado com sucesso!\n");
				
				system("pause");
				
				system("cls");	
				
				break;
			} 
			case 3: {
				printf("\nInforme o nome do Funcionário: ");
				char nome[40];
				scanf("%s",nome);
				int resultado = localizarFuncionario(nome);
				system("cls");
				if (resultado >= 0){
					printf("\nFuncionario: %d\n",resultado+1);
					printf("Nome: %s\nFunção: %s\nIdade: %d\nSalário: R$%.2f\n",registros[resultado].nome,
						registros[resultado].funcao,registros[resultado].idade,registros[resultado].salario);
				} else {
					printf("\nFuncionário não encontrado\n");
				}
				system("pause");
				system("cls");
				break;
			}
			case 4: {
				printf("Informe o nome do Funcionário: ");
				char nome[40];
				scanf("%s",nome);
				int resultado = removerFuncionarios(nome);	
				system("cls");
				if(resultado >= 0){
					printf("\nFuncionário Removido Com sucesso!\n");
				} else {
					printf("\nFuncionário não encontrado!\n");
				}
				system("pause");
				system("cls");
				break;
			}
			
			case 5:{
				
				system("cls");
				printf("\n[1] Ordenar por Nome\n");
				printf("\n[2] Ordenar por Idade\n");
				printf("\n[3] Ordernar por Salário\n");
				printf("\n[4] Cancelar\n");
			
				printf("\nInforme uma opção: ");
				int opcao;
				scanf("%d",&opcao);
				system("cls");
				
				if(opcao != 4){
					printf("\n[1] Ordem Crescente\n");
					printf("\n[2] Ordem Decrescente\n");
					printf("\n[3] Cancelar\n");
					
					printf("\nInforme a ordem: ");
					int ordem;
					scanf("%d",&ordem);
					
					if(opcao != 4 && ordem != 3) {
						ordenarFuncionarios(opcao,ordem);
						system("cls");
						printf("\nLista ordenada com sucesso!\n");
						system("pause");
						
					}	
					
				}
				system("cls");
				break;
			}
			
			case 6: {  // Gravacao dos Registros no arquivo registros.txt
				printf("\nSaindo...\n");
				
				arquivo = fopen("registros.txt","w");
				
				fprintf(arquivo,"%d\n",tamanho);
				for(int c = 0; c < tamanho; c++){
					fprintf(arquivo,"%s %s %d %.2f\n",registros[c].nome,registros[c].funcao,registros[c].idade,registros[c].salario);	
				}
				fclose(arquivo);
				break;
			}
			
			default: printf("\nOpção Inválida!\n");
			
			
		}
		
		/* FIM do Switch */
		
	}
	
		/* FIM do While */

	
	system("pause");
	return 0;
}
