#include "AuctionSolver.hpp"
#include <experimental/filesystem>
#include <iostream>
#include "utils.hpp"
using namespace std;
int main() {
    std::vector<std::vector<int> > reward_matrix {
       {7,   51,  52,  87,  38,  60,  74,  66,   0,  20},
       {50,  12,   0,  64,   8,  53,   0,  46,  76,  42},
       {27,  77,   0,  18,  22,  48,  44,  13,   0,  57},
       {62,   0,   3,   8,   5,   6,  14,   0,  26,  39},
       {0,   97,   0,   5,  13,   0,  41,  31,  62,  48},
       {79,  68,   0,   0,  15,  12,  17,  47,  35,  43},
       {76,  99,  48,  27,  34,   0,   0,   0,  28,   0},
       {0,   20,   9,  27,  46,  15,  84,  19,   3,  24},
       {56,  10,  45,  39,   0,  93,  67,  79,  19,  38},
       {27,   0,  39,  53,  46,  24,  69,  46,  23,  1}
    };


    int epsilon = 1;
    std::vector<int> object_assignments = auction(reward_matrix, epsilon);
    cout << "done" <<endl;
    print_vector(object_assignments); cout <<endl;


    string path = "resources/test_problems8bit";
    for (const auto & entry : experimental::filesystem::directory_iterator(path)) {
        auto p = string(entry.path().string());
        auto rew = parse_csv(p);
        cout <<p <<endl;
        for (auto r: rew) {
           print_vector(r); cout <<endl;
        }

        auto object_assignments = auction(rew,epsilon);
        cout <<"Object assignment" <<endl;
        print_vector(object_assignments);; cout<<endl;
    }




    return 0;
}