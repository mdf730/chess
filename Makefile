CMP = g++
CLASS = finalclass
MAIN = final
EXEC = go
FLAGS = -std=c++11 -lX11

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(FLAGS) $(MAIN).o gfxnew.o $(CLASS).o -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) $(FLAGS) -c $(CLASS).cpp -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) $(FLAGS) -c $(MAIN).cpp -o $(MAIN).o

clean:
	rm $(CLASS).o $(MAIN).o
	rm $(EXEC)