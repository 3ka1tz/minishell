#include "../include/minishell.h"

int	g_status = 0;

static void	init_mini(t_mini *mini, char **envp)
{
	mini->env = copy_env(envp);
	mini->input = NULL;
	mini->tokens = NULL;
	mini->nodes = NULL;
	mini->nbr_nodes = 0;
}

void	mini_loop(t_mini *mini)
{
	while (1)
	{
		init_input(mini);
		create_nodes(mini);
		execution(mini);
		free_mini(mini);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	mini = malloc(sizeof(*mini));
	if (!mini)
	{
		perror("minishell: malloc");
		return (1);
	}
	ft_putstr_fd("Minishell by elopez-u and iullibar\n", 1);
	init_mini(mini, envp);
	handle_signals();
	mini_loop(mini);
	return (0);
}
