# To-Do-List em C

Bem-vindo ao meu projeto to-do-list em C! Este é um simples programa de lista de tarefas feito em C incluindo algumas bibliotecas como <stdio.h>, <stdlib.h>, <stdbool.h>, <string.h>, <locale.h> e <ctype.h>. Também consta um header dicio.h que manipula as strings para corrigir as falhas que a biblioteca locale.h possui.

# Como Usar

Você vai precisar de um compilador para rodar o programa, no meu caso, eu utilizei o DEV c++ que permite construir programas em Linguagem C, após fazer a execução, o usuário vai se deparar com 9 opções: 

- Opção 1: inserir tarefas, você vai digitar um título e uma descrição para cadastrar uma tarefa no sistema.
- Opção 2: editar tarefas, você vai digitar o número equivalente a tarefa na lista e irá digitar um novo título e/ou uma nova descrição para a tarefa
- Opção 3: remover tarefas, você vai digitar o número equivalente a tarefa na lista e o algorítmo vai fazer a remoção desta tarefa na lista
- Opção 4: ver tarefas não concluídas, uma opção somente para visualização de tarefas que estiverem com o status de não concluídas
- Opção 5: ver tarefas já concluídas, uma opção somente para visualização de tarefas que o usuário ja marcou como concluídas
- Opção 6: marcar tarefas como concluídas, uma opção que o usuário pode definir se uma tarefa ja foi concluída, ele mescolhe um número equivalente a tarefa na lista e depois o algoritmo muda o status desta tarefa
- Opção 7: salvar em arquivo, esta opção permite você salvar todos os itens em um arquivo txt para que você não perca as tarefas ao fechar o programa
- Opção 8: estatísticas de tarefas, somente números de tarefas, bem como porcentagens, para o usuário verificar.
- Opção 9: sair, com essa opção o programa é encerrado

## Baixar

Para baixar abra o terminal no diretório que deseja salvar o arquivo e digite:

```
https://github.com/LucMacedoo/ToDoList-linguagemC.git
```

## Motivo do projeto

O projeto foi feito para treino de linguagem de programação em C, colocando o aprendizado da faculdade na prática, as técnicas de lista simplesmente encadeadas foram executadas com sucesso neste programa. Técnicas de manipulação de strings também foram muito utilizadas neste programa, como o locale.h para Portuguese_Brazil contém alguns erros na hora do usuário digitar palavras, um arquivo de substituição de strings foi inserida para fazer as devidas correções. As técnicas de arquivos externos também foram utilizadas, leitura de arquivos e gravamento de dados fizeram parte do código do to-do-list para melhor usabilidade dos dados.
