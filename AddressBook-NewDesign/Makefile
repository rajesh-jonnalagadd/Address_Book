###########################################   OPTION SETTING ###########################################

OUTPUT =  addressBook
CCOMPILE = gcc

LINK = gcc

LINKOPTION += -o $(OUTPUT)
INCLUDEDIR += -I.

INCLUDEDIR += -I ../Include/contact.h
INCLUDEDIR += -I ../Include/populate.h
INCLUDEDIR += -I ../Include/colour.h
INCLUDEDIR += -I ../Include/file.h

OBJS += File/file.o
OBJS += Populate/populate.o
OBJS += Contact/contact.o

OBJS += main.o

#########################################	OPTION END	 ##############################################


$(OUTPUT):$(OBJS) 

	$(LINK) $(LINKOPTION)  $(OBJS) 

clean: 
	rm -f $(OBJS)
	rm -f $(OUTPUT)

all: clean $(OUTPUT)
.PRECIOUS:%.cpp %.cc %.cxx %.c 
.SUFFIXES:
.SUFFIXES: .cpp .cc .cxx .c  .o

.cpp.o:
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cpp
	
.cc.o:
	$(CCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cc

.cxx.o:
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cxx

.c.o:
	$(CCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR) $*.c


#######################################################################################################	
