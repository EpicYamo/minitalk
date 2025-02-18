/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:44:13 by aaycan            #+#    #+#             */
/*   Updated: 2025/02/18 16:38:30 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void	ft_send_char_bits(char c, int pid);
static int	ft_atoi(const char *str);
static void	ft_server_affirmation(int sigval);
static void	ft_failure_processor(int option);

static int g_signal_received = 0;

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;
	int					i;

	sa.sa_handler = ft_server_affirmation; 
	sa.sa_flags = 0;
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	if (argc != 3)
		ft_failure_processor(1);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
			ft_failure_processor(2);
		if (argc == 3)
		{
			while (argv[2][i])
				ft_send_char_bits(argv[2][i++], pid);
			ft_send_char_bits('\0', pid);
			sleep(5);
			if (!g_signal_received)
				ft_failure_processor(3);
		}
	}
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	strg;

	sign = 1;
	strg = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = sign * -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		strg = (10 * strg) + (str[i] - '0');
		i++;
	}
	return (strg * sign);
}

static void	ft_send_char_bits(char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		i--;
	}
}

static void	ft_server_affirmation(int sigval)
{
	if (sigval == SIGUSR2)
	{
		write(1, "Server received the message successfully.\n", 42);
		g_signal_received = 1;
    	exit(EXIT_SUCCESS);
	}
}

static void	ft_failure_processor(int option)
{
	if (option == 1)
		write(2, "Error (Wrong Usage)\nUsage: <PID> <MESSAGE>\n", 43);
	else if (option == 2)
		write(2, "Error (PID was incorrect)\nPID must be a positive number.\n", 57);
	else if (option == 3)
		write(2, "Error (Timeout)\nServer did not respond in time or PID Number was incorrect.\n", 76);
	exit(EXIT_FAILURE);
}
