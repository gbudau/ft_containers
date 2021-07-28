NAME = test
NAME_FT = test_ft
NAME_STD = test_std
CPPFLAGS = -Wall -Werror -Wextra -std=c++98 -ansi -pedantic
CXX = clang++

OBJ = main.o
OBJ_FT = main_ft.o
OBJ_STD = main_std.o
DEPS = algorithm.hpp  bst_tree.hpp  functional.hpp  iterator.hpp \
	   list.hpp  map.hpp  memory.hpp  queue.hpp  stack.hpp  \
	   type_traits.hpp  utility.hpp  utils.hpp  vector.hpp

%.o: %.cpp $(DEPS)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(NAME_FT): $(OBJ_FT)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME_FT)

$(NAME_STD): $(OBJ_STD)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME_STD)

.PHONY: clean
clean:
	rm -f $(OBJ) $(OBJ_FT) $(OBJ_STD)

.PHONY: fclean
fclean: clean
	rm -f $(NAME) $(NAME_FT) $(NAME_STD)

.PHONY: re
re: fclean all
