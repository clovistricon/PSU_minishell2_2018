#include "my.h"

int main(int ac, char **av, char **env)
{
    char **myenv = my_tabcpy(env);

    if (ac > 1)
        my_exec2(&av[1], myenv);
    return (0);
}