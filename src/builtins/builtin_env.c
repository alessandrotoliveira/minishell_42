#include "minishell.h"


int builtin_env(t_cmd *cmd, t_mini *mini)
{
    (void)cmd;
    t_env	*current;

    current = mini->env_list;
    while (current)
    {
        if (current->value)
        {
            ft_putstr_fd(current->key, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putendl_fd(current->value, STDOUT_FILENO);
        }
        current = current->next;
    }
    return (0);
}