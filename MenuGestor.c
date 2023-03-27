#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cliente.h"

gestor* gestores = NULL;
automoveis* mobilidades = NULL;
clientes* cliente = NULL;

void DesejaAlterar() {
	int desejo;
	printf("Deseja alterar esse campo?\n");
	printf("1- Sim\n");
	printf("0- Nao\n");

	scanf("%d", &desejo);
	return(desejo);
}
void EditarMobilidade(int cod) {
	char nome[50];
	float carga = 0, valor = 0, autonomia = 0;
	//printf("Digite o novo nome: ");
	//scanf("%s", nome);
	printf("Digite o novo valor: ");
	scanf("%f", &valor);
	//printf("Digite a nova carga: ");
	//scanf("%f", &carga);
	printf("Digite a nova autonomia: ");
	scanf("%f", &autonomia);

	AlterarMobilidade(mobilidades, cod, valor, autonomia);
	system("cls");

}

void CadastrarMobilidade() {
	
	char name[50];
	float autonomia, custo;
	int cod = NumeroAleatorio();

	printf("O Codigo da nova mobilidade e:%d\n", cod);
	printf("Digite o nome da mobilidade:\n");
	getchar();
	fgets(name, 50, stdin);
	name[strcspn(name, "\n")] = '\0';
	printf("Digite quanto de bateria e gasto por minuto de utilizacao do dispositivo\n");
	scanf_s("%f", &autonomia);
	printf("Digite o valor, por minuto, de utilizacao do dispositivo\n");
	scanf_s("%f", &custo);

	mobilidades = NovaMobilidade(mobilidades,cod, name, custo, autonomia);
	

}

void CadastrarGestor() {
	

	char name[50];
	int fiscal;
	int cod = NumeroAleatorio();

	printf("O codigo no novo gestor e: %d\n", cod);
	printf("Ditige seu nome:\n");
	getchar();
	fgets(name, 50, stdin);
	printf("Digite seu nif:\n");
	scanf_s("%d", &fiscal);


	gestores = NovoGestor(gestores,cod, name, fiscal);
}
void MenuGestor() {
	int aux;
	int mobilidadeexlcuir, mobilidadeeditar;
	if (mobilidades == NULL) {
		mobilidades = LerMobilidade();
	}
	if (cliente == NULL) {
		cliente = LerClientes();
	}
	
	int escolha;

	printf("1- Adicionar um novo gestor\n");
	printf("2- Adicionar uma nova mobilidade\n");
	printf("3- Ver todas as mobilidades disponiveis\n");
	printf("4- Editar mobilidade\n");
	printf("5- Remover uma mobilidade\n");
	printf("6- Ver clientes cadastrados\n");
	printf("7- EXIT\n");

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
		system("cls");
		ListarMobilidades(mobilidades);
		printf("Digite 1 para retornar: ");
		scanf("%d", &aux);
		system("cls");
		MenuGestor();
		break;
	case 4:
		system("cls");
		ListarMobilidades(mobilidades);
		printf("Digite o codigo da mobilidade que deseja editar: ");
		scanf("%d", &mobilidadeeditar);
		system("cls");
		ListarMobilidadeAltera(mobilidades, mobilidadeeditar);
		EditarMobilidade(mobilidadeeditar);
		MenuGestor();
		break;
	case 5:
		system("cls");
		ListarMobilidades(mobilidades);
		printf("Escolha o codigo da mobilidade  que voce quer excluir: ");
		scanf("%d", &mobilidadeexlcuir);
		mobilidades = RemoverMobilidade(mobilidades, mobilidadeexlcuir);
		system("cls");
		MenuGestor();
		break;
	case 6:
		system("cls");
		ListarClientes(cliente);
		printf("Digite 1 para retornar: ");
		scanf("%d", &aux);
		system("cls");
		MenuGestor();
		break;
	case 7:
		
		SalvarMobilidadesFILE(mobilidades);
		
		break;
	default:
		system("cls");
		printf("Escolha um numero valido\n");
		MenuGestor();
		break;
	}
}
