#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "dicio.h"

//Definindo uma estrutura de dados em lista
typedef struct lista {
	char nomeTarefa[100];
	char descricao[256];
	bool concluido;
	struct lista *prox;
} Lista;

//Criando uma lista vazia
Lista* lista_cria() {
	return NULL;
}

//Verificando se a lista tá vazia
bool lista_vazia(Lista* lst) {
	return (lst == NULL);
}

//Inserindo elementos dentro da lista
Lista * lista_insere(Lista* lst, char* tarefa, char* desc, bool conc) {
	Lista *novo = (Lista*) malloc (sizeof(Lista));
	strcpy(novo->nomeTarefa, tarefa);
	strcpy(novo->descricao, desc);
	novo->concluido = conc;
	novo->prox = lst;
	
	return novo;
}

//Fazendo busca de acordo com a solicitação do usuário
Lista* lista_busca(Lista* lst, int dado) {
	Lista *a;
	int i=1;
	for(a=lst; a != NULL; a=a->prox) {
		if(i==dado) return a;
		i++;
	}
	return NULL;
}

//Editando o elemento especifico que o usuário escolheu
Lista* lista_editarTarefa(Lista* lst, Lista* dado, char* tarefa, char* desc) {
	Lista *aux;
	for(aux = lst; aux != NULL; aux = aux->prox) {
		if(aux == dado) {
			strcpy(aux->nomeTarefa, tarefa);
			strcpy(aux->descricao, desc);
		}
	}
	
	return lst;
}

//Removendo o item da lista de acordo com a busca
Lista* lista_remove(Lista* lst, Lista* dado) {	
	Lista *atual = lst;
	Lista *ant = NULL;
	
	if(dado == NULL) {
		return lst;
	}
	
	//Para o caso do elemento a ser removido for o primeiro
	if(atual == dado) {
		lst = atual->prox;
		free(atual);
		return lst;
	}
	
	//Procurando o elemento na lista
	while(atual != NULL && atual != dado) {
		ant = atual;
		atual = atual->prox;
	}
	
	ant->prox = atual->prox;
	free(atual);
	return lst;
}

//Marcar uma tarefa como concluido
Lista* lista_marcarConcluido(Lista* lst, Lista* dado) {
	Lista *aux;
	for(aux=lst; aux != NULL; aux = aux->prox) {
		if(aux == dado) {
			aux->concluido = true;
		}
	}
	
	return lst;
}

//Invertendo a ordem da lista
Lista* lista_inversa(Lista* lst) {
	Lista *atual = lst;
	Lista *ant = NULL;
	Lista *pro = NULL;
	
	while(atual != NULL) {
		pro = atual->prox;
		atual->prox = ant;
		ant = atual;
		atual = pro;
	}
	
	return ant;
}

//Escrever um arquivo em txt com todas as tarefas
void lista_escreverArquivo(Lista* lst, FILE *arquivo) {
	Lista *inverso = lista_inversa(lst);
	Lista *aux;
	
	for(aux = inverso; aux != NULL; aux = aux->prox) {
		fprintf(arquivo, "T: %s\n", aux->nomeTarefa);
		fprintf(arquivo, "D: %s\n", aux->descricao);
		fprintf(arquivo, "C: %d\n\n", aux->concluido);
	}
}

//Caso tenha um arquivo txt salvo, as tarefas serão inseridas usando lista_insere
Lista* lista_preencherSalvamento(Lista* lst, FILE *arquivo) {
	arquivo = fopen("tarefas.txt", "r");
	
	char linha[258], tarefa[256], desc[256];
	int concluido;
	
	//Lendo o conteúdo
	while(fgets(linha, sizeof(linha), arquivo) != NULL) {
		//Tarefas
		if(strncmp(linha, "T: ", 3) == 0) {
			sscanf(linha, "T: %[^\n]", tarefa);
		}
		
		//Descrições
		if(strncmp(linha, "D: ", 3) == 0) {
			sscanf(linha, "D: %[^\n]", desc);
		}
		
		//Status de concluídos (verdadeiro ou falso)
		if(strncmp(linha, "C: ", 3) == 0) {
			sscanf(linha, "C: %d", &concluido);
			lst = lista_insere(lst, tarefa, desc, concluido);
		}
	}
	
	//Fechando o arquivo
	fclose(arquivo);
	
	return lst;
}

