#include "../include/ssl.h"

void			ft_exit_malloc_crash(void)
{
	ft_putendl_fd("malloc can't allocate memory!", STDERR_FILENO);
	exit(FAIL);
}