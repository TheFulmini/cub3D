#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(1, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	
	i = n;
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i = i * -1;
	}
	if (i > 0)
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putnbr_fd(i % 10, fd);
	}
	else
		ft_putchar_fd( i + 48, fd);

}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return;
	while (*s)
		ft_putchar_fd(*s++, fd);
}


int	deal_key(int key, void *param)
{	
	//if (key > 0)
	//	ft_putnbr_fd(key, 1);

	//mlx_pixel_put(mlx_ptr, win_ptr,
	//char k;
	//k = ft_putnbr_fd(key, 1);
	//char *k;
	//k = atoi(key);
		
	ft_putchar_fd('K', 1);
	return (0);
}




int	main()
{
	int	n;
	void	*mlx_ptr;
	void	*win_ptr;

	n = 200;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "first VM try");
	while (n++ < 300)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, 250,n , 0xFFFFFF);
	}
	mlx_key_hook(win_ptr, deal_key,(void *)0 );
	
	mlx_loop(mlx_ptr);
}

