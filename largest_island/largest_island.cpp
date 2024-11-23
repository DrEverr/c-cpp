#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

// Function to perform DFS and calculate the area of an island
int dfs(vector<vector<int>>& grid, int i, int j) {
    // Check if the current position is out of bounds or not part of an island
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0) {
        return 0;
    }

    // Mark the current cell as visited
    grid[i][j] = 0;

    // Initialize area of the current island
    int area = 1;

    // Explore all 8 possible directions (horizontal, vertical, and diagonal)
    for (auto [di, dj] : {
            pair{-1, 0}, pair{1, 0},
            pair{0, -1}, pair{0, 1},
            pair{-1, -1}, pair{-1, 1},
            pair{1, -1}, pair{1, 1}
        }) {
        area += dfs(grid, i + di, j + dj);
    }

    return area;
}

// Function to find the area of the largest island
int largestIsland(vector<vector<int>>& grid) {
    int maxArea = 0;

    // Traverse the entire grid
    for (int i : views::iota(0, static_cast<int>(grid.size()))) {
        for (int j : views::iota(0, static_cast<int>(grid[0].size()))) {
            // If we find a 1, we start a DFS to calculate the area of the island
            if (grid[i][j] == 1) {
                maxArea = max(maxArea, dfs(grid, i, j));
            }
        }
    }

    return maxArea;
}

int main() {
    vector<vector<int>> grid1 = {
        {0, 0, 0},
        {0, 1, 1},
        {0, 1, 1}
    };

    vector<vector<int>> grid2 = {
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {1, 0, 0, 1},
        {0, 0, 0, 1}
    };

    vector<vector<int>> grid3 = {
        {0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 1}
    };

    cout << "The area of the largest island in grid1 is: " << largestIsland(grid1) << endl; // Output: 4
    cout << "The area of the largest island in grid2 is: " << largestIsland(grid2) << endl; // Output: 5
    cout << "The area of the largest island in grid3 is: " << largestIsland(grid3) << endl; // Output: 10

    return 0;
}