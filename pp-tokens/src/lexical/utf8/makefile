
build: encoded_value.o decoder.o encoder.o octet.o

encoded_value.o:
	${CC} ${ARGS} -c encoded_value.cpp

decoder.o: encoded_value.o
	${CC} ${ARGS} -c decoder.cpp

encoder.o: encoded_value.o
	${CC} ${ARGS} -c encoder.cpp

octet.o:
	${CC} ${ARGS} -c octet.cpp
