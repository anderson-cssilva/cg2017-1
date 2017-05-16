BINARY=./spaceinvader
MAIN=./SpaceInvader.cpp
INCLUDES=./includes
CCFILES=src/CircleEnemy.cpp src/Enemy.cpp src/Plane.cpp src/Shoot.cpp src/SquareEnemy.cpp src/TriangleEnemy.cpp
CCFLAGS=-lm -lGL -lGLU -lglut -g

all:
	g++ -o $(BINARY) -I$(INCLUDES) $(MAIN) $(CCFILES) $(CCFLAGS)

run:
	$(BINARY)
