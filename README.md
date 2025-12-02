🚢 Batalha Naval (C)

Projeto da disciplina Programação de Inovação e Fundamentos de Sistemas de Informação (PIFSI 2025.2) da CESAR School, ministrada pelo professor João Victor Tinoco.


📋 Sobre o Projeto
Este projeto consiste na implementação do clássico jogo Batalha Naval (Battleship) via interface de linha de comando (CLI).
O objetivo pedagógico foi consolidar os fundamentos da programação estruturada em C, com foco em gerenciamento de memória e boas práticas de arquitetura.

✨ Principais Funcionalidades
Menu Interativo: Opções para iniciar jogo, configurações e sair.
Tabuleiro Configurável: O tamanho do grid pode ser ajustado entre 6x6 e 26x26 (padrão 10x10).
Posicionamento Flexível: Escolha entre posicionar navios manualmente ou deixar o computador fazer isso aleatoriamente.
Relatório Pós-Jogo: Exibição de estatísticas (precisão, total de tiros) e estado final dos tabuleiros.

👥 Equipe
| Aluno                | Email                                         
| -------------------- | --------------------
| Kaiki Natan      | [knsg@cesar.school
| Leandro Langlois |                                            | 
| Davi Nogueira  | — don@cesar.school                                            


🛠️ Tecnologias e Ferramentas
Linguagem: C (Standard C99)
Compilação: GCC via Makefile
Bibliotecas: Apenas padrão (stdio.h, stdlib.h, string.h, time.h, ctype.h).

🚀 Instalação e Execução
1. Estar na pasta raiz
Onde estão o Makefile e o README.md.

2. Compilar e Executar

Se possuir make ou mingw32-make:

digite make
O jogo será compilado e executado automaticamente.

🎮 Como Jogar
1. Menu Principal

(1) Novo Jogo
(2) Configurações
(3) Sair

2. Preparação

Inserir apelidos dos jogadores
Escolher posicionamento da frota:
• M → Manual
• A → Automático

3. Jogo

Os jogadores alternam turnos

Veja seu tabuleiro e o tabuleiro mascarado do inimigo
Informe coordenadas de ataque (ex.: B5)
O jogo responde: ÁGUA, ACERTOU, AFUNDOU

4. Fim da Partida
Mostra:
Precisão
Total de tiros
Estado final dos tabuleiros

🧠 Decisões de Design
Modularização clara por responsabilidade
board.c → gerenciamento do tabuleiro
fleet.c → definição e posicionamento da frota
game.c → regras e fluxo do jogo
io.c → entrada e saída
rnd.c → geração de valores aleatórios
Alocação dinâmica segura (todo malloc tem seu free)
Uso de structs como Board, Fleet, Player, Cell

🏗️ Estrutura de Arquivos
📁 projeto_pif_main
│
├── Makefile
├── README.md
├── LICENSE
│
└── 📁 src
    ├── main.c
    ├── board.c / board.h
    ├── fleet.c / fleet.h
    ├── game.c / game.h
    ├── io.c / io.h
    └── rnd.c / rnd.h

