#include "philo.h"

void    ft_error(t_params *p)
{
    free(p);
    exit(0);
    return ;
}