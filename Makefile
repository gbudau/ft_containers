NAME = test
NAME_FT = test_ft
NAME_STD = test_std
CPPFLAGS = -Wall -Werror -Wextra -std=c++98 -ansi
CXX = clang++

OBJ = main.o
DEPS = algorithm.hpp  bst_tree.hpp  functional.hpp  iterator.hpp \
	   list.hpp  map.hpp  memory.hpp  queue.hpp  stack.hpp  \
	   type_traits.hpp  utility.hpp  utils.hpp  vector.hpp

%.o: %.cpp $(DEPS)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.PHONY: all
all: $(NAME) $(NAME_FT) $(NAME_STD)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(NAME_FT): $(OBJ)
	$(CXX) $(CPPFLAGS) -D NAMESPACE1=ft -D NAMESPACE2=ft $(OBJ) -o $(NAME_FT)

$(NAME_STD): $(OBJ)
	$(CXX) $(CPPFLAGS) -D NAMESPACE1=std -D NAMESPACE2=std $(OBJ) -o $(NAME_STD)

.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME) $(NAME_FT) $(NAME_STD)

.PHONY: re
re: fclean all
