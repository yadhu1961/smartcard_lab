project=uart_echo

freq=4915200 # 4MHz for accurate baudrate timing

#Frequency needed for the smart card reader
#avrFreq1=3276800 #4MHz for accurate baudrate timing

#avr gcc
CC = avr-gcc
#avr objectcopy
OBJCOPY = avr-objcopy
#avr flashing
avr_programmer=avrdude

#The CFLAGS variable sets compile flags for gcc
#-g                 compile with debug information
#-mmcu=atmega328p   selects the target device
#-std=gnu99         use the C99 standard language definition
CFLAGS = -g -mmcu=atmega644 -std=gnu99 -Wall -Os -Wextra

#flags for flashing the avr board
FLASHFLAGS= -V -Pusb -B10 -cavrispmkII -pm644 -e -U

#OBJFLAG sets the flag for making a elf to hex
OBJFLAG = -j .text -j .data -O ihex

EXECUTABLE = $(project)
SOURCES = ${wildcard *.c}
HEADERS = ${wildcard *.h}
OBJECTS = ${SOURCES:.c=.o}

all: ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS)
	echo $(freq)

