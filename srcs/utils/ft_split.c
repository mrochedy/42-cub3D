/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:32:44 by hdaher            #+#    #+#             */
/*   Updated: 2024/08/28 15:09:44 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	word;
	int	count;

	i = 0;
	count = 0;
	word = 0;
	while (s[i])
	{
		if ((s[i] != c) && word == 0)
		{
			count++;
			word = 1;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (count);
}

static void	insert_word(char const *s, char c, char **tab, int word)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		tab[word][i] = s[i];
		i++;
	}
	tab[word][i] = '\0';
}

static int	insert_in_tab(char const *s, char c, char **tab, int count)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] != c)
		{
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			tab[count] = (char *)malloc((j + 1) * sizeof(char));
			if (tab[count] == NULL)
				return (ft_free_tab((void **)tab, count), 1);
			insert_word(s + i, c, tab, count);
			i += j - 1;
			count++;
		}
		i++;
	}
	return (tab[count] = NULL, 0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;

	if (s == NULL)
		return (NULL);
	count = 0;
	tab = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (insert_in_tab(s, c, tab, count) == 0)
		return (tab);
	else
		return (NULL);
}
