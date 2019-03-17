#include "prot.h"
#include <stdio.h>

char *del_spc(char *str)
{
	char	help;
	char	*rez = str;
	char	*cpy;
	int	i = 0;

	while (*str)
	{
		if (*str == '\n' || *str == '\t' || *str == ' ' || *str == '\v')
		{
			while (*str == '\n' || *str == '\t' || *str == ' ' || *str == '\v')
			{
				str++;
				i++;
			}
			cpy = str;
			while (*cpy)
			{
				help = *(cpy - i);
				*(cpy - i) = *cpy;
				*cpy = help;
				cpy++;
			}
			str -= i;
			i = 0;
		}
		if (*str)
			str++;
	}
	str = rez;
	while (!(*str == '\n' || *str == '\t' || *str == ' ' || *str == '\v'))
		str++;
	*str = '\0';
	return (rez);
}

int	valid_str(char *str)
{
	int	loop;
	char	help;
	char	*cpy;

	loop = 0;
	while (*str)
	{
		if (*str == '(')
			loop++;
		if (*str == ')')
			loop--;
		if (loop < 0 || !(*str == '0' || *str == '1' || *str == '2' || *str == '3' || *str == '4'
					|| *str == '5' || *str == '6' || *str == '7' || *str == '8' ||
					*str == '9' || *str == '-' || *str == '+' || *str == '/'
					|| *str == '*' || *str == '%' || *str == '(' || *str == ')'))
			return (0);
			
		str++;
	}
	if (loop == 0)
		while(*cpy)
		{
			if (*cpy == '*' || *cpy == '/' || *cpy == '%' || *cpy == '+' || *cpy == '-')
			{
				if(*(cpy + 1) == '*' || *(cpy + 1)== '/' || *(cpy + 1) == '%')
					return 6 - write(1, "error\n", 6);
				else if (*(cpy + 1) == '+' || *(cpy + 1) == '-')
					if (*(cpy + 2) == '*' || *(cpy + 2)== '/' ||
						*(cpy + 2) == '%' || *(cpy + 2) == '-' || *(cpy + 2) == '+')
						return 6 - write(1, "error\n", 6);
			}
			cpy++;
		}
		return (1);
	return (0);
}

int	numcounter(char *str)
{
	int i;
	int loop;

	if (*str == '(')
	{
		i = 1;
		loop = 1;
		while (loop)
		{
			if (*(++str) == '(')
				loop++;
			else if (*str == ')')
				loop--;
			str++;
			i++;
		}
		return (i + 1);
	}
	i = 0;
	while (*str && (*str == '0' || *str == '1' || *str == '2' || *str == '3' || *str == '4'
			|| *str == '5' || *str == '6' || *str == '7' || *str == '8' || *str == '9'))
		{
		str++;
		i++;
		}
	return (i);
}

void	replacer(int i, int j, char *str)
{
	char	help;
	char	*buf = malloc (i);
	strncpy(buf, str, i);
	while (j)
	{
		*str = *(str + i);
		str++;
		j--;
	}
	strncpy(str, buf, i);
	free(buf);
	
}

void	accuracy(char *str)
{
	int	i;
	int	j;
	int	flag;
	char	*cpy = str;

	do {
		flag = 0;

		while (*str)
		{
			if (*str == '/')
			{	
				i = numcounter(str + 1);
				if (*(str + 1 + i) != '+' && *(str + 1 + i) != '-'
					&& *(str + 1 + i) != ')' && *(str + 1 + i) && i > 0)
				{
					j =  numcounter(str + i + 2);
					replacer(i + 1, j + 1, str);
					flag = (*(str + i + 2) == '/')? flag : flag + 1;
				}
			}
			str++;
		}
		str = cpy;
	}while (flag > 0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		argv[1] = del_spc(argv[1]);
		if (valid_str(argv[1]))
			{
				accuracy(argv[1]);
				printf("%d",eval_expr(argv[1]));
			}
	}
	printf("\n");
	return (0);
}

