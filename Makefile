CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = a5
OBJECTS = main.o subject.o game.o observer.o textViewer.o graphicsViewer.o commandInterpreterImpl.o xWindow.o commandInterpreter.o board.o cell.o block.o iBlock.o jBlock.o lBlock.o oBlock.o sBlock.o zBlock.o tBlock.o starBlock.o level.o level0.o level1.o level2.o level3.o level4.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
