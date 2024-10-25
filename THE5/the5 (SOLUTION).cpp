#include "the5.h"

// do not add extra libraries here

using namespace std;





void SCC(int &u, const vector<vector<int>> &dep, vector<char> &color, vector<int> &final) {
    
    int size = dep.size();
    color[u] = 'G';
    
    for (int v = 0; v < size; v++) {
        
        if (dep[u][v] == 0) continue; //no adjacency
        
        if (color[v] == 'W')
            SCC(v, dep, color, final);
        
    }
    
    color[u] = 'B';
    final.push_back(u);
    
}


void DFSVisit(int &u, const vector<vector<int>> &dep, vector<char> &color, vector<int> &final, bool &iC) {
    
    int size = dep.size();
    color[u] = 'G';
    
    for (int v = 0; v < size; v++) {
        
        if (dep[v][u] == 0) continue; //no adjacency
        
        if (color[v] == 'W')
            DFSVisit(v, dep, color, final, iC);
        
        
        else if (color[v] == 'G')
            iC = false;
        
    }
    
    color[u] = 'B';
    final.push_back(u);
    
}



void DFS(const vector<vector<int>> &dep, vector<int> &final, bool &iC) {
    
    int size = dep.size();
    vector<char> color(size, 'W');

    for (int u = 0; u < size; u++)
        if (color[u] == 'W')
            DFSVisit(u, dep, color, final, iC);
    
}





void run(const std::vector<std::vector<int>>& dependencyMatrix, 
         bool& isCompilable,
         std::vector<int>& compileOrder, 
         std::vector<std::vector<int>>& cyclicDependencies){
    
    
    
    isCompilable = true;
    
    DFS(dependencyMatrix, compileOrder, isCompilable);
    
    if (isCompilable) return;
    
    
    else {
        
        int u = dependencyMatrix.size();
        
        vector<char> color(u, 'W');
        vector<int> temp;
        
        for (u = u - 1; u >= 0; u--) {
            temp.clear();
            
            if (color[compileOrder[u]] == 'W') {
                SCC(compileOrder[u], dependencyMatrix, color, temp);
                if (temp.size() > 1 || (temp.size() == 1 && dependencyMatrix[compileOrder[u]][compileOrder[u]]))
                    cyclicDependencies.push_back(temp);
            }
            
        }
        
        
        
    }
    
    
    }
