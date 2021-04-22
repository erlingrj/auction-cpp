#include "utils.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;
vector<int> parse_line(string s){
    vector<int> res;
	string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==','){
			res.push_back(stoi(temp));
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
	res.push_back(stoi(temp));
    return res;
	
}

vector<vector<int>> parse_csv(std::string path) {
    fstream f;
    vector<std::vector<int>> res;
    f.open(path, ios::in);
    if (f.is_open()) {
        string line;
        while(getline(f, line)) {
            res.push_back(parse_line(line));
        } 
    } else {
        throw;
    }
    return res;
}

int align_to_rows(std::vector<std::vector<int>> rew, uint8_t *buf) {
  int buf_idx = 0;

  const int bytesPerMemWord = 8;


  for (int i = 0; i< rew.size(); i++) {
    for(int j = 0; j< rew[i].size(); j++) {
      buf[buf_idx++] = rew[i][j];
    }
    // After a row is finished, pad on zeros. We check the remainder of the index
    int pads_needed = bytesPerMemWord - buf_idx % bytesPerMemWord;
    if (pads_needed > 8) {
      for (int k = 0; k<pads_needed; k++) {
        buf[buf_idx++] = 0x00;
      }
    } else {
      // We are good, the row is already aligned (its 8x8 or 16x16 ...)
    }
  }
  return buf_idx;
}
