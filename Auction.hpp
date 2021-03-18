#ifndef __AUCTION_HPP__
#define __AUCTION_HPP__

#include <vector>
#include <string>

//template <typename T>
std::vector<int> auction(std::vector<std::vector<int> > rewards, int epsilon);

template <typename T>
void print_vector(std::vector<T> &v);


template <class T>
void print_matrix(std::vector<std::vector<T>> &m);


std::vector<std::vector<int>> parse_csv(std::string path);

#endif