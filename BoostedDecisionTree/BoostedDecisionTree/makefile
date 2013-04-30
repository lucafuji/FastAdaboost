.SUFFIXES:.cpp
.cpp.o:
	$(CPP) $(INCLUDES) $(CFLAGS) -c $< -o $(ODIR)/$@

CPP=g++
INCLUDES=-I.:/opt/local/include/
LDFLAGS=-L/opt/local/lib
LIBRARIES=-lboost_program_options-mt -lboost_serialization-mt
ODIR=.
EXEC= boost_tree
SRC = data_processor.cpp math_util.cpp matrix_util.cpp  stump_classifier.cpp boost_classifier.cpp feature_hashing_classifier.cpp boost_tree_helper.cpp murmurhash.cpp #classifier.cpp
SRC_HDR = $(SRC:.cpp=.h)
OBJS=$(SRC:.cpp=.o)

BIN=bin
LIB_UTIL_TARGET = libutil.a
MAIN_SRC = main.cpp
MAINOBJ = $(MAIN_SRC:.cpp=.o)

TEST_SRC = test.cpp 
TESTOBJ = $(TEST_SRC:.cpp=.o)
TEST_EXEC = test

ARCHIVE_OPTIONS = rucsv

default:all

$(OBJS): $(SRC) $(SRC_HDR)

$(LIB_UTIL_TARGET): $(OBJS)
	ar $(ARCHIVE_OPTIONS) $(ODIR)/$(LIB_UTIL_TARGET) $(OBJS)
	
$(MAINOBJ) : $(LIB_UTIL_TARGET)
$(TESTOBJ) : $(LIB_UTIL_TARGET)


run_test:test
	bin/test
	
test:$(TESTOBJ)
	$(CPP) -o $(BIN)/$(TEST_EXEC) $(ODIR)/$(LIB_UTIL_TARGET) $(ODIR)/$(TESTOBJ) $(INCLUDES) $(LDFLAGS) $(LIBRARIES)

$(EXEC) : $(MAINOBJ)
	$(CPP) -o $(BIN)/$(EXEC) $(ODIR)/$(LIB_UTIL_TARGET) $(ODIR)/$(MAINOBJ) $(INCLUDES) $(LDFLAGS) $(LIBRARIES)

exec:$(EXEC)

all: exec

clean:
	rm -rf $(ODIR)/*.o $(ODIR)/*.a  $(BIN)/$(EXEC) 
