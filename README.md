README - Projeto Prático 1 (PP1)
Descrição do Projeto:
Este projeto consiste na implementação de um interpretador para a linguagem fictícia NEE, que utiliza conceitos fundamentais de algoritmos e estruturas de dados. O interpretador lê um código-fonte no formato NEE e executa suas instruções, iniciando a execução a partir da função especial Z.

Objetivos:
O principal objetivo deste projeto é exercitar e avaliar habilidades em algoritmos e estruturas de dados, implementando um sistema de execução de código que simula o funcionamento de um interpretador. 

O projeto abrange:
Implementação de Tipos Abstratos de Dados (TADs):

Lista: Utilizada para armazenar as linhas do código-fonte, permitindo acesso sequencial e facilitando a execução dos comandos.

Pilha: Implementada com alocação dinâmica para gerenciar as chamadas de funções. A pilha armazena o endereço da linha seguinte a uma chamada de função, permitindo o retorno ao fluxo correto após a execução da função chamada.

Fila: Utilizada para gerenciar a ordem de execução dos comandos de impressão. A fila armazena os valores a serem impressos, garantindo que sejam exibidos na ordem correta.
Desenvolvimento de Algoritmos:

Algoritmos de Execução: Implementação de um algoritmo que interpreta e executa as instruções do código NEE, respeitando a hierarquia de chamadas de funções e a sequência de comandos.

Algoritmos de Impressão: Implementação de um algoritmo que processa e imprime os números inteiros gerados pelas instruções de impressão, assegurando que a saída esteja correta e formatada conforme especificado.
Tratamento de Fluxo de Execução: Criação de um mecanismo que controla o fluxo de execução a partir da função inicial Z, permitindo saltos para outras funções conforme necessário e garantindo o retorno ao ponto correto após a execução.

Funcionalidades
Funções NEE: Suporte para definir e chamar funções, bem como imprimir valores inteiros.
Execução do Código: Início da execução pela função Z, processando comandos e respeitando as chamadas de funções e a ordem de execução.
