/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huit_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlouisia <qlouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:33:21 by qlouisia          #+#    #+#             */
/*   Updated: 2020/03/05 11:45:58 by qlouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/bmp.h"
#include <stdlib.h>

/*
**                 #######################################
**                 ######### convert 8bits color #########
**                 #######################################
**
** Convert R,G,B color in char (format use in BMP) to a uint32 color
** use in display
*/

uint32_t	convert_8bitscolor(char r, char g, char b)
{
	int value;

	value = ((255 & 0xFF) << 24) |
			(((int)r & 0xFF) << 16) |
			(((int)g & 0xFF) << 8) |
			(((int)b & 0xFF) << 0);
	return (value);
}

/*
**                 #######################################
**                 ########### format_data8bit ###########
**                 #######################################
**
** In BMP, pixels[0] = Lower left, we want to have it in Upper Left
*/

void		format_data8bit(char *tmp, t_bmp *bmp)
{
	int				x;
	int				y;
	int				i;
	unsigned char	index;

	i = 0;
	y = bmp->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < bmp->width)
		{
			index = tmp[y * bmp->width + x];
			bmp->data[i] = bmp->palette[index];
			x++;
			i++;
		}
		y--;
	}
}

/*
**                 #######################################
**                 ########### create palette ###########
**                 #######################################
**
** Create a palette from the bmp files informations and convert each color 8bit
** to a 32bits color
*/

int			create_palette(char *tmp, t_bmp *bmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	tmp += bmp->header_size + 14;
	if (bmp->nb_color_palette == 0)
		bmp->nb_color_palette = 256;
	if (!(bmp->palette = (uint32_t *)malloc(sizeof(uint32_t) *
	bmp->nb_color_palette)))
		return (0);
	while (i < bmp->nb_color_palette * 4)
	{
		bmp->palette[j] = convert_8bitscolor(tmp[i + 2], tmp[i + 1], tmp[i]);
		i += 4;
		j++;
	}
	return (1);
}
