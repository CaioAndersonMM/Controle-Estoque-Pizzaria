#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "pizzaria.h"
#include <string.h>

bool compareStrings(char* nome1, char* nome2) {
    // Compara as strings sem diferencia��o de mai�sculas e min�sculas

    //Corre��o Implementada, se eu quiser adicionar MASSA E MASSARICO, por exemplo
    if(strlen(nome1) != strlen(nome2))//se elas forem do mesmo tamanho
        return false;

    for (int i = 0; nome1[i] != '\0' && nome2[i] != '\0'; i++) { //for com condi��o de at� chegar no fim das strings
        if (tolower(nome1[i]) != tolower(nome2[i])) { //transforma a letra em minuscula e verifica se s�o diferentes
            return false;
        }
        //strcmp(nome1, nome2) == 0;
    }

    return true; //se n�o for diferente, ou seja, as minusculas s�o iguais, ent�o � verdadeiro
}

void AdicionarNoEstoque(Produto*& vetor_estoque, int& qtdProdutos) {

    Produto productadd;
    cout << "Produto: ";
    cin >> productadd.nome;
    cout << "Pre�o: ";
    cin >> productadd.preco;
    cout << "Quantidade: ";
    cin >> productadd.quantidade;

    bool exist = false;
    int indice = 0;

    for (int i = 0; i < qtdProdutos; i++) {
        if (compareStrings(productadd.nome, vetor_estoque[i].nome)) { //Se existem produtos com nomes iguais - maiusculos ou minusculos
            //cout << "Esse produto j� existe, atualizando... " << endl;
            exist = true;
            indice = i;
            break;
        }
    }
    if (exist) { //Se existem produtos com nomes iguais
        vetor_estoque[indice].preco = productadd.preco; //atualiza o pre�o
        //for (int j = 0; j < productadd.nome[j] != '\0'; j++)
        //{
        //  vetor_estoque[indice].nome[j] = productadd.nome[j]; //atualiza os caracteres do nome
        //}
         //vetor_estoque[indice].nome[strlen(vetor_estoque[indice].nome)] = '\0'; //colocando fim do caractere na ultima posi��o.
        strcpy(vetor_estoque[indice].nome, productadd.nome);//atualiza os caracteres do nome
        vetor_estoque[indice].quantidade += productadd.quantidade; //aumenta a quantidade
    }
    else { //Se produto n�o existe
        //cout << "Novo produto... " << endl;
        vetor_estoque[qtdProdutos] = productadd; //Na �ltima posi��o do vetor de estoque adiciono o produto novo
        qtdProdutos++; //Aumento a quantidade de produtos que existem
    }
}

void ExcluirDoEstoque(Produto*& vetor_estoque, int& qtdProdutos) {
    int numproduct = 0;
    char seletor;

    //Imprimo o vetor de estoque
    for (int i = 0; i < qtdProdutos; i++)
    {
        cout << i+1 << ") " << vetor_estoque[i].nome << endl;
    }
    cout << "Numero do produto:";
    cin >> numproduct;

    numproduct--; //Estou diminuindo uma posi��o j� que foi manipulado visualmente para o usu�rio as posi��es do vetor

    if (numproduct < 0 || numproduct >= qtdProdutos) { //Se o usu�rio escolher um produto fora da faixa!
        cout << "Produto Inv�lido" << endl;
        return; //Sai da fun��o
    }

    cout << "Deseja excluir " << vetor_estoque[numproduct].nome << " (S/N)? ";
    cin >> seletor;

    if (seletor == 'S' || seletor == 's'){
        //Primeiro eu vou colocar o elemento que o usu�rio escolheu para a �ltima posi��o do vetor
            //Antes eu estava criando um novo vetor menor, isso n�o � necess�rio!

        for (int i = numproduct; i < qtdProdutos - 1; i++) {
            //Estou come�ando o i na posi��o que o usu�rio quer apagar, e todos depois dele est�o vindo, um espa�o ficar� vazio no final!
            vetor_estoque[i] = vetor_estoque[i + 1];
            //A posi��o que o usu�rio escolheu, a que tinha antes no caso, foi "esquecida" apagada
        }

        qtdProdutos--; //Quantidade de produtos diminui

    }
}

