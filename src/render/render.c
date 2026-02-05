/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:13:30 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/05 15:11:13 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Scrittura diretta in memoria molto più veloce di mlx_pixel_put (che comunica con X11 ogni volta)
static void	my_mlx_pixel_put(t_mlx *mlx, int x, int *y, int color)
{
	char	*dst;

	if (x < 0 || x >= mlx->screen_width || *y < 0 || *y >= mlx->screen_height)  // Controllo limiti schermo
		return ;  // Evita scrittura fuori dal buffer (segfault)
	dst = mlx->addr + (*y * mlx->line_length + x * (mlx->bits_per_pixel / 8));  // Calcola offset nel buffer: riga*larghezza + colonna*byte_per_pixel
	*(unsigned int *)dst = color;  // Scrive il colore direttamente in memoria (cast a int per 4 byte ARGB)
	(*y)++;  // Incrementa Y per il prossimo pixel (usato nei loop verticali)
}

// Formula base lodev: line_height = screen_height / distance
// Correzione aspect_ratio previene distorsione su monitor 16:9, 21:9 etc
static void	get_line_to_draw(t_ray *ray, t_mlx *mlx)
{
	double	corrected_height;

	corrected_height = mlx->screen_height * sqrt(mlx->aspect_ratio);  // Corregge altezza per schermi widescreen (evita muri troppo bassi)
	ray->line_height = (int)(corrected_height / ray->perp_wall_dist);  // Altezza muro: più vicino = più alto, più lontano = più basso
	ray->draw_start = -ray->line_height / 2 + mlx->screen_height / 2;  // Inizio linea: centra il muro verticalmente sullo schermo
	if (ray->draw_start < 0)  // Se parte sopra lo schermo
		ray->draw_start = 0;  // Clippa al bordo superiore
	ray->draw_end = ray->line_height / 2 + mlx->screen_height / 2;  // Fine linea: seconda metà del muro centrato
	if (ray->draw_end >= mlx->screen_height)  // Se finisce sotto lo schermo
		ray->draw_end = mlx->screen_height - 1;  // Clippa al bordo inferiore
}

// Determina QUALE colonna della texture usare in base a DOVE il raggio ha colpito il muro
// wall_x rappresenta "quanto lontano lungo il muro" (da 0.0 a 1.0)
static void	set_tex_x_coord(t_ray *ray, t_player *player, t_tex *tex)
{
	double	wall_x;

	if (ray->wall_side == WEST || ray->wall_side == EAST)  // Muro verticale
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;  // Calcola punto di impatto usando coordinata Y
	else  // Muro orizzontale (NORTH o SOUTH)
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;  // Calcola punto di impatto usando coordinata X
	wall_x -= floor(wall_x);  // Prendi solo la parte frazionaria (0.0 - 1.0): posizione dentro la cella
	tex->x = (int)(wall_x * (double)tex->width);  // Scala a coordinate texture (0 a tex_width-1)
	if (ray->wall_side == WEST || ray->wall_side == SOUTH)  // Muri Ovest e Sud
		tex->x = tex->width - tex->x - 1;  // Inverte texture per evitare effetto specchio
}

static void	draw_column(t_ray ray, t_data d, int x, t_tex tex)
{
	int		y;
	int		color;
	int		tex_index;

	y = 0;  // Parte dall'alto dello schermo
	while (y < ray.draw_start)  // Prima del muro
		my_mlx_pixel_put(d.mlx, x, &y, d.map->ceiling_color);  // Disegna ceiling
	while (y <= ray.draw_end)  // Zona del muro
	{
		tex.y = (int)tex.pos;  // Converte posizione texture a coordinata Y intera
		tex.pos += tex.step;  // Avanza nella texture (step = quante righe texture per pixel schermo)
		tex_index = tex.width * tex.y + tex.x;  // Calcola offset nel array texture (riga*larghezza + colonna)
		if (tex_index >= 0 && tex_index < tex.width * tex.height)  // Bounds check
			color = d.mlx->tex[ray.wall_side].addr[tex_index];  // Legge colore dalla texture corretta (NORTH/SOUTH/EAST/WEST)
		my_mlx_pixel_put(d.mlx, x, &y, color);  // Disegna pixel con colore texture
	}
	while (y < d.mlx->screen_height)  // Dopo il muro fino in fondo
		my_mlx_pixel_put(d.mlx, x, &y, d.map->floor_color);  // Disegna floor
}

void	set_pixel_buffer(t_data *d, t_ray *ray, int x)
{
	int		tex_id;
	t_tex	tex;

	tex_id = ray->wall_side;  // Usa wall_side come indice texture (NORTH=0, SOUTH=1, WEST=2, EAST=3)
	tex = d->mlx->tex[tex_id];  // Copia la texture corretta in base al lato del muro colpito
	set_tex_x_coord(ray, d->player, &tex);  // Calcola quale colonna X della texture usare
	get_line_to_draw(ray, d->mlx);  // Calcola altezza muro e dove inizia/finisce sullo schermo
	tex.step = (double)tex.height / (double)ray->line_height;  // Quante righe texture per ogni pixel schermo (scaling verticale)
	tex.pos = (ray->draw_start - d->mlx->screen_height / 2
			+ ray->line_height / 2) * tex.step;  // Posizione iniziale nella texture (gestisce clipping corretto quando muro esce dallo schermo)
	draw_column(*ray, *d, x, tex);  // Disegna la colonna verticale completa
}
