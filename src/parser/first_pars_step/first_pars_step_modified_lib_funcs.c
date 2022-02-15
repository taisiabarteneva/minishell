#include "../../../libft/libft.h"

char	*ft_strndup(char *str,int len)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (len > i)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_memmove_without_return(void *dest, void *src, size_t len)
{
	size_t			i;
	unsigned char	*new_dest;
	unsigned char	*new_src;

	i = 0;
	new_dest = dest;
	new_src = src;
	if (new_dest > new_src)
	{
		while (len > 0)
		{
			new_dest[len - 1] = new_src[len - 1];
			len--;
		}
	}
	else
	{
		while ((new_dest != NULL || new_src != NULL) && (i < len))
		{
			*new_dest++ = *new_src++;
			i++;
		}
	}
}

int	ft_strchr_index(char *string, int symbol)
{
	int i;

	i = 0;
	if (symbol > 255)
		symbol -= 256;
	while (string[i])
	{
		if (string[i] == symbol)
			return (i);
		i++;
	}
	if (string[i] == symbol)
		return (i);
	return (i);
}