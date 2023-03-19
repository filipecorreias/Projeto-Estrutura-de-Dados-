#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cliente.h"

void CadastrarMobilidade() {
	automoveis* mobilidades = NULL;
	char name[50];
	float autonomia, custo;
	int cod = NumeroAleatorio();

	printf("O Codigo da nova mobilidade e:%d\n", cod);
	printf("Digite o nome da mobilidade:\n");
	getchar();
	fgets(name, 50, stdin);
	printf("Digite quanto de bateria e gasto por minuto de utilizacao do dispositivo\n");
	scanf_s("%f", &autonomia);
	printf("Digite o valor, por minuto, de utilizacao do dispositivo\n");
	scanf_s("%f", &custo);

	NovaMobilidade(mobilidades,cod, name, custo, autonomia);

}

void CadastrarGestor() {
	gestor* pessoas = NULL;

	char name[50];
	int fiscal;
	int cod = NumeroAleatorio();

	printf("O codigo no novo gestor e: %d\n", cod);
	printf("Ditige seu nome:\n");
	getchar();
	fgets(name, 50, stdin);
	printf("Digite seu nif:\n");
	scanf_s("%d", &fiscal);


	pessoas = NovoGestor(pessoas,cod, name, fiscal);
}
void MenuGestor() {
	int escolha;

	printf("1- Adicionar um novo gestor\n");
	printf("2- Adicionar uma nova mobilidade\n");
	printf("3- Remover uma mobilidade\n");
	printf("4- EXIT\n");

	scanf_s("%d", &escolha);
	switch (escolha)
	{
	case 1:
		system("cls");
		CadastrarGestor();
		system("cls");
		MenuGestor();
		break;
	case 2:
		system("cls");
		CadastrarMobilidade();
		system("cls");
		MenuGestor();
		break;
	case 3:

		break;
	case 4:
		return 0;
		break;
	default:
		system("cls");
		printf("Escolha um numero valido\n");
		MenuGestor();
		break;
	}
}