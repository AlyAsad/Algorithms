#include "the4.h"
// do not add extra libraries here


using namespace std;



//solution with 0 indexing

/*
int divide_land(int X, int Y, bool** possible_plots){

    //dp matrix
    vector<vector<int>> F(X, vector<int>(Y));
    
    
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            
            // if no need for division, best case
            if (possible_plots[i + 1][j + 1] == 1) {
                F[i][j] = 0;
                continue;
            }
            
            //else case
            F[i][j] = (i + 1) * (j + 1); //worst case, no split
            
            //horizontal split
            for (int h = 0; h < i; h++)
                F[i][j] = min(F[i][j], F[i - h - 1][j] + F[h][j]);
            
            //vertical split
            for (int v = 0; v < j; v++)
                F[i][j] = min(F[i][j], F[i][j - v - 1] + F[i][v]);
            
        }
    }
    
    return F[X - 1][Y - 1];
}
*/


//solution with 1 indexing
int divide_land(int X, int Y, bool** possible_plots){
    
    // if no dimensions
    if (X == 0 || Y == 0) return 0;
    
    //if no need for dp
    if (possible_plots[X][Y] == 1) return 0;
    
    //dp matrix
    vector<vector<int>> F(X + 1, vector<int>(Y + 1));
    
    
    //dp solution
    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            
            // if no need for division, best case
            if (possible_plots[i][j] == 1) {
                F[i][j] = 0;
                continue;
            }
            
            //else case
            F[i][j] = i*j; //worst case, no split
            
            //horizontal split
            int horLimit = (i+1)/2;
            for (int h = 1; h <= horLimit; h++)
                F[i][j] = min(F[i][j], F[i - h][j] + F[h][j]);
            
            //vertical split
            int verLimit = (j+1)/2;
            for (int v = 1; v <= verLimit; v++)
                F[i][j] = min(F[i][j], F[i][j - v] + F[i][v]);
            
        }
    }
    
    return F[X][Y];
}









