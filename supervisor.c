#include "struct.h"

int     check_death(t_table *t)
{
    int i;
    size_t cur_time;

    i = -1;
    while (++i < t->args->number_philo)
    {
        if (t->philos[i].is_eating == 0)
        {
            cur_time = ft_time();
            if (cur_time - t->philos[i].last_meal >= t->args->time_to_die)
            {
                pthread_mutex_lock(&t->print);
                write(1, KRED, ft_strlen(KRED));
                ft_putnbr(ft_time() - t->t0);
                write (1, " ", 1);
                ft_putnbr(t->philos[i].id);
                write(1, DIED, ft_strlen(DIED));
                return (1);
            }
        }
    }
    return 0;
}

int     check_meals(t_table *t)
{
    int i;
    int r;

    i = -1;
    r = 0;
    if (t->args->number_meals != -1)
    {
        while (++i < t->args->number_philo)
        {
            if (t->philos[i].meals_number >= t->args->number_meals)
                r++;
        }
        if (r == t->args->number_philo)
        {
            pthread_mutex_lock(&t->print);
            write(1, KCYN, ft_strlen(KCYN));
            write(1, "all philosopher eat at least ", 29);
            ft_putnbr(t->args->number_meals);
            write(1, "\n", 1);
            return (r);
        }
    }
    return (0);
}

void    *supervisor(void *table)
{
    t_table *t;

    t = (t_table*)table;

    create_threads(t);
    usleep(200);
    while (1)
    {
        if (check_death(t))
            return (NULL);
        if (check_meals(t))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}