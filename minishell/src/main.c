#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_mini mini;
    char *input;
    
    (void)argc;
    (void)argv;
    
    // Inicialização única (fora do loop)
    ft_memset(&mini, 0, sizeof(t_mini)); 
    init_env(&mini, envp);
    init_signals();
    
    while (1)
    {
        input = readline("minishell> ");

        // Trata Ctrl+D (EOF)
        if (!input)
        {
            ft_putstr_fd("exit\n", 1);
            break;
        }

        // Se foi interrompido durante readline, resetar e continuar
        if (g_received_signal == SIGINT)
        {
            g_received_signal = 0;
            continue;
        }

        if (*input)
        {
            add_history(input);
            // Salva na struct para facilitar limpeza em caso de erro/sinal
            mini.input_line = input;

            if (parse_input(&mini, input) == SUCCESS)
            {
                // Aqui você chama o seu execute_pipeline ou executor
                executor(&mini);
            }
        }
        
        // Resetar sinal APÓS execução
        g_received_signal = 0;

        // LIMPEZA OBRIGATÓRIA A CADA COMANDO
        free(input);
        mini.input_line = NULL;
        if (mini.cmd_list)
        {
            free_commands(mini.cmd_list);
            mini.cmd_list = NULL;
        }
        // Limpar tokens também
        if (mini.tokens)
        {
            free_tokens(&mini.tokens);
        }
    }
    
    // Limpeza final antes de fechar o programa
    free_env_list(mini.env_list);
    rl_clear_history();
    return (mini.exit_code);
}