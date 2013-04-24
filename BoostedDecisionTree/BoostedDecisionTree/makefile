.SUFFIXES:.cpp
.cpp.o:
	$(CPP) $(INCLUDES) $(CFLAGS) -c $< -o $(ODIR)/$@

CPP=g++
INCLUDES=-I.:/opt/local/include/
LDFLAGS=-L/opt/local/lib
LIBRARIES=-lboost_program_options-mt
ODIR= obj
EXEC= boost_tree
OBJS= #Instance.o stringutil.o


default:all

MAIN_SRC = main.cpp
MAINOBJ = $(MAIN_SRC:.cpp=.o)

$(MAINOBJ) : $(OBJS)

$(EXEC) : $(MAINOBJ)
	$(CPP) -o $(EXEC) $(ODIR)/*.o $(MAINOBJ) $(INCLUDES) $(LDFLAGS) $(LIBRARIES)

exec:$(EXEC)


all: exec
	

clean:
	rm -rf $(OBJ)/* $(EXEC)
