#include "Auction.hpp"
#include <iostream>
#include <deque>
#include <numeric>
#include <algorithm>


using namespace std;

template <typename T>
void print_vector(vector<T> &v) {
    for (auto a: v) {
        cout <<a <<", ";
    }
}

void print_queue(deque<int> &q) {
    for (auto a: q) {
        cout <<a <<", ";
    }
}


template <typename T>
void print_matrix(std::vector<std::vector<T>> &m) {
    for (auto row: m) {
        print_vector<T>(row); cout<<endl;
    }
}


template <typename T>
vector<size_t> sort_indices(const vector<T> &v) {
    // initialize original index locations
    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values 
    stable_sort(idx.begin(), idx.end(),
    [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});

  return idx;
}

//template <class T>
vector<int> auction(vector<vector<int> > rewards, int epsilon) {
    
    #ifdef DEBUG
        cout <<"Starting Auction algorithm" <<endl;
    #endif

    int n_objects = rewards[0].size();
    int n_agents = rewards.size();

    #ifdef DEBUG
        cout <<"n_objects=" <<n_objects <<" n_agents=" <<n_agents <<endl;
    #endif

    // Initialize data structures holding the running results
    vector<int> prices(n_objects, 0);
    vector<int> object_assignments(n_objects, -1);
    vector<int> agent_assignments(n_agents,-1);
    deque<int> unassigned;
    for (int i = 0; i<n_agents; i++) {
        unassigned.push_back(i);
    }


    // Main loop running until we have no more unassigned agents
    int n_iterations = 0;
    while(unassigned.size() > 0) {
        n_iterations++;

        #ifdef DEBUG
            cout <<"iter:" <<n_iterations <<" Remaining agents: "; print_queue(unassigned); cout <<endl;
        #endif
        // Step 1: Dequeue the first agent and calculate his rewards for the different objects
        int curr_agent = unassigned.front(); unassigned.pop_front(); //TODO: Use a real stack-based container
        vector<int> curr_rewards = rewards[curr_agent];
        vector<int> benefits(n_objects, -1);
        #ifdef DEBUG
            cout << "Pick agent=" <<curr_agent <<" Rewards= "; print_vector<int>(curr_rewards); cout<<endl;
        #endif

        std::transform(curr_rewards.begin(), curr_rewards.end(), prices.begin(), benefits.begin(), std::minus<int>());

        #ifdef DEBUG
            cout << "benefits = "; print_vector(benefits); cout <<endl;        
        #endif

        // Step 2: Find the two objects with the highest benefit
        vector<size_t> benefit_indices_sorted = sort_indices(benefits);
        int highest_idx = benefit_indices_sorted[0];
        int sec_highest_idx = 0;
        if (benefit_indices_sorted.size() > 1) {
            sec_highest_idx = benefit_indices_sorted[1];
        }
        if (benefits[highest_idx] <= 0) {
            #ifdef DEBUG
                cout << "No benefit found" <<endl;
            #endif
            continue;
        }

        #ifdef DEBUG
            cout <<"Highest: " <<highest_idx <<" Second highest:" <<sec_highest_idx <<endl;
        #endif

        // Step 3: Find the owner of the object. Re-assign the new owner and enqueue the old
        int old_owner = object_assignments[highest_idx];
        int old_price = prices[highest_idx];
        int price_delta;
        if (benefits[sec_highest_idx] >= 0 && benefit_indices_sorted.size() > 1) {
            price_delta = benefits[highest_idx] - benefits[sec_highest_idx];
            if (price_delta == 0) {
                price_delta += epsilon;
            }
        } else {
            price_delta = benefits[highest_idx];
        }
        prices[highest_idx] = old_price + price_delta;
        object_assignments[highest_idx] = curr_agent;
        agent_assignments[curr_agent] = highest_idx;
        if (old_owner >= 0) {
            #ifdef DEBUG
                cout <<"Dequeing old agent=" <<old_owner <<endl;
            #endif
            agent_assignments[old_owner] = -1;
            unassigned.push_back(old_owner);
        }

        #ifdef DEBUG
            cout <<"new price = " <<old_price+price_delta <<endl;
        #endif
    }

    return object_assignments;

}


#include <fstream>
#include <string>
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