//Mostrando todas as estatisticas
void mostrarEstatisticas(Lista* lst) {
	int qtdTarefas=0, qtdNaoConc=0, qtdSimConc=0;
	Lista *aux;
	for(aux=lst; aux != NULL; aux = aux->prox) {
		if(aux->concluido == true) {
			qtdSimConc++;
		}
		else if(aux->concluido == false) {
			qtdNaoConc++;
		}
		qtdTarefas++;
 	}
 	
 	float pctSimConc = 0.0, pctNaoConc = 0.0;
 	
 	if(qtdTarefas > 0) {
 		pctSimConc = (float)qtdSimConc / qtdTarefas;
 		pctNaoConc = (float)qtdNaoConc / qtdTarefas;
	}
	
	printf("Quantidade de tarefas: %d\n", qtdTarefas);
	printf("Qtd. Tarefas Concluídas: %d\n", qtdSimConc);
	printf("Qtd. Tarefas não Concluídas: %d\n", qtdNaoConc);
	printf("Porc. Tarefas Concluídas: %.2f%%\n", pctSimConc*100);
	printf("Porc. Tarefas não Concluídas: %.2f%%\n", pctNaoConc*100);
}

//Mostrando a lista de tarefas não concluídas para o usuário
void lista_tarefasNaoConcluidas(Lista* lst) {
	Lista *aux;
	for(aux=lst; aux != NULL; aux = aux->prox) {
		if(aux->concluido == false) {
			printf("Tarefa: %s\n", aux->nomeTarefa);
			printf("Descrição: %s\n", aux->descricao);
			printf("\n");
		}
	}
}

//Mostrando a lista de tarefas já concluídas para o usuário
void lista_tarefasConcluidas(Lista* lst) {
	Lista *aux;
	for(aux=lst; aux != NULL; aux = aux->prox) {
		if(aux->concluido == true) {
			printf("Tarefa: %s\n", aux->nomeTarefa);
			printf("Descrição: %s\n", aux->descricao);
			printf("\n");
		}
	}
}

//Mostrando um menu com todas as tarefas de acordo com a requisição
int mostrar_menuTarefas(Lista* lst, int tipo) {
	if(lista_vazia(lst)) {
		printf("[AVISO] Não conseguimos achar tarefas, a lista está vazia!!!\n\n");
	}
	
	Lista *a;
	int i=1;
	
	switch(tipo) {
		case 1: //Mostrar todas as tarefas
			for(a = lst; a != NULL; a = a->prox) {
				printf("[%d] %s: %s\n", i, a->nomeTarefa, a->descricao);
				i++;
			}
			printf("[%d] Voltar\n", i);
			break;
		case 2: //Mostrar somente tarefas não concluídas
			for(a = lst; a != NULL; a = a->prox) {
				if(a->concluido == false) {
					printf("[%d] %s: %s\n", i, a->nomeTarefa, a->descricao);
					i++;
				}
			}
			printf("[%d] Voltar\n", i);
			break;
		case 3: //Mostrar somente tarefas concluídas
			for(a = lst; a != NULL; a = a->prox) {
				if(a->concluido == true) {
					printf("[%d] %s: %s\n", i, a->nomeTarefa, a->descricao);
					i++;
				}
			}
			printf("[%d] Voltar\n", i);
			break;
	}
	
	return i;
}

//Mostrando o menu principal para o usuário
void mostrar_menuPrincipal() {
	system("cls");
	printf("----- MENU PRINCIPAL -----");
	printf("\n\n[1] Adicionar Tarefas");
	printf("\n[2] Editar Tarefas");
	printf("\n[3] Remover Tarefas");
	printf("\n[4] Ver Tarefas não Concluídas");
	printf("\n[5] Ver Tarefas já Concluídas");
	printf("\n[6] Marcar Tarefas como Concluídas");
	printf("\n[7] Salvar em arquivo");
	printf("\n[8] Estatisticas de Tarefas");
	printf("\n[9] Sair");
}

