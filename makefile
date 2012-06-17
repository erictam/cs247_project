CXX = g++
CXXFLAGS = -g -Wall
OBJECTS = straightsTestHarness.o Command.o Card.o Deck.o Player.o PlayerHuman.o PlayerComputer.o Hand.o Game.o Table.o
EXEC = straight

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

Player.o : Player.cpp Player.h Hand.h Table.h
	${CXX} ${CXXFLAGS} -c Player.cpp

PlayerHuman.o : PlayerHuman.cpp PlayerHuman.h Player.h
	${CXX} ${CXXFLAGS} -c PlayerHuman.cpp

PlayerComputer.o : PlayerComputer.cpp PlayerComputer.h Player.h
	${CXX} ${CXXFLAGS} -c PlayerComputer.cpp

Hand.o : Hand.cpp Hand.h Card.h
	${CXX} ${CXXFLAGS} -c Hand.cpp

Game.o : Game.cpp Game.h Deck.h Player.h Table.h
	${CXX} ${CXXFLAGS} -c Game.cpp

Table.o : Table.cpp Table.h Card.h
	${CXX} ${CXXFLAGS} -c Table.cpp

clean :
	rm *.o
	rm straight
