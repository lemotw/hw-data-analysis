CC = g++
FLAG = -g -std=c++11

COMPILE = main.cpp
OBJDIR = ./obj
LIBOBJDIR = ./obj/lib
LIBDIR = ./lib
LIB_OBJFILES =	apriori.o

APRIORI = apriori

all: $(APRIORI)

$(APRIORI): $(LIB_OBJFILES)
	$(CC) $(COMPILE) -I $(LIBDIR) $(LIBOBJDIR)/*.o -o $(APRIORI)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCompile (main.cpp) as excutable file.\e[0m"

$(LIB_OBJFILES): %.o: $(LIBDIR)/%.cpp $(LIBOBJDIR)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCompile library to object file.\e[0m"
	$(CC) -c $(C_FLAG) $< -o $(LIBOBJDIR)/$@

$(LIBOBJDIR): $(OBJDIR)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCreate object directory(obj/lib)\e[0m"
	mkdir -p $@

$(OBJDIR):
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCreate object directory(obj/)\e[0m"
	mkdir -p $@

clean:
	@echo -e "\e[41m:::\e[0m \e[91mDeleting object file and execute file.\e[0m"
	rm -f $(OBJDIR)/*.o $(TARGET)
