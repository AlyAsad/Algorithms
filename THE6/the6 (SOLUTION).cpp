#include "the6.h"

// do not add extra libraries here

using namespace std;

int size;




int extractMin(vector<int> &key, vector<bool> &inQ) {
    
    int minIndex = 0;
    int min = INT_MAX;
    
    for (int i = 0; i < size; i++) {
        if (inQ[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }
    }
    
    inQ[minIndex] = false;
    return minIndex;
    
}



int find_structure(std::vector< std::vector<std::pair<int,int> > >& bond_energies, std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure) {
    
    int lowest = 0;
    size = bond_energies.size();
    
    vector<int> key;
    vector<int> parent;
    vector<bool> inQ;
    
    
    
    lowest_energy_structure.clear();
    
    for (int i = 0; i < size; i++) {
        lowest_energy_structure.push_back(vector<pair<int,int>>());
        key.push_back(INT_MAX);
        parent.push_back(-1);
        inQ.push_back(true);
    }
    
    
    key[0] = 0;
    
    
    for (int i = 0; i < size; i++) {
        int u = extractMin(key, inQ);
        
        if (u != 0) {  //avoiding base case
            lowest += key[u];
            lowest_energy_structure[u].push_back(make_pair(parent[u], key[u]));
            lowest_energy_structure[parent[u]].push_back(make_pair(u, key[u]));
        }
        
        for (pair<int,int> v : bond_energies[u]) {
            if (inQ[v.first] && v.second < key[v.first]) {
                parent[v.first] = u;
                key[v.first] = v.second;
            }
        }
        
    }
    
    
    
    
    return lowest;
}





int maxIndex(vector<int> &dist) {
    
    int mi = 0;
    
    for (int i = 1; i < size; i++) {
        if (dist[i] > dist[mi]) mi  = i;
    }
    
    return mi;
}



int find_longest_chain(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, std::vector<int>& chain){
    
    
    size = molecule_structure.size();
    
    vector<int> visited(size, false);
    vector<int> dist(size, -1);
    vector<int> parent(size, -1);
    
    stack<int> dfs;
    
    dist[0] = 0;
    dfs.push(0);
    
    
    // first dfs to find root
    
    while (!dfs.empty()) {
        int u = dfs.top();
        dfs.pop();
        visited[u] = true;
        
        
        if (u != 0) {// ignore base case
            dist[u] = dist[parent[u]] + 1;
            
        }
        
        for (pair<int,int> v : molecule_structure[u]) {
            if (!visited[v.first]) {
                parent[v.first] = u;
                dfs.push(v.first);
            }
        }
        
    }
    
    
    //starting second dfs
    
    int root = maxIndex(dist);
    
    for (int i = 0; i < size; i++) {
        visited[i] = false;
        dist[i] = -1;
        parent[i] = -1;
    }
    
    dist[root] = 0;
    dfs.push(root);
    
    while (!dfs.empty()) {
        int u = dfs.top();
        dfs.pop();
        visited[u] = true;
        
        if (u != root) {// ignore base case
            dist[u] = dist[parent[u]] + 1;
            
        }
        
        for (pair<int,int> v : molecule_structure[u]) {
            if (!visited[v.first]) {
                parent[v.first] = u;
                dfs.push(v.first);
            }
        }
        
    }
    
    int final = maxIndex(dist);
    
    
    int longest = dist[final] + 1;
    
    while (final != root) {
        chain.push_back(final);
        final = parent[final];
    }
    chain.push_back(root);
    
    
    return longest;
}
