#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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
	int	key_touched;


	ft_putchar('#');
	ft_putnbr(key);
	key_touched = key;
	return (key);
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
	void	*img;
	int		n;

	n = 600; 

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "cub3D");
	img = mlx_new_image(mlx_ptr, 600, 600);
	// my_mlx_pixel_put(mlx_ptr, 350,350, 16777215);
	while (n-- > 50)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, 250, n, 0xFFFFFF);
	}
	
	int  mykey;
	mykey = mlx_key_hook(win_ptr, deal_key, (void *)0);

/*	mykey = deal_key(int key, 0);
	if (key == 1)
	{
		n = 600;
		while (n-- > 50)
			mlx_pixel_put(mlx_ptr, win_ptr, n, 250, 0xFFFFFF);
	}
	*/
	printf("%d\n", mykey);
	mlx_loop(mlx_ptr);
	return (0);
}
