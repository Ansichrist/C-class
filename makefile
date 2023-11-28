#  set this in Build.sh
#  MK_IO_BITNESS = [x86, x64]
#  MK_IO_OS = [Lin, MCBC]


########################### VARIABLES ############################

TARGET      = KLS_LIB
COMPILER    = gcc
C_RELEASE   = -c -O3 -Wall
C_DEBUG     = -ggdb -c -Wall
C_FLAGS     = $(C_RELEASE)
C_FLAGS     = $(C_DEBUG)
LD_FLAGS    =
SOURCES     =
OBJECTS     =
OBJECTS_ADD =

##################################################################

LD_FLAGS += -lm
LD_FLAGS += -lc
LD_FLAGS += -lrt

##################################################################

SOURCES += main.c

##################################################################

OBJECTS += $(SOURCES:.c=.o)

##################################################################

all: $(SOURCES) $(TARGET)

##################################################################

$(TARGET): $(OBJECTS) $(OBJECTS_ADD)
	$(COMPILER) $(LD_FLAGS) $(OBJECTS) $(OBJECTS_ADD) -o $(TARGET)

.c.o:
	$(COMPILER) $(C_FLAGS) $< -o $@

##################################################################

rmo:
	rm $(OBJECTS)

clean:
	rm $(OBJECTS) $(TARGET) *.map

