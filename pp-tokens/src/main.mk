CXXFLAGS := -std=gnu++11 -Wall -g

SUBMAKEFILES := lexical/lexical.mk \
	lexical/ucn/ucn.mk \
	lexical/utf8/utf8.mk \
	conversions/conversions.mk

TARGET := pp-tokens

SOURCES := main.cpp

#SRC_INCDIRS := \
    conversions \
    lexical
