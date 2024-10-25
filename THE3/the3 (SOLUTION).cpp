#include "the3.h"
// do not add extra libraries, but you can define helper functions below.


int callG;
int gapG, mismatchG, matchG;


/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/

int comp(char a, char b) {
    if (a == b) return matchG;
    else return -mismatchG;
}

int recF(std::string A, std::string B, std::string &pos_align, int i, int j) {
    
    //overflow
    if (++callG >= 1000000) {
        pos_align = "STACK LIMIT REACHED";
        return INT_MIN;
    }
    
    if (i < 0 && j < 0) {
        pos_align = "";
        return 0;
    }
    
   
    if (i < 0) {
        int temp = recF(A, B, pos_align, i, j - 1) - gapG;
        if (pos_align == "STACK LIMIT REACHED") {
        return INT_MIN;
    }
        pos_align.push_back('_');
        return temp;
    }
    
    if (j < 0) {
        int temp = recF(A, B, pos_align, i - 1, j) - gapG;
        if (pos_align == "STACK LIMIT REACHED") {
        return INT_MIN;
    }
        pos_align.push_back('.');
        return temp;
    }
    
    
    std::string pos1, pos2, pos3;
    int val1 = recF(A, B, pos1, i - 1, j - 1) + comp(A[i], B[j]);
    // if overflow
    if (pos1 == "STACK LIMIT REACHED") {
        pos_align = pos1;
        return INT_MIN;
    }
    
    int val2 = recF(A, B, pos2, i - 1, j) - gapG;
    if (pos2 == "STACK LIMIT REACHED") {
        pos_align = pos2;
        return INT_MIN;
    }
    
    int val3 = recF(A, B, pos3, i, j - 1) - gapG;
    if (pos3 == "STACK LIMIT REACHED") {
        pos_align = pos3;
        return INT_MIN;
    }
    
    
    // if first call max
    if (val1 >= val2 && val1 >= val3) {
        // if chars matching
        if (A[i] == B[j]) pos1.push_back(A[i]);
        else pos1.push_back('!');
        pos_align = pos1;
        return val1;
    }
    
    
    // if second call max
    else if (val2 > val1 && val2 > val3) {
        pos2.push_back('.');
        pos_align = pos2;
        return val2;
    }
    
    
    // if third call max
    else {
        pos3.push_back('_');
        pos_align = pos3;
        return val3;
    }
    
}



int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){
    
    callG = call_count;
    gapG = gap;
    mismatchG = mismatch;
    matchG = match;
    
    return recF(sequence_A, sequence_B, possible_alignment, sequence_A.size() - 1, sequence_B.size() - 1);
}


/*PART 2
you are expected to create a dynamic programming table to find the highest alignment score. 
then you will need to reconstruct a possible alignment string from the table.
*/
int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    
    int sizeA = sequence_A.size();
    int sizeB = sequence_B.size();
    int i, j;
    possible_alignment = "";
    
    //dp table
    std::vector<std::vector<int>> F(sizeA + 1, std::vector<int>(sizeB + 1));
    
    //initializing the gap row and column
    for (i = 0; i <= sizeA; i++) F[i][0] = i* (-gap);
    for (j = 0; j <= sizeB; j++) F[0][j] = j* (-gap);
    
    
    // double loop for bottom up approach
    for (i = 1; i <= sizeA; i++) {
        for (j = 1; j <= sizeB; j++) {
            int diag = F[i-1][j-1] + comp(sequence_A[i - 1], sequence_B[j - 1]);
            int up = F[i-1][j] - gap;
            int left = F[i][j-1] - gap;
            
            F[i][j] = std::max({diag, up, left});
        }
    }
    
    
    //aligning A and B
    std::string A = "", B = "";
    for (i = sizeA, j = sizeB; i > 0 && j > 0;) {
        if (F[i][j] == F[i-1][j-1] + comp(sequence_A[i - 1], sequence_B[j - 1])) {
            A = sequence_A[--i] + A;
            B = sequence_B[--j] + B;
        }
        
        else if (F[i][j] == F[i-1][j] - gap) {
            A = sequence_A[--i] + A;
            B = '.' + B;
        }
        
        else {
            A = '_' + A;
            B = sequence_B[--j] + B;
        }
    }
    
    //emptying the rest of the strings
    while (i > 0) {
        A = sequence_A[--i] + A;
        B = '.' + B;
    }
    while (j > 0) {
        A = '_' + A;
        B = sequence_B[--j] + B;
    }
    
    //finally setting possible alignment
    int s = A.size();
    
    for (int i = 0; i < s; i++) {
        
        // if both same, best case
        if (A[i] == B[i]) possible_alignment.push_back(A[i]);
        
        //if gap in A
        else if (A[i] == '_') possible_alignment.push_back('_');
        
        //if gap in B
        else if (B[i] == '.') possible_alignment.push_back('.');
        
        //if no gap but mismatch
        else possible_alignment.push_back('!');
    }

    return F[sizeA][sizeB];
    
}









