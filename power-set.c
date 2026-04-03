/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power-set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:42:58 by brfialho          #+#    #+#             */
/*   Updated: 2026/04/03 18:08:16 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_set
{
	int *set;
	int	size;
} t_set;

int	sum_result(t_set *result)
{
	int sum = 0;

	int i = - 1;
	while (++i < result->size)
		sum += result->set[i];
	return (sum);
}

void	print_sum(t_set *result)
{
	int i = -1;
	while (++i < result->size)
	{
		printf("%d", result->set[i]);
		if (i + 1 < result->size)
			printf(" ");
	}
	printf("\n");
}

void	solver(int n, t_set *set, t_set *result, int index)
{
	while (index < set->size)
	{
		result->set[result->size] = set->set[index];
		result->size++;
		solver(n, set, result, index + 1);
		if (sum_result(result) == n)
			print_sum(result);
		result->set[index] = 0;
		result->size--;
		index++;
	}
}

int main(int argc, char **argv)
{
	if (argc < 3)
		return (2);

	t_set	set;
	t_set	result;
	int	n;

	n = atoi(argv[1]);
	if (!n)
		printf("\n");
	set.size = argc - 2;
	set.set = calloc(set.size, sizeof(int));
	if (!set.set)
		return (1);
	result.size = 0;
	result.set = calloc(set.size, sizeof(int)); 
	if (!result.set)
		return (free(set.set), 1);

	int i = 1;
	while (argv[++i])
		set.set[i - 2] = atoi(argv[i]);

	solver(n, &set, &result, 0);
	free(set.set);
	free(result.set);
}
