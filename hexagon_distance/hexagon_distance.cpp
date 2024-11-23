#include <iostream>
#include <vector>
#include <cmath>
#include <ranges>

using namespace std;

// Function to calculate the distance between two points in axial coordinates
int hexDistance(pair<int, int> p1, pair<int, int> p2) {
    int x = abs(p1.first - p2.first);
    int y = abs(p1.second - p2.second);
    int z = abs(p1.first + p1.second - p2.first - p2.second);
    return (x + y + z) / 2;
}

// Function to find the distance between two marked locations on a hexagonal grid
int hexDistance(const vector<string>& grid) {
    pair<int, int> p1, p2;
    bool foundFirst = false;

    // Traverse the grid to find the two marked locations
    for (int row : views::iota(0, static_cast<int>(grid.size()))) {
        int colIndex = 0;
        for (int col : views::iota(0, static_cast<int>(grid[row].size()))) {
            if (grid[row][col] == ' ') {
                continue;
            }
            if (grid[row][col] == 'x') {
                if (!foundFirst) {
                    p1 = make_pair(row, colIndex);
                    foundFirst = true;
                } else {
                    p2 = make_pair(row, colIndex);
                    // Calculate and return the distance between the two points
                    return hexDistance(p1, p2);
                }
            }
            colIndex++;
        }
    }

    // Found only one point
    return -1;
}

int main() {
    vector<string> grid1 = {
        "  o o  ",
        " o x o ",
        "  o x  "
    };

    vector<string> grid2 = {
        "  o o  ",
        " x o o ",
        "  o x  "
    };

    vector<string> grid3 = {
        "   o o o   ",
        "  o o o o  ",
        " o o o o o ",
        "  x o o x  ",
        "   o o o   "
    };

    cout << "Distance in grid1: " << hexDistance(grid1) << endl; // Output: 1
    cout << "Distance in grid2: " << hexDistance(grid2) << endl; // Output: 2
    cout << "Distance in grid3: " << hexDistance(grid3) << endl; // Output: 3

    return 0;
}