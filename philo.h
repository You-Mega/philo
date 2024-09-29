/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:57:01 by ysouhail          #+#    #+#             */
/*   Updated: 2024/09/29 09:57:01 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>


typedef struct table t_table;


typedef struct fork
{
    pthread_mutex_t mlx;
    int fork_id;
} t_fork;

// Struct for philosopher
typedef struct philo
{
    long id;
    long meal_counter; 
    bool full;
    long last_meal_time;
    t_fork *left_f;
    t_fork *right_f;
    t_table *table;
    pthread_t thread;
    pthread_mutex_t meal;
} t_philo;

// Struct for table
typedef struct table
{
    long nb_p;
    long t_d;
    long t_e;
    long t_s;
    long num_must_eat;
    long time_start;
    bool end_sim;
    t_philo *philo;
    t_fork *fork;
    pthread_mutex_t write;
    pthread_mutex_t stop;
} t_table;


long    ft_atoi(char *str);
void    ft_check(t_table *data, char **av);
void    ft_init(t_table *data);
void    error_w(char *str);
void    create_threads(t_table *data);
long    get_time(void);
void    *philosopher_routine(void *data);
void    set_long(pthread_mutex_t *mtx,long *dest, long value);
long    get_long(pthread_mutex_t *mtx, long value);
void    ft_write(char *str, t_philo *philo);
void    set_bool(pthread_mutex_t *mtx, bool *dest, bool m);
void    monitor(t_table *data);
void    usslepp(long x);
void    is_sleeping(t_philo *philo);
void    is_eating(t_philo *philo);
bool get_bool(pthread_mutex_t *mtx, bool value);
#endif // PHILO_H