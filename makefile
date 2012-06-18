CXX = g++
CXXFLAGS = -g -Wall
OBJECTS = straightsTestHarness.o Command.o Card.o Deck.o Player.o Game.o Table.o Strategy.o StrategyHuman.o StrategyComputer.o
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

straightsTestHarness.o : straightsTestHarness.cpp Game.h
	${CXX} ${CXXFLAGS} -c straightsTestHarness.cpp

Command.o : Command.cpp Command.h
	${CXX} ${CXXFLAGS} -c Command.cpp

Card.o : Card.cpp Card.h
	${CXX} ${CXXFLAGS} -c Card.cpp

Deck.o : Deck.cpp Deck.h Card.h
	${CXX} ${CXXFLAGS} -c Deck.cpp

Player.o : Player.cpp Player.h Hand.h Table.h Strategy.h StrategyHuman.h StrategyComputer.h
	${CXX} ${CXXFLAGS} -c Player.cpp

Game.o : Game.cpp Game.h Deck.h Player.h Table.h
	${CXX} ${CXXFLAGS} -c Game.cpp

Table.o : Table.cpp Table.h Card.h
	${CXX} ${CXXFLAGS} -c Table.cpp

Strategy.o : Strategy.cpp Strategy.h Player.h
	${CXX} ${CXXFLAGS} -c Strategy.cpp

StrategyHuman.o : StrategyHuman.cpp StrategyHuman.h Strategy.h
	${CXX} ${CXXFLAGS} -c StrategyHuman.cpp

StrategyComputer.o : StrategyComputer.cpp StrategyComputer.h Strategy.h
	${CXX} ${CXXFLAGS} -c StrategyComputer.cpp

clean :
	rm *.o
	rm straights
