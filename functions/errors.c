/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:50:39 by alancel           #+#    #+#             */
/*   Updated: 2021/02/02 20:21:30 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

int		kick_error(int err_num)
{
	if (err_num == 1)
		write(1, "wrong arguments", 15);
	if (err_num == 2)
		write(1, "wrong map or defines", 20);
	if (err_num == 3)
		write(1, "memory error", 12);
	exit(1);
	return (0);
}
