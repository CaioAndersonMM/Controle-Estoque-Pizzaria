# Controle de Estoque de Pizzaria

Os pedidos são enviados através de arquivos de texto contendo os produtos e quantidades desejadas. O programa lê o conteúdo e gera um recibo de compra. O recibo de compra mostra os produtos solicitados, seus preços unitários, as quantidades e o valor total. Após gerar o recibo, o sistema atualiza a quantidade em estoque de cada produto.

## Solicitação de Produtos
O cliente solicita os produtos através de um arquivo .txt da seguinte forma:


| Produto  | Quantidade |
|----------|------------|
| massa    | 20         |
| queijo   | 5          |
| Massa    | 10         |
| frango   | 5          |
| molho    | 40         |
| Queijo   | 30         |
| FRANGO   | 10         |
| presunto | 18         |

## Recibo gerado
O programa deve ler o conteúdo do pedido e gerar um recibo .nfc da seguinte forma:


| Produto  | Quantidade | Valor Unitário | Valor Total |
|----------|------------|----------------|-------------|
| Massa    | 30kg       | R$2.50/kg      | R$75.00     |
| Queijo   | 35kg       | R$15.00/kg     | R$525.00    |
| Frango   | 15kg       | R$9.00/kg      | R$135.00    |
| Molho    | 40kg       | R$8.20/kg      | R$328.00    |
| Presunto | 18kg       | R$10.00/kg     | R$180.00    |
|Compra = R$1243.00  |
Desconto = R$124.30
Total = R$1118.70


- Obs: A fim organizacional os exemplos foram mostrados em tabela, porém os arquivos devem seguir um padrão, primeiro o nome da pizzaria, depois um cabeçalho de linhas e posteriormente o nome do produto e a quantidade. No caso do recibo, segue o mesmo cabeçalho, mas ele tratará as informações na linha, por exemplo: (Massa 30kg a 2.50/kg = R$75.00). 

## Regras
Observe que no pedido os nomes podem usar letras maiúsculas ou minúsculas e podem haver 
pedidos do mesmo produto em linhas diferentes. Além disso, a empresa dá um desconto de 10%
para compras de valor igual ou superior a R$1000.00. 
Uma vez gerado o recibo de compra, a quantidade em estoque de cada produto deve ser 
atualizada no sistema. 

## Sistema de Controle
- Pedir: Lê um arquivo de pedido, gera um recibo para o pedido e atualiza as quantidades dos produtos em estoque. Caso algum produto solicitado esteja em falta ou em quantidade insuficiente, o pedido falha e uma mensagem é exibida. O recibo é um arquivo texto com o mesmo nome do arquivo de pedido, mas com a extensão ".nfc" (por exemplo: mamute.nfc).

- Adicionar: Adiciona um novo produto ao estoque, incluindo o nome do produto, o preço e a quantidade que está chegando ao estoque. Se o produto já existir, apenas o preço é atualizado e a quantidade informada é adicionada ao valor atual do estoque.

- Excluir: Mostra uma lista numerada dos produtos existentes no estoque. Ao escolher um número, o programa confirma a exclusão e remove o produto selecionado do estoque.

- Listar: Mostra a lista de produtos existentes no estoque, exibindo o nome, valor unitário e quantidade de cada produto.

- Sair: Encerra o programa.

## Recursos
Um arquivo binário guarda as informações dos produtos em estoque. Este arquivo 
é lido na entrada do programa e seus dados passados para um vetor dinâmico. O arquivo 
é atualizado apenas ao final do programa. Quando a opção (S) Sair for selecionada, o 
programa sobrescreve o arquivo binário com o conteúdo atualizado do vetor dinâmico. 
Enquanto o programa estiver rodando, adições, exclusões, listagens e processamentos de 
pedidos são feitos sobre o vetor dinâmico.
Caso o arquivo de estoque ainda não exista, o programa simplesmente inicia com o vetor 
dinâmico vazio. 
O vetor dinâmico é inicializado com a quantidade de produtos no arquivo.
Se a capacidade do vetor for excedida durante a execução do programa, um novo vetor é
criado com a nova capacidade igual a capacidade anterior + 2n, sendo n a quantidade de vezes
que o vetor foi expandido. Os dados são copiados do vetor antigo para o novo e o vetor 
antigo é liberado da memória. 


