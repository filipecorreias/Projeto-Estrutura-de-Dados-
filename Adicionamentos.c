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
		printf("\n");
		inicio = inicio->seguinte;
	}
}

clientes* AlterarSaldo(clientes* dados,int cod, float novosaldo) {
	while (dados != NULL) {
		//printf("entrou no while");
		if (dados->id == cod) {
			//printf("entrou para editar saldo");
			dados->saldo = dados->saldo + novosaldo;
			return(dados);
		}
		else {
			dados = dados->seguinte;
		}
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
	//ListarClientes(aux);
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

//---------------------FUNÇÕES PARA MOBILIDADE---------------------

//NOVA MOBILIDADE
automoveis* NovaMobilidade(automoveis* mobilidades, int cod, char modelo[], float valor, float consumo) {
	automoveis* novo = malloc(sizeof(struct mobilidade));

	if (novo != NULL) {
		//printf("Entrou no codigo de salvar");
		novo->id = cod;
		strcpy_s(novo->tipo, sizeof(novo->tipo), modelo);
		novo->carga = 100;
		novo->custo = valor;
		novo->autonomia = consumo;
		novo->seguinte = mobilidades;
		return(novo);
	}
	else {
		printf("Erro ao Alocar memoria.\n");
		return(mobilidades);
	}

}


//Salvando as Mobilidades Criada pelo gestor em um arquivo txt
void SalvarMobilidadesFILE(automoveis* dados) {
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "mobilidades.txt", "w");

	if (err != 0) {
		printf("Erro ao abrir o arquivo. Codigo de erro: %d\n", err);
		exit(1);
	}

	automoveis* aux = dados;
	while (aux != NULL) {
		fprintf(fp, "%d;%.2f;%.2f;%.2f;%s\n", aux->id, aux->carga, aux->custo, aux->autonomia, aux->tipo);

		aux = aux->seguinte;

	}
	fclose(fp);
}

void ListarMobilidades(automoveis* inicio) {
	while (inicio != NULL) {

		printf(" identificador:%d\n nome:%s\n carga:%.2f\n custo:%.2f\n autonomia:%.2f\n", inicio->id, inicio->tipo, inicio->carga, inicio->custo, inicio->autonomia);
		printf("\n");
		inicio = inicio->seguinte;
	}
}
void ListarMobilidadeAluguel(automoveis* inicio) {
	while (inicio != NULL) {

		printf(" ID: %d\n NOME: %s\n CARGA DISPONIVEL: %.2f\n Valor: %.2f euros por minuto\n Gasto Energenico de %.2f por minuto\n", inicio->id, inicio->tipo, inicio->carga, inicio->custo, inicio->autonomia);
		printf("\n");
		inicio = inicio->seguinte;
	}
}

void ListarMobilidadeAltera(automoveis* dados, int cod) {
	while (dados != NULL) {
		if (dados->id == cod) {
			printf(" ID: %d\n NOME: %s\n CARGA DISPONIVEL: %.2f\n Valor: %.2f euros por minuto\n Gasto Energenico de %.2f por minuto\n", dados->id, dados->tipo, dados->carga, dados->custo, dados->autonomia);
			break;
		}
		else {
			dados = dados->seguinte;
		}
	}
}
//RemoverMobilidade
automoveis* RemoverMobilidade(automoveis* dados, int cod) {
	automoveis* anterior = dados, * atual = dados, * aux;

	if (atual == NULL) return(NULL);
	else if (atual->id == cod) {
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else {
		while ((atual != NULL) && (atual->id != cod))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(dados);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			return(dados);
		}
	}
}

//Ler Mobilidade
automoveis* LerMobilidade() {
	FILE* fp = fopen("mobilidades.txt", "r");


	if (fp == NULL) {
		//printf("Erro ao abrir o arquivo. Codigo de erro: %d\n");
		//exit(1);
		/*printf("deu certo");*/
		exit(0);
	}

	int cod;
	float valor,carga,autonomia;
	char nome[50];
	automoveis* aux = NULL;


	while (!feof(fp))
	{
		/*printf("entrou");*/
		fscanf(fp, "%d;%f;%f;%f;%[^\n]\n", &cod, &carga, &valor, &autonomia , nome);
		//printf("%d", cod);
		//printf("%s", pessoa);
		//printf("%d", fiscal);
		//printf("%d", anos);
		//printf("%.2f", valor);
		//printf("%s", lugar);
		aux = NovaMobilidade(aux, cod, nome, valor, autonomia);
	}
	fclose(fp);

	return(aux);
}

automoveis* AlterarMobilidade(automoveis* mobilidade, int cod, float valor, float consumo) {
	//char nome[50];
	//strcpy(nome, model);
	while (mobilidade != NULL) {
		//printf("entrou no while");
		if (mobilidade->id == cod) {
			/*strcpy(mobilidade->tipo, nome);*/
			mobilidade->custo = valor;
			mobilidade->autonomia = consumo;
			/*mobilidade->carga = cargaatual;*/
			return(mobilidade);
		}
		else {
			mobilidade = mobilidade->seguinte;
		}
	}

}


