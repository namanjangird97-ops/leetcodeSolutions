#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;

        // dp_sum[i][j] will store the max score to reach (i, j) from (0, 0)
        vector<vector<int>> dp_sum(n, vector<int>(n, -1));
        // dp_paths[i][j] will store the number of paths to achieve that max score
        vector<vector<int>> dp_paths(n, vector<int>(n, 0));

        // Base case: starting at 'E' (0, 0)
        dp_sum[0][0] = 0;
        dp_paths[0][0] = 1;

        // Directions: up, left, up-left relative to current cell
        int dirs[3][2] = {{-1, 0}, {0, -1}, {-1, -1}};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Skip the start cell 'E' or obstacles 'X'
                if ((i == 0 && j == 0) || board[i][j] == 'X') {
                    continue;
                }

                int max_prev_score = -1;
                int paths_count = 0;

                // Check all 3 possible incoming directions
                for (auto& dir : dirs) {
                    int pi = i + dir[0];
                    int pj = j + dir[1];

                    // Ensure valid coordinates and that the neighbor is reachable
                    if (pi >= 0 && pj >= 0 && dp_sum[pi][pj] != -1) {
                        if (dp_sum[pi][pj] > max_prev_score) {
                            max_prev_score = dp_sum[pi][pj];
                            paths_count = dp_paths[pi][pj];
                        } else if (dp_sum[pi][pj] == max_prev_score) {
                            paths_count = (paths_count + dp_paths[pi][pj]) % MOD;
                        }
                    }
                }

                // If at least one incoming neighbor was reachable
                if (max_prev_score != -1) {
                    int current_val = (board[i][j] == 'S') ? 0 : (board[i][j] - '0');
                    dp_sum[i][j] = max_prev_score + current_val;
                    dp_paths[i][j] = paths_count;
                }
            }
        }

        // Return results from the bottom-right corner 'S'
        if (dp_sum[n-1][n-1] == -1) {
            return {0, 0};
        }
        return {dp_sum[n-1][n-1], dp_paths[n-1][n-1]};
    }
};