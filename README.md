Projeto Prático 1 - Algoritmo e Estrutura de Dados


Chat, fiz um interpretador de uma pseudo linguagem que funciona da seguinte forma

a chamada de função é uma unica letra maiuscula seguida de espaço seguido de dois pontos:

ex:

A :

após a  funcao temos duas possibilidades: 

print identado com quatro espaços em branco com numero não negativo exemplo:

    PRINT 1


ou uma chamada para outra função, que é apenas uma letra maiuscula identado com 4 espaçoes em branco. exemplo: 


    B
após cada fim de bloco de código deve haver uma linha em branco para separar os blocos

o fim do código sempre deve ser uma linha com apenas ~

a função principal da linguagem é a Z :, que é de onde o programa iniciara, Z : pode estar em qualquer parte do código. segue um exemplo de codigo e sua saída:


A :
    PRINT 1
    PRINT 2
    B

B :
    PRINT 3
    PRINT 5

Z : 
    A

~


a saída desse código seria : 1 2 3 5

preciso que faça casos de testes complexos, porém que não ocorram erros de recursividade, por exemplo: função A que chama B que chama C que chama A

isso ocorreria num looping infinito, por tanto, não deve ser usado como caso teste.

Não faça nada além da sintaxe descrita, laços de repetições ou coisas do tipo
