CC = "g++"
ARGS = -std=gnu++11 -Wall
#LINKFLAGS = " "

DIRS = ./lexical/ ./utf8/ ./conversions/
OBJ_FILES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.o))

build: main.o
	${CC} ${ARGS} -o pp-tokens main.o ${OBJ_FILES}

main.o: build_obj_files
	${CC} ${ARGS} -c main.cpp 

#
# recursively call make in each subdirectory listed in "DIRS"
build_obj_files:
	for DIR in $(DIRS); do (cd $$DIR; make CC=${CC} ARGS=${ARGS}); done
	
clean:
	clear
	\rm -f pp-tokens
	\rm -f *.o
	-for dir in $(DIRS); do (cd $$dir; \rm -rf *.o *~); done
