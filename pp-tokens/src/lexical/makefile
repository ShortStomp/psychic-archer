
DIRS = ./utf8/
OBJ_FILES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.o))

build: lexical_helper.o lexical_analyzer.o

lexical_helper.o:
	${CC} ${ARGS} -c lexical_helper.cpp

lexical_analyzer.o: build_obj_files
	${CC} ${ARGS} -c lexical_analyzer.cpp ${OBJ_FILES}



#
# recursively call make in each subdirectory listed in "DIRS"
build_obj_files:
	for DIR in $(DIRS); do (cd $$DIR; make CC=${CC} ARGS=${ARGS}); done

clean:
	for dir in $(DIRS); do (cd $$dir; \rm -rf *.o *~); done
