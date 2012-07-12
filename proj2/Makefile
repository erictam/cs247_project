CXX= g++
#CXXFLAGS = -g `/opt/local/bin/pkg-config gtkmm-2.4 --cflags --libs`
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags --libs`
OBJS = DeckGUI.o View.o driver.o Subject.o controller.o Game.o Card.o Table.o Player.o Deck.o Strategy.o StrategyHuman.o StrategyComputer.o
EXEC = straights

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC)

DeckGUI.o: DeckGUI.h DeckGUI.cc
View.o: View.h View.cc Observer.h
driver.o: View.h driver.cc

clean:
	rm $(EXEC) $(OBJS)
	rm *.o
