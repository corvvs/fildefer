#include "libft.h"

t_list	*ft_lstmap2(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*top;

	if (lst)
	{
		top = ft_lstnew(f(lst->content));
		if (top)
		{
			if (!(lst->next))
				return (top);
			top->next = ft_lstmap(lst->next, f, del);
			if (top->next)
				return (top);
			ft_lstdelone(top, del);
		}
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*top;
	t_list	*next;

	if (!lst)
		return (NULL);
	next = NULL;
	if (lst->next)
	{
		next = ft_lstmap(lst->next, f, del);
		if (!next)
			return (NULL);
	}
	top = ft_lstnew(f(lst->content));
	if (top)
		ft_lstadd_front(&next, top);
	else
		ft_lstclear(&next, del);
	return (top);
}
