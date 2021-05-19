#########################################################################################
#	FileName:		Makefile
#	Author:			LiamNurx
#	Update:			2021.05	
#
#	Description:
#	
#########################################################################################

TARGET = DataStructure

APPPATH = ./app
SRCPATH = ./src
INCPATH = ./inc
LIBPATH = ./lib

PATHINC += -I $(INCPATH)
PATHINC += -I $(LIBPATH)

APPOBJECT += $(APPPATH)/main.o

SRCOBJECT += $(SRCPATH)/linear_list.o

LIBOBJECT += $(LIBPATH)/function_lib.o

ALLOBJECT += $(APPOBJECT)
ALLOBJECT += $(SRCOBJECT)
ALLOBJECT += $(LIBOBJECT)

$(TARGET) : $(ALLOBJECT)
	gcc -o $(TARGET) $^
	@echo !****************************************************************!
	@echo -- Compiled Success!
	@echo -- Excuting -make clean- to delete all *.o files right now?
	@echo !****************************************************************!

%.o : %.c
	gcc -c $(PATHINC) -o $@ $<

.PHONY: clean rm

clean:
	rm -rf $(APPPATH)/*.o
	rm -rf $(SRCPATH)/*.o
	rm -rf $(LIBPATH)/*.o

rm:
	rm -rf $(TARGET)
	rm -rf $(APPPATH)/*.o
	rm -rf $(SRCPATH)/*.o
	rm -rf $(LIBPATH)/*.o

