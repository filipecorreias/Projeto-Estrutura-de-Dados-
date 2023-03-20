#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"

int NumeroAleatorio() {
	int num;

	//Gerando numero aleatorio pelo tempo atual
	srand(time(NULL));

	num = rand() % 9000 + 1000;
	return(num);
}


int LoginCliente(clientes* dados, int cod) {
	while (dados != NULL) {
		if (dados->id == cod) {
			return(1);
			break;
		}
		else {
			dados = dados->seguinte;
		}
	}
	return(0);
}


automoveis* NovaMobilidade(automoveis* mobilidade, int cod,char modelo[], float valor, float consumo) {
	automoveis* novo = malloc(sizeof(struct mobilidade));

	if (novo != NULL) {
		novo->id = cod;
		strcpy_s(novo->tipo, sizeof(novo->tipo), modelo);
		novo->carga = 100;
		novo->custo = valor;
		novo->autonomia = consumo;
		novo->seguinte = mobilidade;
		return(novo);
	}
	else {
		printf("Erro ao Alocar memoria.\n");
		return(mobilidade);
	}

}


gestor* NovoGestor(gestor* dados, int cod, char pessoa[],int fiscal) {
	gestor* novo = malloc(sizeof(struct gestao));

	if (novo != NULL) {
		novo->id = cod;
		strcpy_s(novo->nome, sizeof(novo->nome), pessoa);
		novo->nif = fiscal;
		novo->seguinte = dados;
		return(novo);
	}
	else {
		printf("Erro ao alocar memoria");
		return(dados);
	}
}


clientes* NovoCliente(clientes* dados, int cod, char pessoa[], int fiscal, int age, char local[]) {
	clientes* novo = malloc(sizeof(struct registo));

	if (novo != NULL) {
		novo->id = cod;
		strcpy_s(novo->nome,sizeof(novo->nome), pessoa);
		novo->nif = fiscal;
		novo->idade = age;
		strcpy_s(novo->morada,sizeof(novo->morada), local);
		novo->saldo = 0;
		novo->seguinte = dados;
		return(novo);
	}
	else {
		printf("Erro ao alocar memoria");
		return(dados);
	}
}

void ListarClientes(clientes* inicio) {
	while (inicio != NULL) {

		printf(" identificador:%d\n nome:%s\n idade:%d\n nif:%d\n morada:%s\n saldo:%.2f\n", inicio->id, inicio->nome, inicio->idade, inicio->nif, inicio->morada, inicio->saldo);

		inicio = inicio->seguinte;
	}
}
void SalvarClientesFILE(clientes* dados) {
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "clientes.txt", "w");

	if (err != 0) {
		printf("Erro ao abrir o arquivo. Codigo de erro: %d\n", err);
		exit(1);
	}

	clientes* aux = dados;
	ListarClientes(aux);
	while (aux != NULL) {
		fprintf(fp, "%d;%s;%d;%d;%.2f;%s\n", aux->id, aux->nome, aux->nif, aux->idade, aux->saldo, aux->morada);

		//fprintf(fp, "%d,", aux->mobilidade->id);
		aux = aux->seguinte;

	}
	fclose(fp);
}

	//ler clientes e colocar na lista encadeada
clientes* LerClientes() {
	FILE* fp = fopen("clientes.txt", "r");


	if (fp == NULL) {
		//printf("Erro ao abrir o arquivo. Codigo de erro: %d\n");
		//exit(1);
		/*printf("deu certo");*/
		exit(0);
	}

	int cod,fiscal,anos;
	float valor;
	char pessoa[50], lugar[100];
	clientes* aux = NULL;


	while (!feof(fp))
	{
		/*printf("entrou");*/
		fscanf(fp, "%d;%[^;];%d;%d;%f;%[^\n]\n", &cod, pessoa, &fiscal, &anos, &valor, lugar);
		//printf("%d", cod);
		//printf("%s", pessoa);
		//printf("%d", fiscal);
		//printf("%d", anos);
		//printf("%.2f", valor);
		//printf("%s", lugar);
		aux = NovoCliente(aux, cod, pessoa, fiscal, anos, lugar);
	}
	fclose(fp);
	
	return(aux);
}
