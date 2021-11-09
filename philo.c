#include "struct.h"

size_t	ft_time(void)
{
	struct timeval	tv;
	size_t			time_in_milli;

	gettimeofday(&tv, NULL);
	time_in_milli = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_milli);
}

int      check_syntax(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j] != '\0')
        {
            if (!ft_isdigit(av[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}
//initialize general information
t_arg    *get_argument(int ac, char **av)
{
    t_arg *argument;

    argument = (t_arg *)malloc(sizeof(t_arg));
    if (!argument)
        return (NULL);
    if (!check_syntax(av))
    {
        printf("incorrect syntax\n");
        return (NULL);
    }
    argument->number_philo = ft_atoi(av[1]);
    argument->time_to_die = ft_atoi(av[2]);
    argument->time_to_eat = ft_atoi(av[3]);
    argument->time_to_sleep = ft_atoi(av[4]);
    if(ac == 6)
        argument->number_meals = ft_atoi(av[5]);
    else
        argument->number_meals = -1;
    return(argument);
}

// initialize philo information
void     init_philos(t_table *table)
{
    int     i;

    table->philos = malloc(sizeof(t_philo) * table->args->number_philo);
    if (!table->philos)
        return ;
    i = 0;
    while (i < table->args->number_philo)
    {
        table->philos[i].id = i + 1;
        table->philos[i].meals_number = 0;
        table->philos[i].last_meal = ft_time();
        pthread_mutex_init(&( table->philos[i].eating), NULL);
        table->philos[i].table = table;
        i++;
    }
}

// initialize forks as a mutex's
void    init_forks(t_table *table)
{
    int i;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->args->number_philo);
    if (!table->forks)
        return;
    i = 0;
    while (i < table->args->number_philo)
    {
        pthread_mutex_init(table->forks + i, NULL);
        i++;
    }
}
void    delay(size_t delay)
{
    size_t beginning;

    beginning = ft_time();
    while ((ft_time() - beginning) < delay)
        usleep(60);
}

void    print_msg(t_philo *philo, char *color, char *msg)
{
    pthread_mutex_lock(&(philo->table->print));
    write(1, color, ft_strlen(color));
    ft_putnbr(ft_time() - philo->table->t0);
    write (1, " ", 1);
    ft_putnbr(philo->id);
    write(1, msg, ft_strlen(msg));
    write(1, KNRM, ft_strlen(color));
    pthread_mutex_unlock(&(philo->table->print));
}

void    get_left_right(t_philo *philo, int *left, int *right)
{
    *left = philo->id - 1;
    *right = philo->id % philo->table->args->number_philo;
}

void    *routine(void *philo)
{
    int left;
    int right;
    if (((t_philo*)philo)->id % 2 == 0)
        usleep(200);
    while (1)
    {
        get_left_right(philo, &left, &right);
        pthread_mutex_lock(((t_philo*)philo)->table->forks + left);
        print_msg(philo, KBLU, TAKE_FORK);
        pthread_mutex_lock(((t_philo*)philo)->table->forks + right);
        print_msg(philo, KBLU, TAKE_FORK);
        print_msg(philo, KGRN, EATING);
        ((t_philo*)philo)->is_eating = 1;
        pthread_mutex_lock(&((t_philo*)philo)->eating);
        ((t_philo*)philo)->last_meal = ft_time();
        delay(((t_philo*)philo)->table->args->time_to_eat);
        ((t_philo*)philo)->is_eating = 0;
        ((t_philo*)philo)->meals_number++;
        pthread_mutex_unlock(&((t_philo*)philo)->eating);
        pthread_mutex_unlock(((t_philo*)philo)->table->forks + left);
        pthread_mutex_unlock(((t_philo*)philo)->table->forks + right);
        print_msg(philo, KYEL, SLEEPING);
        delay(((t_philo*)philo)->table->args->time_to_sleep);
        print_msg(philo, KMAG, THINKING);
    }

}
void      create_threads(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->args->number_philo)
        pthread_create(&(table->philos[i].index), NULL, &routine, table->philos + i);
}