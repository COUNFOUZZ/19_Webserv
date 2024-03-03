NAME = Webserv
OBJS_DIR = objs
FILES = main.cpp Webserv.cpp
SRCS = $(FILES)
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
CFLAGS = -Wall -Wextra -Werror -g
CPPFLAGS = -std=c++98

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	c++ $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.cpp
	c++ $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re