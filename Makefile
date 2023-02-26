FT_NAME = ft_test
STD_NAME = std_test

STD = -std=c++98
COMPILE = c++ -Wall -Werror -Wextra

FT_SRCS = ./test/ft_main.cpp
STD_SRCS = ./test/std_main.cpp

FT_OBJS = $(FT_SRCS:.cpp = .o)
STD_OBJS = $(STD_SRCS:.cpp = .o)

all : $(FT_NAME) $(STD_NAME)

$(FT_NAME) : $(FT_OBJS)
	$(COMPILE) $(STD) $(FT_OBJS) -o $(FT_NAME)

$(STD_NAME) : $(STD_OBJS)
	$(COMPILE) $(STD) $(STD_OBJS) -o $(STD_NAME)

%.o : %.cpp
	$(COMPILE) $(STD) -c $< -o $@

clean :
	rm -rf $(FT_OBJS) $(STD_OBJS)

fclean :
	make clean
	rm -rf $(FT_NAME) $(STD_NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re