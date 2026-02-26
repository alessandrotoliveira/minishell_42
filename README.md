# 🐚 Minishell - @42São Paulo
![42 Badge](https://img.shields.io/badge/Score-93%2F100-success?style=for-the-badge&logo=42)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Norminette](https://img.shields.io/badge/Norminette-Passing-brightgreen?style=for-the-badge)

## 📝 Sobre o Projeto
O **Minishell** é um dos projetos mais desafiadores do currículo inicial da 42. O objetivo é criar um shell simples, mas funcional, replicando o comportamento do Bash. O foco está no gerenciamento de processos, manipulação de descritores de arquivo (file descriptors), parsing de comandos e execução de built-ins.

> "As beautiful as a shell"

---

## ✨ Funcionalidades
O shell suporta as seguintes operações:

* **Prompt interativo:** Exibe um prompt funcional aguardando comandos.
* **Histórico:** Mantém um histórico de comandos executados (utilizando `readline`).
* **Execução de Binários:** Busca e executa executáveis baseados na variável de ambiente `PATH` ou caminhos relativos/absolutos.
* **Built-ins implementados:**
    * `echo` (com opção `-n`)
    * `cd` (apenas caminho relativo ou absoluto)
    * `pwd`, `export`, `unset`, `env`, `exit`
* **Redirecionamentos:**
    * `<` redireciona a entrada.
    * `>` redireciona a saída (truncate).
    * `<<` heredoc.
    * `>>` redireciona a saída (append).
* **Pipes (`|`):** A saída de cada comando no pipeline é conectada à entrada do próximo comando.
* **Variáveis de Ambiente:** Expansão de `$VAR` e do status de saída `$?`.
* **Sinais:** Lida corretamente com `Ctrl-C`, `Ctrl-D` e `Ctrl-\` como no Bash.

---

## 🛠️ Tecnologias e Conceitos
* **Linguagem:** C
* **Principais Funções:** `fork`, `execve`, `waitpid`, `pipe`, `dup2`, `sigaction`.
* **Gerenciamento de Memória:** Tratamento rigoroso de memory leaks (uso de `valgrind`).
---

## 🏗️ Arquitetura do Projeto

O Minishell funciona através de um loop contínuo (Read-Eval-Print Loop - REPL) seguindo este fluxo:

### 🔄 Ciclo de Vida de um Comando

1.  **Readline**: Captura a entrada do usuário e adiciona ao histórico.
2.  **Lexer (Tokenização)**: Divide a string de entrada em "tokens" (palavras, operadores como `|`, `<`, `>`).
3.  **Parser (Análise Sintática)**: Organiza os tokens em uma estrutura de dados (geralmente uma lista ligada de comandos), identificando comandos, argumentos e redirecionamentos.
4.  **Expansor**: Substitui variáveis de ambiente (ex: `$USER`) e trata as aspas (`'` e `"`).
5.  **Executor**:
    * Cria *pipes* se necessário.
    * Faz o `fork()` para comandos externos.
    * Redireciona entrada/saída (`dup2`).
    * Executa built-ins ou busca o binário no `PATH`.
6.  **Cleanup**: Limpa a memória alocada e aguarda o próximo comando.

### 🗺️ Fluxograma Visual

```text
       [ ENTRADA DO USUÁRIO ]
                |
                v
      +--------------------+
      |       LEXER        |  --> Divide em tokens (palavras, pipes, redirs)
      +--------------------+
                |
                v
      +--------------------+
      |       PARSER       |  --> Cria a estrutura de comandos
      +--------------------+
                |
                v
      +--------------------+
      |     EXPANSOR       |  --> Resolve $VAR e retira aspas
      +--------------------+
                |
                v
      +--------------------+
      |     EXECUTOR       |  --> Fork, Pipes, Redirs e Execve
      +--------------------+
                |
                v
       [ RETORNO AO PROMPT ]
---

## 🚀 Como Executar

### Pré-requisitos
Você precisará da biblioteca `readline` instalada. No Ubuntu/Debian:
```bash
sudo apt-get install libreadline-dev
```
### Instalação e Uso:
```bash
git clone https://github.com/alessandrotoliveira/minishell_42.git
```
### Entre na pasta e compile:
```bash
cd minishell && make
```
### Inicie o shell
```bash
./minishell
```


