project=blink_led

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
CFLAGS = -g -DF_CPU=$(avrFreq) -mmcu=atmega644 -std=gnu99 -Wall -Os -Werror -Wextra

#flags for flashing the avr board
FLASHFLAGS= -V -Pusb -B10 -cavrispmkII -pm644 -e -U

#OBJFLAG sets the flag for making a elf to hex
OBJFLAG = -j .text -j .data -O ihex

EXECUTABLE = $(project)
SOURCES = ${wildcard *.c}
HEADERS = ${wildcard *.h}
OBJECTS = ${SOURCES:.c=.o}

all: ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	@echo "========================"
	@echo "source files" $(SOURCES)
	@echo "object files" $(OBJECTS)
	@echo "========================"
	$(CC) $(CFLAGS) -Wa,-ahlmns=$(project).lst -c -o $(SOURCES) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(project).elf $(OBJECTS)
	$(OBJCOPY) $(OBJFLAG) $(project).elf $(project).hex
	@echo "-- Build: " $$(cat buildnumber.num)

# Creeer dependency file met optie -MM van de compiler
depend: $(SOURCES)
	@echo "calling depend"
	$(CC) $(CFLAGS) -Os -c -MM $^ > $@

-include depend

# Buildnumber administration
buildnumber.num: $(OBJECTS)
	@if ! test -f buildnumber.num; then echo 0 > buildnumber.num; fi
	@echo $$(($$(cat buildnumber.num)+1)) > buildnumber.num

# Create a clean environment
.PHONY: clean
clean:
	@echo "============removing binaries================="
	$(RM) $(OBJECTS) $(project).hex $(project).elf $(project).lst
	$(RM) depend
	$(RM) buildnumber.num

.PHONY: program
program:
	@echo "Flashing the program"
	$(avr_programmer) $(FLASHFLAGS) flash:w:$(project).hex

# Clean up dependency file
#.PHONY: clean-depend
#clean-depend: clean
#	$(RM) depend
