NAME = authentication
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror

AUTH_DIR = ./auth/
APP_DIR = ./app/

INCLUDES = -I./ -I$(AUTH_DIR) -I$(APP_DIR)

SRCS = $(AUTH_DIR)transform.cpp $(APP_DIR)application.cpp use_and_test.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -c $< -o $@

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
