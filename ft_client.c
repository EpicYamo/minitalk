/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:44:13 by aaycan            #+#    #+#             */
/*   Updated: 2025/02/17 12:06:19 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void	ft_send_char_bits(char c, int pid);
static int	ft_atoi(const char *str);

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc != 3)
	{
		write(2, "Error (Wrong Usage)\nUsage: <PID> <MESSAGE>\n", 43);
		exit (EXIT_FAILURE);
	}
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
		{
			write(2, "Error (PID was incorrect)\nPID Should be a positive number.\n", 59);
			exit (EXIT_FAILURE);
		}
		if (argc == 3)
		{
			while (argv[2][i])
				ft_send_char_bits(argv[2][i++], pid);
			ft_send_char_bits('\0', pid);
			write(1, "Message Sent\n", 13);
		}
	}
	exit (EXIT_SUCCESS);
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
