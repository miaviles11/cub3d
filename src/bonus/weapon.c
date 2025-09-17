#include "../../include/cub3d.h"

#define WFIRE_TICKS 6
#define WEAPON_SCALE 2

static t_img	*g_idle;
static t_img	*g_fire;
static int		g_fire_timer;

static int	load_img(void *mlx, const char *p, t_img *out)
{
	void	*ptr;

	ft_bzero(out, sizeof(t_img));
	ptr = mlx_xpm_file_to_image(mlx, (char *)p, &out->w, &out->h);
	if (!ptr)
		return (-1);
	out->ptr = ptr;
	out->data = (int *)mlx_get_data_addr(ptr, &out->bpp,
			&out->line_len, &out->endian);
	if (!out->data)
		return (-1);
	return (0);
}

static void	lazy_init(t_cub *c)
{
	static int	inited;
	static t_img	idle;
	static t_img	fire;

	if (inited)
		return ;
	if (load_img(c->mlx, "./assets/ui/weapon_idle.xpm", &idle))
		return ;
	if (load_img(c->mlx, "./assets/ui/weapon_fire.xpm", &fire))
		return ;
	g_idle = &idle;
	g_fire = &fire;
	g_fire_timer = 0;
	inited = 1;
}

void	weapon_on_click(t_cub *c)
{
	(void)c;
	lazy_init(c);
	if (g_idle && g_fire)
		g_fire_timer = WFIRE_TICKS;
}

static void	blit_scaled(t_img *dst, t_img *src, int ox, int oy, int sw, int sh)
{
	int	pd;
	int	ps;
	int	x;
	int	y;
	int	sx;
	int	sy;

	if (!dst || !src || !dst->data || !src->data)
		return ;
	pd = dst->line_len / 4;
	ps = src->line_len / 4;
	y = 0;
	while (y < sh)
	{
		if (oy + y >= 0 && oy + y < dst->h)
		{
			x = 0;
			sy = (y * src->h) / sh;
			while (x < sw)
			{
				if (ox + x >= 0 && ox + x < dst->w)
				{
					sx = (x * src->w) / sw;
					if ((src->data[sy * ps + sx] & 0x00FFFFFF) != 0)
						dst->data[(oy + y) * pd + (ox + x)]
							= src->data[sy * ps + sx];
				}
				++x;
			}
		}
		++y;
	}
}

void	weapon_draw(t_cub *c)
{
	int		sw;
	int		sh;
	int		ox;
	int		oy;
	t_img	*frame;

	lazy_init(c);
	if (!g_idle || !g_fire)
		return ;
	frame = (g_fire_timer > 0) ? g_fire : g_idle;
	sw = frame->w * WEAPON_SCALE;
	sh = frame->h * WEAPON_SCALE;
	ox = c->screen.w - sw;
	oy = c->screen.h - sh;
	blit_scaled(&c->screen, frame, ox, oy, sw, sh);
	if (g_fire_timer > 0)
		g_fire_timer--;
}
