# .SUFFIXES:.cpp
# .cpp.o:
# 	$(CPP) $(INCLUDES) $(CFLAGS) -c $< -o $(ODIR)/$@

#compile flags
CPP=g++
INCLUDES=-I.:/opt/local/include/
LDFLAGS=-L/opt/local/lib
LIBRARIES=-lboost_program_options-mt -lboost_serialization-mt

#directories
ODIR=obj
TEST_DIR= src
BIN_DIR=bin
SRC_DIR = src

#execs
EXEC= boost_tree
TEST_EXEC = test

#src objs
_SRCS = data_processor.cpp math_util.cpp matrix_util.cpp  stump_classifier.cpp boost_classifier.cpp feature_hashing_classifier.cpp boost_tree_helper.cpp murmurhash.cpp #classifier.cpp
SRCS = $(patsubst %,$(SRC_DIR)/%,$(_SRCS))
_OBJS = $(_SRCS:.cpp=.o)
OBJS=  $(patsubst %,$(ODIR)/%,$(_OBJS))
SRC_HDRS = $(SRCS:.cpp=.h)

DEPDIR = .deps
MAKEDEPEND = touch $(DEPDIR)/$*.d && makedepend $(CPPFLAGS) -f $(DEPDIR)/$*.d $<

df = $(DEPDIR)/$(*F)

$(ODIR)/%.o :$(SRC_DIR)/%.cpp
	@$(MAKEDEPEND); \
	cp $(df).d $(df).P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P; \
	rm -f $(df).d
	$(CPP) -c $< $(INCLUDES) $(CFLAGS) -o $@ 

$(TEST_DIR)/%.o:$(TEST_DIR)/%.cpp
	@$(MAKEDEPEND); \
	cp $(df).d $(df).P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P; \
	rm -f $(df).d
	$(CPP) -c $< $(INCLUDES) $(CFLAGS) -o $@ 

-include $(SRCS:%.cpp=$(DEPDIR)/%.P)	
# %.o : %.c
# 	$(COMPILE.c) -MD -o $@ $<
# 	@cp $*.d $*.P; \
# 	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
# 	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
# 	rm -f $*.d



MAIN_SRC = $(SRC_DIR)/main.cpp
MAINOBJ = $(ODIR)/main.o

TEST_SRC = $(TEST_DIR)/test.cpp 
TESTOBJ = $(TEST_DIR)/test.o


default:all
	
$(MAINOBJ) : $(OBJS)
$(TESTOBJ) : $(OBJS)
 
run_test:test
	$(BIN_DIR)/test
	
test:$(TESTOBJ)
	$(CPP) -o $(BIN_DIR)/$(TEST_EXEC) $(OBJS) $(TESTOBJ) $(INCLUDES) $(LDFLAGS) $(LIBRARIES)

$(EXEC) : $(MAINOBJ)
	$(CPP) -o $(BIN_DIR)/$(EXEC) $(OBJS) $(MAINOBJ) $(INCLUDES) $(LDFLAGS) $(LIBRARIES)

exec:$(EXEC)

all: exec

clean:
	rm -rf $(ODIR)/*.o $(BIN_DIR)/$(EXEC) $(BIN_DIR)/$(TEST_EXEC) 
# DO NOT DELETE
