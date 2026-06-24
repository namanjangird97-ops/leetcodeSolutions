#include <vector>

using namespace std;

class Solution {
private:
    int MOD = 1000000007;


    vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B, int size) {
        vector<vector<long long>> C(size, vector<long long>(size, 0));
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                if (A[i][k] == 0) continue; 
                for (int j = 0; j < size; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

   
    vector<vector<long long>> power(vector<vector<long long>> A, long long p, int size) {
        vector<vector<long long>> res(size, vector<long long>(size, 0));
        for (int i = 0; i < size; i++) res[i][i] = 1; 
        
        while (p > 0) {
            if (p & 1) res = multiply(res, A, size);
            A = multiply(A, A, size);
            p >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int M = r - l + 1;
        
      
        if (n == 1) return M;

        int size = 2 * M;
        vector<vector<long long>> T(size, vector<long long>(size, 0));

        
        for (int v_idx = 0; v_idx < M; v_idx++) {
            for (int u_idx = 0; u_idx < v_idx; u_idx++) {
                T[v_idx][u_idx + M] = 1;
            }
        }

        for (int v_idx = 0; v_idx < M; v_idx++) {
            for (int u_idx = v_idx + 1; u_idx < M; u_idx++) {
                T[v_idx + M][u_idx] = 1;
            }
        }
          T = power(T, n - 1, size);
          long long total_sum = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                total_sum = (total_sum + T[i][j]) % MOD;
            }
        }

        return total_sum;
    }
};