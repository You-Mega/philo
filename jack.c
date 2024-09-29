/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jack.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:20:53 by ysouhail          #+#    #+#             */
/*   Updated: 2024/09/28 22:20:53 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


// Error handling function
void error_w(char *str)
{
    printf("%s\n", str);
    exit(1);
}

// String to long conversion function with error checking
long ft_atoi(char *str)
{
    int i;
    long res;

    i = 0;
    res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;

    if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    if (str[i] != '\0')
        error_w("Error: invalid argument");
    return res;
}

// Check and initialize table data
void ft_check(t_table *data, char **av)
{
    data->nb_p = ft_atoi(av[1]);
    data->t_d = ft_atoi(av[2]) * 1000;
    data->t_e = ft_atoi(av[3]) * 1000;
    data->t_s = ft_atoi(av[4]) * 1000;
    if (av[5])
        data->nb_t_e = ft_atoi(av[5]);
    else
        data->nb_t_e = -1;
}

// Initialize philosophers and forks
void ft_init(t_table *data)
{
    int i = 0;

    data->philo = malloc(sizeof(t_philo) * data->nb_p);
    if (!data->philo)
        error_w("malloc error");
    data->fork = malloc(sizeof(t_fork) * data->nb_p);
    if (!data->fork)
        error_w("malloc error");

    while (i < data->nb_p)
    {
        data->philo[i].mail_counter = 0;
        data->philo[i].last_meal_time = get_time();
        data->philo[i].id = i;
        data->philo[i].left_f = &data->fork[i];
        data->philo[i].right_f = &data->fork[(i + 1) % data->nb_p];
        pthread_mutex_init(&data->fork[i].mutex, NULL);
        i++;
    }
    data->time_start = get_time();
}

// Get current time in milliseconds
long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long milliseconds = (tv.tv_sec * 1000) + tv.tv_usec / 1000;
    return milliseconds;
}

// Philosopher routine
void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Philosopher's actions (thinking, eating, sleeping) go here
    // This is a placeholder for the actual routine
    while (1)
    {
        // Thinking
        printf("Philosopher %d is thinking\n", philo->id);
        // Eating
        pthread_mutex_lock(&philo->left_f->mutex);
        pthread_mutex_lock(&philo->right_f->mutex);
        printf("Philosopher %d is eating\n", philo->id);
        philo->last_meal_time = get_time();
        philo->mail_counter++;
        pthread_mutex_unlock(&philo->right_f->mutex);
        pthread_mutex_unlock(&philo->left_f->mutex);
        // Sleeping
        printf("Philosopher %d is sleeping\n", philo->id);
    }
    return NULL;
}

// Create threads for each philosopher
void create_threads(t_table *data)
{
    int i = 0;

    while (i < data->nb_p)
    {
        if (pthread_create(&data->philo[i].thread, NULL, philosopher_routine, &data->philo[i]) != 0)
            error_w("Error: pthread_create failed");
        i++;
    }

    // Wait for all threads to finish (this is just a placeholder, actual implementation may vary)
    i = 0;
    while (i < data->nb_p)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }
}

int main(int ac, char **av)
{
    t_table data;

    if (ac < 5 || ac > 6)
        error_w("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
    ft_check(&data, av);
    ft_init(&data);
    create_threads(&data);
    return 0;
}