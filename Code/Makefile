
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Directories #
SRCDIR   = src
INCDIR   = include
BUILDDIR = build
BINDIR   = bin

# Output #
NAME = 3SAT

# Remove #
RM  =  rm -rf

# Clean #
CLEAN = $(RM) $(BUILDDIR)/*.o $(BINDIR)/$(NAME)

# Directories #
MKDIR = mkdir -p -- $@


SRCS   = $(wildcard $(SRCDIR)/*.cpp)
OBJS   = $(subst $(SRCDIR)/, $(BUILDDIR)/, $(SRCS:.cpp=.o))
TARGET = $(BINDIR)/$(NAME)

$(TARGET): directories $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CXXFLAGS) $(LFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) -c $< -o $@

directories: $(BUILDDIR) $(BINDIR)

$(BUILDDIR):
	$(MKDIR)
$(BINDIR):
	$(MKDIR)

clean:
	$(CLEAN)
