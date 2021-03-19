CPPFLAGS=-g -DDEBUG=true
LDFLAGS=--std=c++17 -lstdc++fs
CC=g++



all:
	$(CC) $(CPPFLAGS) main.cpp utils.cpp AuctionSolver.cpp -o run.x $(LDFLAGS)