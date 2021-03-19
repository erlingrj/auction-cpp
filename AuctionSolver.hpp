#ifndef __AUCTION_HPP__
#define __AUCTION_HPP__

#include <vector>
#include <string>

//template <typename T>
std::vector<int> auction(std::vector<std::vector<int> > rewards, int epsilon);


void print_vector(std::vector<int> &v);


template <class T>
void print_matrix(std::vector<std::vector<T>> &m);



#endif