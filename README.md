# Dicionario com Hash

# Repositório – Tabela Hash em C

Este repositório contém uma atividade desenvolvida na disciplina de Estruturas de Dados utilizando a linguagem C.
O projeto consiste na implementação de um dicionário utilizando Tabela Hash com tratamento de colisões por listas encadeadas.

## Funcionalidades

O sistema permite:

- inserir palavras e definições;
- buscar palavras cadastradas;
- remover palavras;
- exibir a tabela hash;
- tratar colisões utilizando listas encadeadas;
- exibir estatísticas da tabela.

## Estruturas Utilizadas

### No

Armazena uma palavra, sua definição e um ponteiro para o próximo elemento da lista encadeada.

### TabelaHash

Armazena:

- tamanho da tabela;
- quantidade de elementos;
- quantidade de colisões;
- vetor de buckets (listas encadeadas).

## Função Hash

A função hash calcula o índice de armazenamento somando os valores ASCII dos caracteres da palavra e aplicando o operador módulo (`%`) com o tamanho da tabela.

## Funções Principais

- `criarNo`: cria um novo nó dinamicamente;
- `criarTabela`: cria e inicializa a tabela hash;
- `hashString`: calcula o índice de uma palavra;
- `inserir`: adiciona ou atualiza palavras no dicionário;
- `buscar`: procura uma palavra na tabela;
- `remover`: remove uma palavra do dicionário;
- `imprimirTabela`: exibe o conteúdo da tabela hash;
- `mostrarEstatisticas`: exibe informações sobre a tabela.

## Estatísticas

O sistema exibe:

- quantidade de elementos;
- quantidade de colisões;
- fator de carga;
- maior lista encadeada.

## Conceitos Aplicados

- Tabela Hash;
- Função Hash;
- Listas Encadeadas;
- Structs;
- Ponteiros;
- Alocação Dinâmica;
- Manipulação de Strings.
