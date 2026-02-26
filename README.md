# 🐚 Minishell - @42São Paulo

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
* **Arquitetura:** Divisão entre *Lexer* (tokenização), *Parser* (análise sintática) e *Executor*.

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


