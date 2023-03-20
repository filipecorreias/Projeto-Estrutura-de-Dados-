#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct mobilidade{
	int id;
	char tipo[50];
	float carga;
	float custo;
	float autonomia;
	struct mobilidade* seguinte;
}automoveis;

typedef struct gestao{
	int id;
	char nome[50];
	int nif;
	struct gestao* seguinte;
}gestor;

typedef struct {
	int id;
	char nome[50];
}cidade;

typedef struct registo{
	int id;
	char nome[50];
	int nif;
	int idade;
	char morada[100];
	float saldo;
	automoveis* mobilidade;
	cidade localidade;
	struct registo *seguinte;
}clientes;



//void MenuInicial();

//Adicionar novo Cliente
clientes* NovoCliente(clientes* dados, int cod, char pessoa[], int fiscal, int age, char local[]);


//Listar Clientes Existentes
void ListarClientes(clientes* inicio);

//Adicionar novo Gestor
gestor* NovoGestor(gestor* dados, int cod, char pessoa[], int fiscal);

//Adicionar Nova Mobilidade
automoveis* NovaMobilidade(automoveis* mobilidade, int cod, char modelo[], float valor, float consumo);

//GERA UM NUMERO ALEATORIO PARA OS IDs.
int NumeroAleatorio();

//Login do Cliente
int LoginCliente(clientes* dados, int cod);

//Salvar Clientes em arquivo txt
void SalvarClientesFILE(clientes* dados);

//Leitura de Clientes
clientes* LerClientes();