void Listar(const Produto* vetor, const int& qtdProdutos) {
    //Imprimo o vetor de estoque, com a qtdProdutos sendo o tamanho limitante - porque ele pode ser maior (capacidade) e estar vazio em algumas posi��es
    for (int i = 0; i < qtdProdutos; i++){
        cout << vetor[i].nome << " - " << "R$" << vetor[i].preco << " - " << vetor[i].quantidade << "kg " << endl;
    }
}

void Pedir(Produto*& vetor, const int qtdProdutos) {

    char nomearqv[30]{};

    cin.get(); //Limpeza do buff

    cout << "Arquivo: ";

    cin.getline(nomearqv, 30);

    ifstream arqv;

    char titulo[30];
    char tracos[30];
    char nameproduct[15]; //nome do produto
    char nameproducts[10][10]; //vetor de vetor de char
    float qtdproducts[10]; //valores dos nameproducts
    float qtdproduct = 0; //valor do produto

    bool NaoGerarNfc = false;
    
	arqv.open(nomearqv); //Abre o arquivo que o usuario deu o nome

	if (!arqv.is_open()) {
        perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}
	else { //Caso abra normalmente

        //Ler cabe�alho do arqv
        arqv.getline(titulo, 30);
        arqv.getline(tracos, 30);

        int cont = 0;
        int tamanhoName = 0;
       
        int numProducts = 0; //contador para o n�mero de produtos no vetor

        bool firstFalha = true;

        while (!arqv.eof()){  //Enquanto o arquivo nao chegar no final "End of file"

            bool nomejaexiste = false; //bool se o nome j� existe no vetor

            // Ler de arqv o nome do produto e a quantidade dele
            arqv >> nameproduct >> qtdproduct;

            //cout << nameproduct << "-produto e quantidade-" << qtdproduct << endl;

            nameproduct[strlen(nameproduct)] = '\0'; //colocando caractere nulo no fim do nome do produto
            tamanhoName = strlen(nameproduct);

            //Procura pelo nome lido no vetor
            for (int i = 0; i < numProducts; i++) {
                if (compareStrings(nameproduct, nameproducts[i])) { //se o nome j� existe no vetor
                    nomejaexiste = true; //marca como encontrado
                    //cout << "ja existe produto com esse nome" << endl << endl;
                    qtdproducts[i] += qtdproduct; //como ja existe o produto e a quantidade pode ser outra, iremos somar
                    //a posi��o deve ser i, porque � aquele indice de nameproducts! - importante isso
                    break; //quebra o la�o de repeti��o

                    //n�o � necess�rio aumenta um produto j� que ele j� existe
                }
                //Se n�o entrar no if o booleano permanecer� falso
            }

            //Se o nome n�o foi encontrado no vetor, adiciona-o ao final
            if (!nomejaexiste) {
                for (int i = 0; i < strlen(nameproduct); i++) {
                    nameproducts[numProducts][i] = nameproduct[i]; //na posi��o de numero de produtos vai salvar char por char do nome do produto
                    //o vetor de vetor de caracteres recebe os char de nameproduct na posi��o do numero de produtos (numProducts);
                }
                qtdproducts[numProducts] = qtdproduct; //coloca na posi��o do numero de produtos a quantidade de produtos dita pelo arquivo
                nameproducts[numProducts][strlen(nameproduct)] = '\0';
                numProducts++; //aumenta um produto
            }

        }

        /*
        for (int i = 0; i < numProducts; i++) {
            cout << "Produto " << i << ": " << nameproducts[i] << endl;
            cout << "Quantidade Solicitada" << ": " << qtdproducts[i] << endl;
        }
        */

        //Como os produtos ficaram em vetores irei us�-lo agora...

        // Criando vetor auxiliar para armazenar as quantidades originais
        //int quantidades_originais[qtdProdutos]; precisa ser valor const
        int* qtd_original = new int[qtdProdutos];

        //inicializa
        for (int i = 0; i < qtdProdutos; i++) {
            qtd_original[i] = 0;
        }

        //Armazenando a quantidade original do vetor de estoque nesse vetor auxiliar
        for (int i = 0; i < qtdProdutos; i++){
            qtd_original[i] = vetor[i].quantidade;
            //Pois NaoGerarNFC pode fuder tudo!
        }

        for (int i = 0; i < numProducts; i++) { //lembrando que numProducts � quantos produtos existem no arquivo pedido
            bool encontrado = false;
            for (int j = 0; j < qtdProdutos; j++){//qtdProdutos � o tamanho do vetor_estoque
                if (compareStrings(vetor[j].nome, nameproducts[i])) {//Se existir no vetor de estoque e no vetor de vetor de caracteres
                    encontrado = true; //foi encontrado
                    if (vetor[j].quantidade >= qtdproducts[i]){ //Se tiver quantidade suficiente no estoque
                            vetor[j].quantidade -= qtdproducts[i]; //diminuindo
                            //cout << "OK Existe no estoque e no pedido..." << endl;
                    }
                    else { //Nao tiver suficiente produtos no vetor
                        if(firstFalha){
                            cout << "Pedido falhou!" << endl;
                            firstFalha = false;
                        }
                        NaoGerarNfc = true; //N�o pode gerar o arquivo nfc
                        cout << nameproducts[i] << ": Solicitado = " << qtdproducts[i] << "kg / Em Estoque = " << vetor[j].quantidade << "kg " << endl;
                    }
                    break;
                }

                //se nao existir... encontado permanecer� false
            }
            if (!encontrado) { //N�o tem produto com esse nome no estoque
                if(firstFalha){
                    cout << "Pedido falhou!" << endl;
                    firstFalha = false;
                }
                NaoGerarNfc = true;
                cout << nameproducts[i] << ": Solicitado = " << qtdproducts[i] << "kg / Em Estoque = 0" << endl;
            }     
        }

        if (!NaoGerarNfc) {
            ofstream arqv;

            char recibo[20] = ""; 
            int total = 0;

            for (int i = 0; nomearqv[i] != '.'; ++i){ //pega o nome do nomearqv at� o ponto
                recibo[i] = nomearqv[i];
            }

            strcat(recibo, ".nfc"); //concatena .nfc em recibo

            arqv.open(recibo); //abre o novo arquivo com esse nome

            if (arqv.is_open()){
                //Adiciona cabe�alho
                arqv << titulo <<  endl;
                arqv << tracos << tracos << endl;

                for (int i = 0; i < numProducts; ++i){
                    for (int j = 0; j < qtdProdutos; j++) {// qtdProdutos � o tamanho do vetor_estoque
                        if (compareStrings(vetor[j].nome, nameproducts[i])) {//Se estiver no estoque e estiver no arquivo (nameproducts)
                            arqv << vetor[j].nome << "  " << qtdproducts[i] << "kg  a   " << vetor[j].preco << "/kg  =  R$" << (qtdproducts[i] * vetor[j].preco) << endl;
                            total += (qtdproducts[i] * vetor[j].preco);
                        }
                    }
                   
                }
                arqv << tracos << tracos << endl;
                    arqv << "                  Compra     =  " << total << endl;

                if (total >= 1000){//se for acima de mil reais.
                    arqv << "                  Desconto   = " << total * 0.10 << endl;
                    arqv << "                  Total      =  " << total - (total * 0.10);
                }
                else {
                    arqv << "                  Total      =  " << total;
                }
                cout << endl << "A opera��o foi um sucesso!" << endl;
            }
            else {
                cout << "A abertura do arquivo falhou!" << endl;
                exit(EXIT_FAILURE);
            }

        }
        else { //N�oGerarNFC � true, ent�o tudo deve ser cancelado, e os valores do estoque devem voltar ao valor antigo!
            //cout << endl << " NAO GERAR NFC " << endl;

            /*  // Imprimindo quantidades_originais
            cout << "Quantidades originais: ";
            for (int i = 0; i < qtdProdutos; i++) {
                cout << qtd_original[i] << " ";
            }
            cout << endl;
            */

            for (int i = 0; i < qtdProdutos; i++) {
                vetor[i].quantidade = qtd_original[i]; //retornando os valores originais
                //pois nao deve ser gerado o NFC
            }

        }

        delete[] qtd_original;
       
        arqv.close(); //fecha

	}
}