int main() {
	//Definindo a localidade para Português do Brasil
	setlocale(LC_ALL, "Portuguese_Brazil");
	
	//Variáveis que vão manipular todo o menu principal e seus casos
	int opMenu, opCaso, result, i;
	Lista *busca; 
	FILE *arquivo;
	
	//Fazendo uma lista vazia
	Lista *lista = lista_cria();
	
	//Verificando a existencia do arquivo
	lista = lista_preencherSalvamento(lista, arquivo);
	
	//Montando a estrutura do menu que vai permitir que o usuário insira somente valores de 1 a 9
	do {
		//Visualização do menu
		mostrar_menuPrincipal();
		
		//Usuário vai inserir o número
		printf("\n\nDigite o número correspondente:\n--> ");
		result = scanf("%d", &opMenu);
		
		//Tratamento de erros adaptado pra linguagem C
		if(result != 1 || (opMenu < 1 || opMenu > 9)) {
			while(getchar() != '\n'); //Para limpar o buffer
			continue;
		}
		
		//Variáveis
		char desc[256], titulo[100];
		
		//Limpando a tela
		system("cls");
		
		//Conectando os números as funções e executando o pedido do usuário
		switch(opMenu) {
			case 1: //Adicionar Tarefas
				while(getchar() != '\n'); //Para limpar o buffer
				
				//Mostrando titulo do caso 1
				printf("----- INSERIR TAREFA -----\n\n");
				
				//Usuário vai digitar tarefa e arrumaremos o texto pra indicar os caracteres corretos
				printf("Digite o nome da tarefa:\n--> ");
				fgets(titulo, sizeof(titulo), stdin);
				arrumarTexto(titulo);
				
				//Usuário vai digitar descrição e arrumaremos o texto pra indicar os caracteres corretos
				printf("\nDigite a Digite a descrição desta tarefa:\n--> ");
				fgets(desc, sizeof(desc), stdin);
				arrumarTexto(desc);
				
				//Esses dados serão inseridos na lista
				lista = lista_insere(lista, titulo, desc, false);
				printf("\nDados inseridos com sucesso!!!");
				break;
			case 2: //Editar Tarefas
				while(getchar() != '\n'); //Para limpar o buffer
				
				do {
					//Limpando a tela
					system("cls");
					
					//Mostrando titulo do caso 2
					printf("----- EDITAR TAREFA -----\n\n");
					
					//Visualização do menu de lista de tarefas
					i = mostrar_menuTarefas(lista, 2);
					
					//Usuário vai inserir o número
					printf("\n\nDigite o número correspondente:\n--> ");
					result = scanf("%d", &opCaso);
					
					//Tratamento de erros adaptado pra linguagem C
					if(result != 1) {
						while(getchar() != '\n'); //Para limpar o buffer
						continue;
					}
				} while(opCaso > i || opCaso < 1);
				
				if(opCaso == i) {
					printf("\nRetornando para a tela inicial...");
					break;
				}
				else {
					busca = lista_busca(lista, opCaso);

					while(getchar() != '\n'); //Para limpar o buffer

					//Usuário vai digitar tarefa e arrumaremos o texto pra indicar os caracteres corretos
					printf("Digite o nome da tarefa: (Deixe vazio caso não queira editar essa parte)\n--> ");
					fgets(titulo, sizeof(titulo), stdin);
					arrumarTexto(titulo);
					
					//Verificando se o usuário não escreveu nada
					if(titulo[0] == '\0' || verificarEspacos(titulo)) {
						strcpy(titulo, busca->nomeTarefa);
					}
					
					//Usuário vai digitar descrição e arrumaremos o texto pra indicar os caracteres corretos
					printf("\nDigite a Digite a descrição desta tarefa: (Deixe vazio caso não queira editar essa parte)\n--> ");
					fgets(desc, sizeof(desc), stdin);
					arrumarTexto(desc);
					
					//Verificando se o usuário não escreveu nada
					if(desc[0] == '\0' || verificarEspacos(titulo)) {
						strcpy(desc, busca->descricao);
					}

					lista = lista_editarTarefa(lista, busca, titulo, desc);
					printf("\nTarefa editada com sucesso!!!");
				}
				break;
			case 3: //Remover Tarefas
				while(getchar() != '\n'); //Para limpar o buffer
				
				//Mostrando titulo do caso 3
				printf("----- REMOVER TAREFA -----\n\n");
				
				do {
					//Visualização do menu de lista de tarefas
					i = mostrar_menuTarefas(lista, 1);
					
					//Usuário vai inserir o número
					printf("\n\nDigite o número correspondente:\n--> ");
					result = scanf("%d", &opCaso);
					
					//Tratamento de erros adaptado pra linguagem C
					if(result != 1) {
						while(getchar() != '\n'); //Para limpar o buffer
						continue;
					}
				} while(opCaso > i || opCaso < 1);
				
				if(opCaso == i) {
					printf("\nRetornando para a tela inicial...");
					break;
				}
				else {
					busca = lista_busca(lista, opCaso);
					lista = lista_remove(lista, busca);
					printf("\nTarefa removida com sucesso!!!");
				}
				break;
			case 4: //Ver Tarefas não Concluídas
				//Mostrando titulo do caso 4
				printf("----- TAREFAS NÃO CONCLUÍDAS -----\n\n");
				
				if(lista_vazia(lista)) {
					printf("Você não tem nenhuma tarefa registrada!!!\n");
				}
				else {
					//Listando tarefas não concluídas
					lista_tarefasNaoConcluidas(lista);
				}
				break;
			case 5: //Ver Tarefas já Concluídas
				//Mostrando titulo do caso 5
				printf("----- TAREFAS JÁ CONCLUÍDAS -----\n\n");
				
				if(lista_vazia(lista)) {
					printf("Você não tem nenhuma tarefa registrada!!!\n");
				}
				else {
					//Listando tarefas já concluídas
					lista_tarefasConcluidas(lista);
				}
				break;
			case 6: //Marcar Tarefas como Concluídas
				while(getchar() != '\n'); //Para limpar o buffer
				
				//Mostrando titulo do caso 3
				printf("----- MARCAR CONCLUÍDO NUMA TAREFA -----\n\n");
				
				do {
					//Visualização do menu de lista de tarefas
					i = mostrar_menuTarefas(lista, 2);
					
					//Usuário vai inserir o número
					printf("\n\nDigite o número correspondente:\n--> ");
					result = scanf("%d", &opCaso);
					
					//Tratamento de erros adaptado pra linguagem C
					if(result != 1) {
						while(getchar() != '\n'); //Para limpar o buffer
						continue;
					}
				} while(opCaso > i || opCaso < 1);
				
				if(opCaso == i) {
					printf("\nRetornando para a tela inicial...");
					break;
				}
				else {
					busca = lista_busca(lista, opCaso);
					lista = lista_marcarConcluido(lista, busca);
					printf("\nTarefa marcada como concluída com sucesso!!!");
				}
				break;
			case 7: //Salvar em arquivo
				//Mostrando titulo do caso 7
				printf("----- SALVANDO EM UM ARQUIVO -----\n\n");
				
				//Abrindo ou criando arquivo no modo append
				arquivo = fopen("tarefas.txt", "w");
				
				//Função que vai escrever as tarefas no arquivo
				lista_escreverArquivo(lista, arquivo);
				
				//Fechando o arquivo
				fclose(arquivo);
				
				//Confirmando o salvamento
				printf("Arquivo tarefas.txt foi salvo com sucesso!!!\n");
				break;
			case 8: //Estatisticas de Tarefas
				//Mostrando titulo do caso 8
				printf("----- ESTATISTICAS DE TAREFAS -----\n\n");
				
				//Mostrando todas as estatisticas pro usuário
				mostrarEstatisticas(lista);
				break;
			case 9: //Sair
				printf("Saindo do programa...\n");
				break;
		}
		
		printf("\n");
		system("pause");
	} while(opMenu != 9);
}
