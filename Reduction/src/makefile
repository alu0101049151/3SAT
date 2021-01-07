program_NAME := Sat-3Sat
program_CXX_HEADERS := $(wildcard *.h)
program_C_SRCS := $(wildcard *.c)
program_CXX_SRCS = $(wildcard *.cpp)
program_CXX_SRC = $(wildcard *.h)
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)
program_INCLUDE_DIRS := ../include
program_LIBRARY_DIRS :=
program_LIBRARIES :=
CPPFLAGS +=	$(foreach includedir, $(program_INCLUDE_DIRS),-I$(includedir) -g)
LDFLAGS +=	$(foreach librarydir, $(program_LIBRARY_DIRS),-L$(librarydir) -g)
LDFLAGS +=	$(foreach library, $(program_LIBRARIES),-l$(library) -g)

.PHONY: all clean distclean

all:	$(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME) -ggdb -std=c++11

clean:
	rm -f $(program_NAME)
	rm -f $(program_OBJS)

distclean: clean
