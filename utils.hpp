#ifndef __AUCTION_UTILS_HPP__
#define __AUCTION_UTILS_HPP__

#include <vector>
#include <string>


std::vector<std::vector<int>> parse_csv(std::string path);

int align_to_rows(std::vector<std::vector<int>> rew, uint8_t *buf);

int allocate_reward(std::vector<std::vector<int>> rew, uint64_t *buf);

#endif