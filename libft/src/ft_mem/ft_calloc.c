#include "../../inc/libft.h"

void	*ft_calloc(size_t nbe, size_t size)
{
	char	*zero;
	size_t	i;

	i = 0;
	if (nbe && (nbe * size) / nbe != size)
		return (NULL);
	zero = (char *)malloc(nbe * size);
	if (!zero)
		return (NULL);
	while (i < size * nbe)
		zero[i++] = 0;
	return (zero);
}
