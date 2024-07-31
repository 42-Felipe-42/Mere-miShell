#include "../include/minishell.h"

// Gestionnaire de signal pour les interruptions generales
void	handle_signal(int signal)
{
	g_signal = signal;
	if (wait(NULL) != -1)
	{
		if (signal == SIGQUIT)
			printf("Quit (core dumped)\n");
		else
			printf("\n");
	}
	else if (signal == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// Gestionnaire de signal specifique pour heredoc
void	handle_heredoc_signal(int signal)
{
	g_signal = signal;
	close(STDIN_FILENO);
	write(STDERR_FILENO, "^C", 3);
}

// Configuration des signaux pour heredoc
void	setup_heredoc_signals(void)
{
	struct sigaction	sig;

	sig.sa_flags = 0;
	sig.sa_handler = handle_heredoc_signal;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
}

// Configuration des signaux pour le shell principal
void	setup_shell_signals(void)
{
	struct sigaction	sig;

	rl_catch_signals = 0;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_signal;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGTERM, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

// Vérification et gestion des signaux capturés
bool	check_captured_signals(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->tmpexit_code = 130;
		g_signal = 0;
		return (true);
	}
	else if (g_signal == SIGQUIT)
	{
		shell->tmpexit_code = 130;
		g_signal = 0;
		return (true);
	}
	return (false);
}