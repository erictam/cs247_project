CXX= g++
#CXXFLAGS = -g `/opt/local/bin/pkg-config gtkmm-2.4 --cflags --libs`
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
OBJS = DeckGUI.o otherworld.o driver.o Subject.o controller.o Game.o Card.o Table.o Player.o Deck.o Strategy.o StrategyHuman.o StrategyComputer.o
EXEC = other

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC)

DeckGUI.o: DeckGUI.h DeckGUI.cc
otherworld.o: otherworld.h otherworld.cc Observer.h
driver.o: otherworld.h driver.cc

clean:
	rm $(EXEC) $(OBJS)
	rm *.o
