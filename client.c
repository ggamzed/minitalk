#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			nb = (nb * 10) + (str[i] - '0');
			i++;
		}
		else
		{
			write(1, "PID is not valid!\n", 19);
			exit(EXIT_FAILURE);
		}
	}
	return (nb);
}

void	send_signal(int pid, int result)
{
	static int	i = 0;

	i++;
	if (i <= 8)
	{
		if (i == 8)
			i = 0;
		if (result)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
	}
}

void	string_handler(int pid, char *str)
{
	static int	i = 0;
	static char	*s_str = 0;
	char		result;

	if (str)
		s_str = str;
	if (*s_str)
	{
		if ((*s_str >> i) & 1)
			result = 1;
		else
			result = 0;
		i++;
		if (i == 8)
		{
			s_str++;
			i = 0;
		}
	}
	if (!(*s_str))
		result = 0;
	send_signal(pid, result);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	server_pid = 0;

	(void)context;
	if (!server_pid)
		server_pid = info->si_pid;
	if (sig == SIGUSR1)
		string_handler(server_pid, NULL);
	if (sig == SIGUSR2) // altına server_pid = 0; gerekli mi?
		exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	struct sigaction	signal_action;

	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	if (argc != 3)
	{
		write(1, "Incorrect form! Format: ./client <PID> <String>\n", 49);
		exit(EXIT_FAILURE);
	}
	string_handler(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
