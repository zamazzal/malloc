make -C libft/	
gcc -Wall -Wextra -Werror  main.c srcs/*.c -I includes -I libft/includes -L libft/ -lft -o malloc	
make -C libft fclean