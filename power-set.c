/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power-set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:42:58 by brfialho          #+#    #+#             */
/*   Updated: 2026/04/02 16:34:55 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	solver(int n, int set_size, int *set, int *result, int index)
{
	if (index == set_size)
		return (0);
	
	int i = index - 1;	  

	return (0);
}

int main(int argc, char **argv)
{
	if (argc < 3)
		return (2);

	int	n	 = atoi(argv[1]);
	int	size = argc - 2;
	int	*set = calloc(size, sizeof(int));
	if (!set)
		return (1);
	int *result = calloc(size, sizeof(int)); 
	if (!result)
		return (free(set), 1);

	int i = 1;
	while (argv[++i])
		set[i - 2] = atoi(argv[i]);

	// printf("N: %d\n", n);
	// for (int j = 0; j < size; j++)
	// 	printf("set[%d]: %d\n", j, set[j]);
	solver(n, size, set, result, 0);
	free(set);
}
