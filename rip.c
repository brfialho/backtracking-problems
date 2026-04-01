/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:04:17 by brfialho          #+#    #+#             */
/*   Updated: 2026/04/01 16:53:27 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

char	count_min_parenthesis(char *s)
{
	int open = 0;
	int close = 0;

	while (*s)
	{
		if (!(*s == '(' || *s == ')'))
			return (0);
		else if (*s == '(')
			open++;
		else if (*s == ')')
			close++;
		s++;
	}
	if (open - close == 0)
		return (0);
	return ((open < close) * open + (close < open) * close);
}

char	is_balanced(char *s, int min)
{
	int		open;
	int		close;

	open = 0;
	close = 0;
	while (*s)
	{
		if (*s == '(')
			open++;
		else if (*s == ')')
			close++;
		if (open - close < 0)
			return (0);
		s++;
	}
	return ((open - close) == 0 && open == min);
}

void	solver(char *s, int min, int index)
{
	if (!s[index])
		return ;

	int		i;
	char	c;

	i = index - 1;
	while (s[++i])
	{
		c = s[i];
		s[i] = ' ';
		if (is_balanced(s, min))
			puts(s);
		solver(s, min, index + 1);
		s[i] = c;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);

	int	min_parenthesis = count_min_parenthesis(argv[1]);
	if (!min_parenthesis)
		return (2);

	char	s[10000] = {0};

	int i = -1;
	while (argv[1][++i])
		s[i] = argv[1][i];


	printf("MIN: %d\n", min_parenthesis);
	solver(s, min_parenthesis, 0);
}
