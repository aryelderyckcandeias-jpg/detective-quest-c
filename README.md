# Detective Quest

Jogo de exploração no terminal, escrito em **C**, para praticar **árvores binárias** e **árvores binárias de busca (BST)**.

Você começa no Hall de uma mansão, escolhe entre ir para a esquerda ou para a direita e coleta pistas pelo caminho. Ao sair, o jogo mostra as pistas encontradas em **ordem alfabética**.

> Trabalho acadêmico de estudo de estruturas de dados.

## Conceitos praticados

| Conceito | Onde aparece |
| --- | --- |
| Árvore binária | A mansão: cada `Sala` aponta para uma sala à esquerda e outra à direita |
| Árvore binária de busca | As pistas coletadas ficam ordenadas em uma BST (`inserirPista`, usa `strcmp`) |
| Travessia in-order | `exibirPistas` imprime as pistas em ordem alfabética |
| Alocação dinâmica | `malloc` em `criarSala` e `inserirPista` |
| Ponteiro para ponteiro | `PistaNode**` permite alterar a raiz da BST dentro da função |
| Recursão | Inserção e exibição na BST |

## Mapa da mansão

```text
Hall
├── Sala de Estar      (pista: "Um bilhete rasgado.")
│   ├── Biblioteca
│   │   ├── Escritório (pista: "Um diário com anotações suspeitas.")
│   │   └── Varanda
│   └── Jardim         (pista: "Pegadas frescas no chão.")
│       ├── Estufa     (pista: "Uma chave antiga foi encontrada aqui.")
│       └── Lago
└── Cozinha
    ├── Despensa       (pista: "Restos de comida envenenada.")
    └── Lavanderia
```

## Como compilar e executar

Requisitos: `gcc` e `make` (Linux ou macOS). No Windows, use MinGW-w64 ou WSL.

```bash
make        # compila
make run    # compila e executa
make clean  # remove o binário
```

Sem `make`:

```bash
gcc -std=c11 -Wall -Wextra -o detective_quest src/detective_quest.c
./detective_quest
```

Comandos durante o jogo: `e` (esquerda), `d` (direita) e `s` (sair).

## Exemplo de execução

Trecho de uma partida (`e`, `e`, `e`, `s`):

```text
Você está na sala: Escritório
Pista encontrada: Um diário com anotações suspeitas.
Escolha um caminho:
...
Sua escolha: Exploração interrompida pelo jogador.

Pistas coletadas (em ordem alfabética):
- Um bilhete rasgado.
- Um diário com anotações suspeitas.
```

## Estrutura do projeto

```text
.
├── src/
│   └── detective_quest.c   # todo o código do jogo
├── Makefile
└── README.md
```

## Limitações conhecidas e próximos passos

- A memória das salas e da BST não é liberada ao final. Próximo passo: funções de limpeza recursivas (percurso pós-ordem).
- O retorno do `scanf` não é verificado.
- Não é possível voltar para a sala anterior, porque a `Sala` não guarda um ponteiro para a sala pai.
- Separar o código em `.h`/`.c` (salas, pistas, jogo) e adicionar testes automatizados.
