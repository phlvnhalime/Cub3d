/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:59:46 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/23 14:50:57 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Main function structure
1. INITIALISATION
---- Initialize game structure to zero values
---- validate argument count (exactly 2)
---- check file extension (.cub)

2. PARSING
---- read and validate config file
---- parse texture (NO SO WE EA)
---- Parse color (floor and ceiling)
---- validate and store map matrix:
		check wall enclosure
		validate player position
		handle space characters

3. MLX SETUP
---- initialize mlx42
---- create window
---- load textures images to memory
---- initialize player position and direction

4. GAME LOOP SETUP
---- register input hooks/key events (ESC W A S D and Mouse
---- rendering loop

5. CLEANUP
---- free all allocated memory
---- destroy mlx42 images and window
---- close mlx42 connection
---- return proper exit code
*/

int	main(int argc, char **argv)
{
	// t_game	*game;

	verify_args(argc, argv[1]);
	return (0);
}

void	ft_error_exit(char *msg)
{
	printf(RED "Error\n" RESET);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	verify_args(int argc, char *argv)
{
	if (argc != 2)
		ft_error_exit(YELLOW "Usage: './cub3d <cub_file>'" RESET);
	if (ft_strnstr(&argv[1], ".cub", ft_strlen(&argv[1])) == NULL)
		ft_error_exit(YELLOW "Usage: [file] with [.cub] extention" RESET);
}
