//-Menu Inicial
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cliente.h"

clientes* pessoas = NULL;
automoveis* mobilidade = NULL;



void EscolhasClientes() {
	int mobilidadeescolhida, auxcod;
	float novosaldo = 0;
	
	auxcod = pessoas->id;
	//printf("%d\n", auxcod);

	if (mobilidade == NULL) {
		mobilidade = LerMobilidade();
	}


	printf("Bem vindo %s, seu saldo atual e de: %.2f\n", pessoas->nome, pessoas->saldo);
	printf("\n");
	printf("O que deseja fazer?\n");
	int escolha;
	printf("1- Alugar Mobilidade\n");
	printf("2- Adicionar Saldo\n");
	printf("3- Ver cidades disponiveis\n");
	printf("4- Exit\n");
	scanf("%d", &escolha);

	switch (escolha)
	{
	case 1:
		system("cls");
		ListarMobilidadeAluguel(mobilidade);
		printf("Digite o numero da mobilidade que deseja alugar: ");
		scanf("%d", &mobilidadeescolhida);
		system("cls");

		printf("Voce alugou a moblidade de ID: %d\n", mobilidadeescolhida);
		EscolhasClientes();
		break;
	case 2:
		system("cls");
		printf("Seu saldo atual e: %.2f euros\n", pessoas->saldo);
		printf("Quanto voce quer adicionar?\n");
		scanf("%f", &novosaldo);
		pessoas = AlterarSaldo(pessoas, auxcod,novosaldo);
		system("cls");
		EscolhasClientes();
		break;
	case 3:
	case 4:
		SalvarClientesFILE(pessoas);
		break;
	default:
		system("cls");
		printf("Warning! : Escolha um numero valido\n");
		EscolhasClientes();
		break;
	}
}
  
void MenuCliente() {

	int opcao, opcaologin;
	printf("1- Entrar\n");
	printf("2- Cadastre-se\n");
	printf("3- EXIT\n");
	/*printf("4- Ver Lista de Clientes");*/

	scanf_s("%d", &opcao);

	switch (opcao)
	{
	case 1:
		
		printf("Digite seu identificador para entrar: ");
		scanf_s("%d", &opcaologin);

		int valor = LoginCliente(pessoas, opcaologin);
		//printf("%d", valor);

		if (valor == 1) {
			system("cls");
			EscolhasClientes();
		}
		else {
			printf("Codigo Invalido\n");
		}

		break;
	case 2:  //Cadastrar Novo Cliente
		system("cls");//(Limpa Console)

		char name[50];
		char endereco[100];
		int age, fiscal;
		int cod = NumeroAleatorio();

		printf("O codigo do seu novo cliente e:%d\n", cod);
		printf("Ditige seu nome: ");
		getchar();
		fgets(name, 50, stdin);
		name[strcspn(name, "\n")] = '\0';
		printf("Digite sua idade: ");
		scanf_s("%d", &age);
		printf("Digite seu nif: ");
		scanf_s("%d", &fiscal);
		printf("Digite sua Morada: ");
		getchar();
		fgets(endereco, 100, stdin);
		endereco[strcspn(endereco, "\n")] = '\0';

		pessoas = NovoCliente(pessoas, cod, name, fiscal, age, endereco);

		system("cls");//(Limpa Console)

		MenuCliente();
		
		break;
	case 3:
		return 0;
		break;

	case 4:
		/*ListarClientes(pessoas);*/
		//SalvarClientesFILE(pessoas);
		break;
	default:
		system("cls");//(Limpa Console)
		printf("Escolha um numero valido!\n");
		MenuCliente();
		break;
	}
}

void MenuInicial() {
	pessoas = LerClientes();
	int escolha;
	printf("1- Cliente\n");
	printf("2- Gestor\n");
	printf("3- EXIT\n");

	scanf_s("%d", &escolha);

	switch (escolha)
	{
	case 1:
		system("cls");//(Limpa Console)
		MenuCliente();
		break;
	case 2:
		system("cls");//(Limpa Console)
		MenuGestor();

		break;
	case 3:
		break;

	default:
		system("cls");//(Limpa Console)
		printf("Escolha um numero valido!\n");
		MenuInicial();
		break;
	}
}
