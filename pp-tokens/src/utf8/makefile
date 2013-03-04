
build: utf8_encoded_value.o utf8_decoder.o utf8_encoder.o

utf8_encoded_value.o:
	${CC} ${ARGS} -c utf8_encoded_value.cpp

utf8_decoder.o: utf8_encoded_value.o
	${CC} ${ARGS} -c utf8_decoder.cpp

utf8_encoder.o: utf8_encoded_value.o
	${CC} ${ARGS} -c utf8_encoder.cpp
