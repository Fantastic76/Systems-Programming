CXX      = g++
CXXFLAGS = -O2 -std=c++17
SRC      = $(wildcard *.cpp)

# make        -> builds app_deque (std::deque)
# make list   -> builds app_list  (std::list)
all: app_deque
app_deque: $(SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@
list: app_list
app_list: $(SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -DUSE_LIST $(SRC) -o $@
clean:
	rm -f app_deque app_list
