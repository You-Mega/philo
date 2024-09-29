/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:21:08 by ysouhail          #+#    #+#             */
/*   Updated: 2024/09/28 22:21:08 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void error_w(char *str)
{
    printf("%s\n", str);
    exit(1);
}
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

void ft_check(t_table *data, char **av)
{
    data->nb_p = ft_atoi(av[1]);
    data->t_d = ft_atoi(av[2]) * 1000;
    data->t_e = ft_atoi(av[3]) * 1000;
    data->t_s = ft_atoi(av[4]) * 1000;
    if (av[5])
        data->num_must_eat = ft_atoi(av[5]);
    else
        data->num_must_eat = -1;
}

void    ft_init(t_table *data)
{
    int i = 0;

    data->end_sim = false;
    data->philo = malloc(sizeof(t_philo) * data->nb_p);
    if (!data->philo)
        error_w("malloc error");
    data->fork = malloc(sizeof(t_fork) * data->nb_p);
    if (!data->fork)
        error_w("malloc error");

    while (i < data->nb_p)
    {
        data->philo[i].meal_counter = 0;
        data->philo[i].last_meal_time = get_time();
        data->philo[i].id = i+1;
        data->philo[i].left_f = &data->fork[i];
        data->philo[i].right_f = &data->fork[(i + 1) % data->nb_p];
        pthread_mutex_init(&data->fork[i].mlx, NULL);
        pthread_mutex_init(&data->philo[i].meal, NULL);
        data->philo[i].table = data; 
        i++;
    }
    data->time_start = get_time();
    pthread_mutex_init(&data->write,   NULL);
    pthread_mutex_init(&data->stop,   NULL);
}
long    get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long milliseconds = (tv.tv_sec * 1000 ) + tv.tv_usec / 1000;
    return milliseconds;
}
// void pass_philo(t_table *jack)
// {
//     int i = 0;
//     while (i < jack->nb_p)
//     {
//         create_threads(jack->philo[i]);
//         i++;
//     }
    
// }
void create_threads(t_table *data)
{
    int i = 0;

    while (i < data->nb_p)
    {
        printf("//////\n");
        if (pthread_create(&data->philo[i].thread, NULL, philosopher_routine, &data->philo[i]) != 0)
            error_w("Error: pthread_create failed");
        i++;
    }
    i = 0;
    while (i < data->nb_p)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }
}

void    *philosopher_routine(void *data)
{
    t_philo *philo = (t_philo *)data;
    if(philo->id % 2  != 0)
        is_sleeping(philo);
    while (!get_bool(&philo->table->stop, philo->table->end_sim))
    {
        ft_write("is thinking", philo);
        is_eating(philo);
        is_sleeping(philo);
    }
    return NULL;
}

void is_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_f->mlx);
    ft_write("has taking a fork", philo);
    pthread_mutex_lock(&philo->right_f->mlx);
    ft_write("has taking a fork", philo);
    ft_write("is eating", philo);
    usslepp(philo->table->t_e);
    // usleep(philo->table->t_e);
    set_long(&philo->meal, &philo->last_meal_time, get_time());
    pthread_mutex_unlock(&philo->right_f->mlx);
    pthread_mutex_unlock(&philo->left_f->mlx);
}

void is_sleeping(t_philo *philo)
{
    ft_write("is sleeping", philo);
    usslepp(philo->table->t_s);
    // usleep(philo->table->t_s);
}

void ft_write(char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->write);
    printf("%ld %ld %s\n",(get_time() - philo->table->time_start), philo->id, str);
    pthread_mutex_unlock(&philo->table->write);
}

void    usslepp(long x)
{
    long temp;

    temp = get_time();
    long i = get_time();
    while (x > 1000 * (i - temp))
    {
        i = get_time(); 
        usleep(500);
    }
}

long get_long(pthread_mutex_t *mtx, long value)
{
    long temp;
    pthread_mutex_lock(mtx);
    temp = value;
    pthread_mutex_unlock(mtx);
    return (temp);
}

void set_long(pthread_mutex_t *mtx,long *dest, long value)
{
    pthread_mutex_lock(mtx);
    *dest = value;
    pthread_mutex_unlock(mtx);
}
bool get_bool(pthread_mutex_t *mtx, bool value)
{
    bool tmp;
    pthread_mutex_lock(mtx);
    tmp = value;
    pthread_mutex_unlock(mtx);
    return tmp;
}
void set_bool(pthread_mutex_t *mtx, bool *dest, bool m)
{
    pthread_mutex_lock(mtx);
    *dest = m;
    pthread_mutex_unlock(mtx);
}