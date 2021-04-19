#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putchar(char c)
{
		write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = nbr * (-1);
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
}

int		deal_key(int key, void *param)
{
	ft_putchar('#');
	ft_putnbr(key);
	return (0);
}

typedef struct	s_data
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

int		main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "cub3D");
	data.img = mlx_new_image(mlx_ptr, 600, 600);
	// my_mlx_pixel_put(mlx_ptr, 350,350, 16777215);
	mlx_pixel_put(mlx_ptr, win_ptr, 250,250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
