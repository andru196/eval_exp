#include "prot.h"

int		ft_atoi(char **str)
{
	int		nbr;

	nbr = 0;
	while (**str >= '0' && **str <= '9')
	{
		nbr = nbr * 10 + (**str - '0');
		(*str)++;
	}
	return (nbr);
}

int	parse_number(char **expr)
{
	int nbr;
	while (**expr == ' ')
		(*expr)++;
	if (**expr == '(')
	{
		(*expr)++;
		nbr = parse_sum(expr);
		if (**expr == ')')
			(*expr)++;
		return (nbr);
	}
	return (ft_atoi(expr));
}

int	parse_factors(char **expr)
{
	int	nbr;
	int	nbr2;
	char	op;

	nbr = parse_number(expr);
	while (**expr)
	{
		while (**expr == ' ')
			(*expr)++;
		op = **expr;
		if (op != '/' && op != '*' && op != '%')
			return (nbr);
		(*expr)++;
		nbr2 = parse_number(expr);
		if (op == '/')
			nbr /= nbr2;
		else if (op == '*')
			nbr *= nbr2;
		else
			nbr %= nbr2;
	}
	return (nbr);
}

int	parse_sum(char **expr)
{
		int	nbr;
		int	nbr2;
		char	op;

		nbr = parse_factors(expr);
		while (**expr)
		{
			while (**expr == ' ')
				(*expr)++;
			op = **expr;
			if (op != '+' && op != '-')
				return (nbr);
			(*expr)++;
			nbr2 = parse_factors(expr);
			if (op == '+')
				nbr += nbr2;
			else
				nbr -= nbr2;
		}
		return (nbr);
}

int	eval_expr(char *expr)
{
	return (parse_sum(&expr));
}
