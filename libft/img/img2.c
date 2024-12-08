/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:16:12 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/30 04:16:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"
#include <stdlib.h>

void	img_destroy(t_img *img)
{
	free(img->px);
	ft_bzero(img, sizeof(t_img *));
}
