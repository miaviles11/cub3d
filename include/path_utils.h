/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:56 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/17 17:33:59 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_UTILS_H
# define PATH_UTILS_H

/* duplica la parte “directorio” de una ruta (sin el nombre del fichero)     */
char	*ft_dirname(const char *path);

/* une dir + "/" + file  →  nuevo malloc                                      */
char	*path_join(const char *dir, const char *file);
char	*ft_path_parent(const char *dir);           /* dev. ".." */
int		file_exists(const char *path);

#endif
