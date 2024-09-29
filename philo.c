/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:56:46 by ysouhail          #+#    #+#             */
/*   Updated: 2024/09/29 09:56:46 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"
int main(int ac, char **av)
{
    t_table table;
    if (ac == 5 || ac == 6)
    {
        printf("abcde\n");
        ft_check(&table, av);
        printf("1234\n");
        ft_init(&table);
        printf("0000000\n");
        create_threads(&table);
        printf("1111111\n");
        monitor(&table);
        // pass_philo(&table);
    }
    else
        error_w("Error: invalid argument");
    
}
void monitor(t_table *data)
{
    int i;
    while (1)
    {
        i = 0;
        while(i < data->nb_p)
        {
            if((data->time_start - data->philo[i].last_meal_time) > data->t_d)
            {
                set_bool(&data->stop, &data->end_sim, true);
                ft_write("is dead", &data->philo[i]);
                return ;
            }
            i++;
        }
    }
}