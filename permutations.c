/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 20:47:04 by brfialho          #+#    #+#             */
/*   Updated: 2026/04/01 11:56:15 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*get_string(char *arg)
{
	char	*new;
	int		len;

	len = -1;
	while (arg[++len])
		if (!(arg[len] >= 'a' && arg[len] <= 'z'))
			return (NULL);
	new = calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	len = -1;
	while (arg[++len])
		new[len] = arg[len];
	return (new);
}

void	set_letters(char *string, char *letters)
{
	int		i;
	char	*l;

	i = -1;
	while (string[++i])
		letters[(int)string[i]] = 1;

	i = -1;
	l = letters;
	while (++i < 256)
		if (letters[i])
			*l++ = i;
	*l = 0;
}

void	solver(char *s, char *letters, char *used, int index)
{
	if (!letters[index])
	{
		puts(s);
		return ;
	}
	int i = -1;
	while (letters[++i])
	{
		if (used[(int)letters[i]])
			continue ;
		used[(int)letters[i]] = 1;
		s[index] = letters[i];
		solver(s, letters, used, index + 1);
		used[(int)s[index]] = 0;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	char 	letters[256] = {0};
	char	used[256] = {0};
	char	*s;

	s = get_string(argv[1]);
	if (!s)
		return (2);
	
	set_letters(s, letters);
	solver(s, letters, used, 0);		
	free(s);
}
