# 🚢 Batalha Naval — Implementação em C

Trabalho desenvolvido para a disciplina **Programação de Inovação e Fundamentos de Sistemas de Informação — PIFSI 2025.2**, na **CESAR School**, sob orientação do professor **João Victor Tinoco**.

---

## 📘 Visão Geral do Projeto

Este repositório apresenta uma versão em C do tradicional jogo **Batalha Naval**, executado totalmente via **linha de comando**.  
A proposta do trabalho é reforçar conhecimentos de **programação estruturada**, **uso adequado de memória** e **organização modular do código**.

---

## 🔧 Recursos Implementados

- Menu inicial intuitivo, permitindo **iniciar partidas**, **alterar preferências** e **encerrar** o programa.  
- Tabuleiro **personalizável**, variando de **6×6 a 26×26** (valor padrão: **10×10**).  
- Configuração da frota de forma **manual ou automática**, dependendo da preferência do jogador.  
- Resumo final da partida, com estatísticas como **precisão**, **total de disparos** e **visualização do estado final dos tabuleiros**.

---

## 👥 Equipe

| Aluno              | Email                                   | Responsabilidades |
|--------------------|-----------------------------------------|-------------------|
| **Kaiki Nattan**   | [knsg@cesar.school](mailto:knsg@cesar.school) | • **Build System (Makefile)** e Interface<br>• Sistema de Menus e Configurações<br>• Revisão de Código e Git Flow<br>• Documentação |
| **Leandro Cisneiros** | [lcml@cesar.school](mailto:lcml@cesar.school) | • **Lógica Principal do Jogo** (`game.c`)<br>• Implementação de Structs `Player` / `Game`<br>• Sistema de Disparos e Verificação de Vitória<br>• Gerenciamento de Ponteiros e Memória (`doshot`, `gameloop`)<br>• Integração de Módulos (`board`, `fleet`) |
| **Davi Nogueira**  | [don@cesar.school](mailto:don@cesar.school) | • **Módulo de Entrada e Validação** (`io.c`, `io.h`)<br>• Parsing de Coordenadas e Inteiros (`ioreadline`, `ioparsecoord`, `ioparseint`)<br>• Geração e Inicialização de Aleatoriedade (`rnd.c`, `rnd.h`)<br>• Testes de Jogabilidade (casos de borda e entradas inválidas)<br>• Apoio na Definição do Tabuleiro e Frotas (tamanho, limites, regras de posicionamento) |

---

## 🛠 Tecnologias Utilizadas

- **Linguagem:** C (padrão **C99**)  
- **Compilação:** **GCC** com uso de **Makefile**  
- **Bibliotecas:** apenas as da linguagem C padrão (`stdio.h`, `stdlib.h`, `string.h`, `time.h`, `ctype.h`)

---

## 🚀 Compilação e Execução

Um **Makefile** acompanha o projeto para agilizar o processo de build.

### 1. Antes de começar

Entre no diretório principal do projeto (mesmo local do `Makefile` e do `README`).

### 2. Compilando e executando

Se possuir `make` (ou `mingw32-make` no Windows), basta rodar:

make


O jogo será compilado e executado automaticamente.

---

## 🎮 Dinâmica do Jogo

### Menu Principal

- `(1)` Iniciar uma nova partida  
- `(2)` Ajustar configurações (como o tamanho do tabuleiro)  

### Configuração Inicial

- Jogadores entram com seus **apelidos**.  
- Escolha entre posicionamento **Manual (M)** ou **Automático (A)**.  

### Partida

- Os jogadores se **alternam para atacar**.  
- O ataque é marcado por **coordenadas** (ex.: `C7`).  
- O jogo responde com **Água**, **Acertou** ou **Navio Afundado**.  

### Encerramento

- A partida termina quando **toda a frota de um jogador** for destruída.  
- **Estatísticas finais** são exibidas, incluindo **precisão** e **número total de turnos**.  

---

## 🧩 Decisões de Arquitetura e Organização

Para manter o código limpo e fácil de evoluir, foram adotadas as seguintes estratégias:

### Divisão Modular

O código foi separado em arquivos como `board`, `fleet`, `game`, `io` e `rnd`, cada qual cuidando de uma parte específica da lógica.

### Uso de Alocação Dinâmica

Os tabuleiros e as estruturas de navios são criados dinamicamente com `malloc`, de acordo com o tamanho definido no menu.  
Toda a memória é liberada ao final da execução.

### Structs + Ponteiros

Dados relacionados foram agrupados em `structs`, como a estrutura `Player`.  
As funções recebem **ponteiros** para evitar cópias desnecessárias e melhorar o desempenho.

### Centralização de Entrada/Saída

Todo o fluxo de **entrada e saída** foi isolado no arquivo `io.c`, deixando a lógica principal no `game.c` mais clara e organizada.
