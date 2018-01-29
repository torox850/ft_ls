/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/29 14:35:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/01/29 15:22:01 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_addlink(t_list **begin, t_list *prv, t_list *new, t_list *cur)
{
	if (prv != NULL)
	{
		if (prv->next != NULL)
			new->next = cur;
		prv->next = new;
	}
	else
	{
		new->next = cur;
		(*begin) = new;
	}
}

void	ft_lstsortadd(t_list **begin, t_list *new, t_opt *opt)
{
	t_file	*ifo;
	t_file	*nfo;
	t_list	*prv;
	t_list	*cur;

	ifo = (*begin)->content;
	nfo = new->content;
	cur = (*begin);
	prv = NULL;
	while ((opt->t == 0 &&
		((opt->r == 1 && ft_strcmp(ifo->name, nfo->name) > 0) ||
		(opt->r == 0 && ft_strcmp(ifo->name, nfo->name) < 0))) ||
		(opt->t == 1 && ((opt->r == 1 && ifo->stamp - nfo->stamp < 0) ||
		(opt->r == 0 && ifo->stamp - nfo->stamp > 0))))
	{
		prv = cur;
		if (cur->next)
			cur = cur->next;
		else
			break ;
		ifo = cur->content;
	}
	ft_addlink(begin, prv, new, cur);
}

void	ft_infodel(void *ptr, size_t size, t_opt *opt)
{
	t_file *info;

	info = ptr;
	if (!opt->ug)
		ft_strdel(&(info->name));
	ft_strdel(&(info->cname));
	ft_strdel(&(info->date));
	if (opt->l)
	{
		ft_strdel(&(info->grp));
		ft_strdel(&(info->usr));
		ft_strdel(&(info->lnk));
	}
	ft_strdel(&(info->perm));
	ft_strdel(&(info->rep));
	ft_bzero(ptr, size);
	free(ptr);
	size++;
	ptr = NULL;
}

void	ft_lstd(t_list **alst, void (*del)(void *, size_t, t_opt *), t_opt *opt)
{
	t_list *cur;
	t_list *tmp;

	cur = *alst;
	while (cur != NULL)
	{
		tmp = cur->next;
		del(cur->content, cur->content_size, opt);
		free(cur);
		cur = tmp;
	}
	*alst = NULL;
}
