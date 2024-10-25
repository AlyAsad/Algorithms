#include "the7.h"

// do not add extra libraries here

using namespace std;


void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<float>& infection_scores){
    
    
    int S = network.size();
    
    vector<vector<int>> D(S, vector<int>(S, INT_MAX));
    
    for (int i = 0; i < S; i++) {
        for (auto j : network[i]) {
            D[i][j.first] = j.second; //turning adjacency list to matrix
        }
        D[i][i] = 0; //no loop on node
    }
    
    
    //FLOYD WARSHALL
    for (int k = 0; k < S; k++) {
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < S; j++) {
                
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX && D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
                
            }
        }
    }
    
    int M = INT_MIN;
    
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            if (D[i][j] != INT_MAX)
                M = max(M, D[i][j]);
        }
    }
    
    M++;
    infection_scores.resize(S);
    
    for (int i = 0; i < S; i++) {
        float tot = 0;
        
        for (int j = 0; j < S; j++) {
            if (i == j) continue;  //avoiding same index
            
            if (D[i][j] == INT_MAX) // no path
                tot += M;
            
            else  // path
                tot += D[i][j];
        }
        tot = tot/(float)(S-1);
        infection_scores[i] = 1/tot;
    }
    
    
}


