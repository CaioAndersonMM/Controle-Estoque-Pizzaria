#pragma once
#include <fstream> //file
using namespace std;

struct Produto {
    char nome[20];
    float preco;
    int quantidade;
};

void AdicionarNoEstoque(Produto *& vetor, int& qtdProdutos);

void ExcluirDoEstoque(Produto*& vetor, int& qtdProdutos);

void Listar(const Produto* vetor, const int& qtdProdutos);

void Pedir(Produto*& vetor, const int qtdProdutos);

bool compareStrings(char* nome1, char* nome2);