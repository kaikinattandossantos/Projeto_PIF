# 🚢 Batalha Naval (C)

![Language](https://img.shields.io/badge/language-C-blue)
![Course](https://img.shields.io/badge/course-PIFSI%202025.2-orange)
![Status](https://img.shields.io/badge/status-completed-brightgreen)

> Projeto da disciplina **Programação de Inovação e Fundamentos de Sistemas de Informação** (PIFSI 2025.2) da **CESAR School**, pelo professor **João Victor Tinoco**.



## 📋 Sobre o Projeto

Este projeto consiste na implementação do clássico jogo **Batalha Naval** (Battleship) via interface de linha de comando (CLI).

O objetivo pedagógico foi consolidar os fundamentos da programação estruturada em C, com foco em gerenciamento de memória e boas práticas de arquitetura.

### ✨ Principais Funcionalidades
* **Menu Interativo:** Opções para iniciar jogo, configurações e sair.
* **Tabuleiro Configurável:** O tamanho do grid pode ser ajustado entre 6x6 e 26x26 (padrão 10x10).
* **Posicionamento Flexível:** Escolha entre posicionar navios manualmente ou deixar o computador fazer isso aleatoriamente.
* **Relatório Pós-Jogo:** Exibição de estatísticas (precisão, total de tiros) e estado final dos tabuleiros.

---

## 👥 Equipe

| Aluno | Email | Responsabilidades |
| :--- | :--- | :--- |
| **Kaiki nattan** | knsg@cesar.school | • **Build System (Makefile)** e Interface<br>• Sistema de Menus e Configurações<br>• Revisão de Código e Git Flow<br>• Documentação |


---

## 🛠️ Tecnologias e Ferramentas

* **Linguagem:** C (Standard C99)
* **Compilação:** GCC via Makefile
* **Bibliotecas:** Apenas padrão (`stdio.h`, `stdlib.h`, `string.h`, `time.h`, `ctype.h`).

---

## 🚀 Instalação e Execução

Para facilitar a compilação, incluímos um **Makefile** que automatiza todo o processo.

### 1. Preparar o Ambiente
Certifique-se de estar na pasta raiz do projeto (onde está este README e o arquivo Makefile).

### 2. Compilar e Rodar (Via Makefile - Recomendado)
Se você tiver o `make` (ou `mingw32-make` no Windows) instalado, basta rodar um único comando para compilar e iniciar o jogo automaticamente:

```bash
make

```

## 🎮 Como Jogar

1.  **Menu Principal:**
    * Escolha **(1) Novo Jogo** para começar.
    * Escolha **(2) Configurações** para alterar o tamanho do tabuleiro (padrão 10x10).

2.  **Preparação:**
    * Insira os apelidos dos jogadores.
    * Escolha o posicionamento da frota: **(M)anual** (você digita coordenadas) ou **(A)utomático** (aleatório).

3.  **O Combate:**
    * Os turnos são alternados. O jogador vê o tabuleiro inimigo (sem navios) e sua própria frota.
    * Digite a coordenada do ataque (ex: `B5`).
    * O jogo informa: **ÁGUA**, **ACERTOU** ou **AFUNDOU**.

4.  **Vitória e Stats:**
    * O jogo termina quando todos os navios de um oponente forem afundados.
    * Ao final, são exibidas a **precisão de tiro (%)** e o número total de turnos.

---

## 🧠 Decisões de Design

Seguindo os requisitos do projeto, adotamos as seguintes estratégias de implementação:

* **Modularização:** O código foi separado em módulos lógicos (`board`, `fleet`, `game`, `io`, `rnd`) para respeitar o princípio de responsabilidade única e facilitar a manutenção.
* **Alocação Dinâmica:** As matrizes dos tabuleiros (`Board`) e os vetores de navios (`Fleet`) são alocados dinamicamente com `malloc` baseados no tamanho configurado pelo usuário. Toda memória é liberada com `free` ao final da execução.
* **Structs e Ponteiros:** Utilizamos `structs` para agrupar dados relacionados (como o estado do jogador na struct `Player`) e passamos essas estruturas via ponteiros para evitar cópias desnecessárias de memória durante as chamadas de função.
* **Encapsulamento de IO:** Todas as operações de entrada e saída (printf/scanf) foram concentradas no módulo `io.c`, mantendo a lógica do jogo (`game.c`) limpa e focada nas regras de negócio.

---

## 🏗️ Estrutura de Arquivos

```text
📁 pif-naval-c-main
│
├── 📄 Makefile         # Script de automação de build
├── 📄 README.md        # Documentação do projeto
|
│
└── 📁 src              # Código Fonte
    ├── main.c          # Ponto de entrada e Menu Principal
    ├── game.c/h        # Lógica de turnos, validação e estatísticas
    ├── board.c/h       # Alocação de matriz e manipulação de células
    ├── fleet.c/h       # Definição de navios e frota
    ├── io.c/h          # Interface de usuário (Inputs e Displays)
    └── rnd.c/h         # Gerador de aleatoriedade
