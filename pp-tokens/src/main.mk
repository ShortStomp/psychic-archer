CXXFLAGS := -std=gnu++11 -Wall

#SUBMAKEFILES :=

TARGET := pp-tokens

#TGT_LDFLAGS := -L${TARGET_DIR}
#TGT_LDLIBS  := -lanimals
#TGT_PREREQS := libanimals.a

SOURCES := main.cpp

SRC_INCDIRS := \
    conversions \
    lexical
