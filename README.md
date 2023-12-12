# SGDB (Sistema de Gerenciamento de Banco de Dados)

## Introdução
Este conjunto de funções em linguagem C oferece operações básicas de gerenciamento de banco de dados, incluindo criação de tabelas, inserção de dados, listagem de tabelas, busca e exclusão de dados. O SGDB utiliza arquivos de texto para armazenar dados das tabelas e metadados.

## Dependências
Certifique-se de incluir os seguintes arquivos de cabeçalho:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgdb.h"
#include "sgdbaux.h"
#include "straux.h"
#include "constant.h"
#include "interface.h"
```

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- `sgdb.h`: Contém o conjunto de **funções principais** relacionadas ao SGDB.
  - Funções principais: createTable, insertLine, listTables, printDataFromTable, searchDataFromTable, deleteLine, deleteTable. 
- `sgdbaux.h`: Contém o conjunto de funções auxiliares relacionadas ao SGDB.
- `straux.h`: Contém o conjunto de funções auxiliares relacionadas a manipulação de strings.
- `constant.h`: Contém o conjunto de constantes do projeto.
- `funcaux.h`: Contém o conjunto de funções gerais auxiliares do projeto.
- `interface.h`: Conjunto de funções relacionadas a interface visual do programa.
- `main.c`: Arquivo principal, onde será rodado o programa.

## Compilação e Execução
Compilação:
```
gcc main.c modules/impl/* -I modules/include 
```
Execução linux:
```
./a.out
```
Execução windows:
```
./a.exe
```

## Funções Principais

### `createTable`

```c
int createTable(int colQty, char *colTyp, char **colNames, char *pkName, char *tableName);
```
Esta função cria uma nova tabela no banco de dados. Ela recebe o número de colunas, os tipos das colunas, os nomes das colunas, o nome da chave primária e o nome da tabela como parâmetros.

### `listTables`

```c
void listTables();
```
Esta função lista todas as tabelas existentes no banco de dados.

### `insertLine`

```c
int insertLine(char *tableName, char **colValues);
```
Esta função insere uma nova linha de dados em uma tabela existente. Ela recebe o nome da tabela e os valores das colunas como parâmetros.

### `printDataFromTable`

```c
void printDataFromTable(char *tableName);
```
Esta função exibe os dados de uma tabela existente. Ela recebe o nome da tabela como parâmetro.

### `searchDataFromTable`

```c
void searchDataFromTable(char *tableName);
```
Esta função realiza uma pesquisa na tabela com base em critérios específicos. Ela recebe o nome da tabela como parâmetro.

Tivemos que definir um critério específico para o tipo string. Pois a depender da interpretação tem outras implementações. Entendemos como uma string *maior* ou *menor* que outra, sua análise lexicográfica. Para isso usamos a função `strcmp` do `string.h`. 
```c
int strcmp(const char *str1, const char *str2)
```
- A função retorna:
  -  `0` quando as trings são iguais.
  - Se str1 for lexicograficamente menor que str2, strcmp retorna um valor negativo.
  - Se str1 for lexicograficamente maior que str2, strcmp retorna um valor positivo.

Já para os valores próximos ao valor informada(*item 6*), usamos a função `strstr()`, da biblitoeca `string.h`. Essa função procura a ocorrência da primeira instância de uma substring em uma string maior, e é isso que etendemos como uma string "próxima a outra".
```c
char *strstr(const char *str1, const char *str2);
```
- A função retorna um ponteiro para a primeira ocorrência da substring em str1 ou NULL se a substring não for encontrada.

### `deleteLine`

```c
void deleteLine(char *tableName, char *pkName);
```
Esta função exclui uma linha específica de uma tabela com base na chave primária. Ela recebe o nome da tabela e a chave primária como parâmetros.

### `deleteTable`

```c
void deleteTable(char *tableName);
```
Esta função exclui uma tabela inteira do banco de dados. Ela recebe o nome da tabela como parâmetro.

## Módulos

Cada módulo deve ter uma responsabilidade específica, isso garante vantagens como: legibilidade/manutenção, reusabilidade, testabilidade, escalabilidade, colaboração, flexibilidade/manutenção evolutiva e entendimento conceitual.

Uma função para criar tabela, não deve, por exemplo, se preocupar em pedir entrada de dados ou fazera saída de dados, isso é de responsabilidade de uma *interface*.

### `SGDB`
Esse módulo é responsável, **apenas**, por mexer com o banco de dados. Não sendo de sua responsabilidade tratar os dados ou fazer qualquer outra coisa que não envolva isso. Ou seja, as funções devem receber os dados perfeitos e ideais para serem executadas. Caso o usuário, por exemplo, digite um nome inválido, não é função desse módulo tratar esse erro.

A exceção da *searchDataFromTable*. Essa função, por si só, junta diversas responsabilidades. Então implementamos ela com algumas responsablidades misturadas, como entrada e saída de dados. Sendo ela a  o nosso patinho feio.

### `sgdbaux`
Esse módulo é responsável por funções que auxiliam as funções principais do banco de dados, funções que estão relacionadas as funções principais, mas não fazem as funcionalidades principais.

Um bom exemplo seria a função updatePK que auxiliam na inserção de uma linha no banco de dados, atualizando o arquivo. Para atualizar uma linha de um arquivo, precisamos recriar o arquivo e é isso que essa função faz.

### `straux`
Módulo responsável por funções que manipulam strings.

### `funcaux`
Módulo responsável por funções auxiliares gerais.

### `interface`
O segundo módulo mais importante é esse. Responsável pela entrada, tratamento de erros e de entradas; e saída de dados;

## Módulos

### O que foi feito
Foram feitas todas as funções pedida. As funcionalidades extras adicionadas são: a chave primária ser adicionada automaticamente. Adicionamos, também, a funcionalidade do usuário digitar quantas linhas irá adicionar de uma vez, tendo a oportunidade de adicionar em diferentes tabelas.

### O que faria de forma diferente
Teria usado constantes desde o começo para serem usadas em todo o programa. Como as constantes para as flags(os delimitadores como "|" e "-") da estrutura do banco de dados.

Teria tentado automatizar nossos testes para podermos, não só testar mais, como também ter mais segurança.

### Autores e Contribuições
Dupla: Ramon Jales e María Paz Marcato
 - Paz:
   - main 
   - listTables
   - printDataFromTable
   - deleteLine
   - deleteTable
   - searchDataFromTable: 1/2
   - módulo straux 1/2
   - limpar os dados do terminal

 - Ramon:
   - createTable
   - insertTable
   - insertLine
   - searchDataFromTable: 1/2
   - módulo interface,
   - módulo sgdbaux
   - módulo funcaux
   - módulo straux 1/2