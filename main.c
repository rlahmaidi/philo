#include "struct.h"

void    clean(t_table *t)
{
    int i;

    i = -1;
    pthread_mutex_destroy(&(t->print));
    while (++i < t->args->number_philo)
        pthread_mutex_destroy(&(t->forks[i]));
}

int main(int ac, char **av)
{
    t_table table;

    if (ac == 5 || ac == 6)
    {
        table.t0 = ft_time();
        pthread_mutex_init(&table.print, NULL);
        table.args = get_argument(ac, av);
        if (!table.args)
            return (1);
        init_philos(&table);
        if (!table.philos)
            return (1);
        init_forks(&table);
        if (!table.forks)
            return (1);
        pthread_create(&(table.supervisor), NULL, supervisor, &table);
        pthread_join(table.supervisor, NULL);

    }
    else
    {
        printf("Bad args number\n");
        return (0);
    }
    clean(&table);
    return (0);
}