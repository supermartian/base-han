#
# Makefile
# martian, 2017-09-16 23:05
#

basehantest: test.o basehan.o
	cc -o basehantest test.o basehan.o

# vim:ft=make
#

