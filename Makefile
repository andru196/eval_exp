NAME = calc

$(NAME):
	@gcc -c 1.c fn_calc.c
	@gcc -o $(NAME) 1.o fn_calc.o
clean:
	rm -rf *.o
fclean:
	rm -rf $(NAME)
