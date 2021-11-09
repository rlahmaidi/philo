#ifndef STRUCT_H
#define STRUCT_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
#include <pthread.h>

# define TAKE_FORK " has taken a fork\n"
# define EATING " is eating\n"
# define SLEEPING " is sleeping\n"
# define THINKING " is thinking\n"
# define DIED " died\n"
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

struct s_table;

typedef struct s_arg
{
    int     number_philo;
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    int     number_meals;
}           t_arg;

typedef struct s_philo
{
    pthread_t   index;
    pthread_mutex_t eating;
    int         id;
    int         meals_number;
    size_t      last_meal;
    int         is_eating;
    struct s_table  *table;

}              t_philo;

typedef struct s_table
{
    pthread_t           supervisor;
    t_arg               *args;
    pthread_mutex_t     *forks;
    pthread_mutex_t     print;
    t_philo             *philos;
    size_t              t0;


}               t_table;

t_arg    *get_argument(int ac, char **av);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void    init_philos(t_table *table);
void    init_forks(t_table *table);
void    create_threads(t_table *table);
size_t  ft_time(void);
void	ft_putnbr(int n);
size_t	ft_strlen(char *s);
void    print_msg(t_philo *philo, char *color, char *msg);
void    *supervisor(void *table);
int     check_meals(t_table *t);
int     check_death(t_table *t);
#endif