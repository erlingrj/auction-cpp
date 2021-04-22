CPPFLAGS=
LDFLAGS=--std=c++17 -lstdc++fs
CC=g++


all:
	$(CC) $(CPPFLAGS) main.cpp utils.cpp AuctionSolver.cpp -o run.x $(LDFLAGS)

debug:
	$(CC) $(CPPFLAGS) -g main.cpp utils.cpp AuctionSolver.cpp -o run.x $(LDFLAGS)
