#include <iostream>
#include "pizzaria.h"

int main() {
	//setlocale(LC_ALL, "portuguese");
	system("chcp 1252");

	int num_expansoes = 0;

	//Come�o o programa lendo o arquivo bin�rio para coloca-lo dentro do vetor de estoque
	ifstream arqv;
	arqv.open("estoque.bin", ios::binary); //abro

	int contadorProduto = 0;
	int qtdProdutos = 0;

	Produto* vetor_estoque = new Produto[qtdProdutos]; //Inicializando

	if (arqv.good()) {//Se arquivo  est� em um estado v�lido
		//cout << "arqv existe" << endl << endl;
		//Calcula o tamanho do arquivo em bytes
		arqv.seekg(0, ios::end); //coloca um ponteiro no final do arquivo para ver o tamanho, end = final
		int tamanho = arqv.tellg(); // obtendo o tamanho do arquivo com o ponteiro no final dele (em bytes)

		//Calcula o n�mero de produtos no arquivo com base no tamanho dele
		qtdProdutos = tamanho / sizeof(Produto); //Divide o tamanho do arquivo pelo tamanho de cada registro de Produto

		//Cria um vetor din�mico com o tamanho inicial igual ao n�mero de produtos no arquivo
		vetor_estoque = new Produto[qtdProdutos];

		//Retorna o ponteiro para o in�cio do arquivo
		arqv.seekg(0, ios::beg); //beg = inicio

		//Ler os dados do arquivo para o vetor din�mico
		arqv.read(reinterpret_cast<char*>(vetor_estoque), tamanho); //segundo argumento � o tamanho do arquivo
		/* Ou
			for (int i = 0; i < qtdProdutos; i++) {
				arqv.read((char*)&vetor_estoque[i], sizeof(Produto)); //segundo argumento � o tamanho de um produto
			}
		*/

		//arqv.read((char*)(vetor_estoque), tamanho);

		// fecha o arquivo
		arqv.close();

	} else {//Se n�o existir
		//cout << "Criando arquivo..." << endl; //No final

		vetor_estoque = new Produto[qtdProdutos]; //colocando ele vazio

		/*Isso deve ser feito no final do programa

		//Abre o arquivo para escrita
		ofstream arquivo_saida("estoque.bin", std::ios::binary);

		// escreve os dados do vetor din�mico vazio para o arquivo
		arquivo_saida.write(reinterpret_cast<char*>(vetor_estoque), 0);

		// fecha o arquivo
		arquivo_saida.close()
		*/
	}

	char seletor;
	int capacidade = qtdProdutos; //Capacidade inicial � a quantidade de produtos do estoque

	do {
		//cout << capacidade << " - qtdprodutos: " << qtdProdutos;
		cout << endl << "Sistema de Controle" << endl << "===================" << endl;
		cout << "(P)edir" << endl;
		cout << "(A)dicionar" << endl;
		cout << "(E)xcluir " << endl;
		cout << "(L)istar" << endl;
		cout << "(S)air" << endl;
		cout << "===================" << endl;
		cout << "Op��o: [" << " ]" << '\b' << '\b';

		cin >> seletor;

		switch (seletor) {
		case 'P':
		case 'p':
			cout << "Pedir" << endl << "-----" << endl;
			Pedir(vetor_estoque, qtdProdutos);
			break;

		case 'A':
		case 'a':

			if (qtdProdutos == capacidade) {// Se a quantidade de produtos do vetor de estoque for igual a capacidade dele � porque est� cheio!
				//cout << endl << "------------------------EXPANDIR";
				capacidade = capacidade + pow(2, num_expansoes);
				Produto* novo_vetor = new Produto[capacidade]; //Novo vetor dinamico tem a nova capacidade
				memcpy(novo_vetor, vetor_estoque, capacidade * sizeof(Produto)); //Copio os dados do vetor novo antigo para o vetor novo sem usar la�o de repeti��o
				delete[] vetor_estoque;
				vetor_estoque = novo_vetor;
				//Apago a memoria alocado para o vetor antigo e aponto para o vetor novo
				num_expansoes++;
			}

			cout << endl << "Adicionar" << endl << "---------" << endl;

			AdicionarNoEstoque(vetor_estoque, qtdProdutos);

			break;

		case 'E':
		case 'e':
			cout << endl << "Excluir" << endl << "---------" << endl;
			ExcluirDoEstoque(vetor_estoque, qtdProdutos);
			break;

		case 'L':
		case 'l':
			cout << endl << "Listagem" << endl << "--------" << endl;
			Listar(vetor_estoque, qtdProdutos);
			break;

		case 'S':
		case 's':

			break;

		default:
			cout << endl << "Foi digitada uma op��o inv�lida! " << endl;
			break;

		}

	} while (seletor != 'S' && seletor != 's');


	// Abre o arquivo em modo de escrita bin�ria
	ofstream arquivo_saida("estoque.bin", ios::out | ios::binary); //abre no modo de escrita bin�ria

	// Verifica se o arquivo foi aberto corretamente
	if (arquivo_saida.is_open()) {
		// Escreve o n�mero de produtos no arquivo

		//arquivo_saida.write(reinterpret_cast<char*>(vetor_estoque), qtdProdutos * sizeof(Produto));
		//arquivo_saida.write((char *)vetor_estoque, qtdProdutos * sizeof(Produto));
		for (int i = 0; i < qtdProdutos; i++) {
			arquivo_saida.write(reinterpret_cast<const char*>(&vetor_estoque[i]), sizeof(Produto));
		}
		arquivo_saida.close();
	}

	else {
		cout << "Erro ao abrir o arquivo!" << endl;
		exit(EXIT_FAILURE);
	}

	delete[] vetor_estoque;

	return 0;

}