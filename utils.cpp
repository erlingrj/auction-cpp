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