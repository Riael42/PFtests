/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speedtest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riael <Don't give up | #42gether>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:12:05 by riael             #+#    #+#             */
/*   Updated: 2026/05/12 13:13:37 by riael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <time.h>
#include "../includes/ft_printf.h"

void speedtest(void)
{
    clock_t start, end;
    double orig_time, mine_time;
    int i;
    int loops = 1000000; 

    fprintf(stderr, "Starting Benchmark... (Please wait)\n");

    start = clock();
    for (i = 0; i < loops; i++)
    {
        printf("Mix: %c %s %p %010d %-15i %u %x %X %%\n", 'G', "Macbeth", &i, -42, 42, 420, 42, 42);
    }
    end = clock();
    orig_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (i = 0; i < loops; i++)
    {
        ft_printf("Mix: %c %s %p %010d %-15i %u %x %X %%\n", 'G', "Macbeth", &i, -42, 42, 420, 42, 42);
    }
    end = clock();
    mine_time = ((double) (end - start)) / CLOCKS_PER_SEC;


    fprintf(stderr, "\n--- RESULTS ---\n");
    fprintf(stderr, "Standard printf : %f seconds\n", orig_time);
    fprintf(stderr, "Your ft_printf  : %f seconds\n", mine_time);

    if (mine_time < orig_time)
        fprintf(stderr, "Verdict: YOU BEAT THE STANDARD LIBRARY!\n");
    else
        fprintf(stderr, "Verdict: Standard library wins this time.\n");
}
