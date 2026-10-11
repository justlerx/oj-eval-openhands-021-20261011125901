#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

struct Point {
    int x, y;
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    // Sort by x-coordinate
    sort(points.begin(), points.end());
    
    // Create mapping from coordinates to indices for fast lookup
    map<int, int> x_to_idx, y_to_idx;
    for (int i = 0; i < n; i++) {
        x_to_idx[points[i].x] = i;
        y_to_idx[points[i].y] = i;
    }
    
    long long result = 0;
    
    // For each point as potential bottom-left corner
    for (int i = 0; i < n; i++) {
        // Use a set to track y-coordinates of points between i and j
        set<int> seen_ys;
        
        // Process points to the right of i
        for (int j = i + 1; j < n; j++) {
            if (points[j].y > points[i].y) {
                // Check if there are any points with y-coordinate between points[i].y and points[j].y
                // that are also between points[i].x and points[j].x
                bool has_inside = false;
                for (int y : seen_ys) {
                    if (y > points[i].y && y < points[j].y) {
                        has_inside = true;
                        break;
                    }
                }
                
                if (!has_inside) {
                    result++;
                }
            }
            
            // Add current point's y-coordinate to the set
            seen_ys.insert(points[j].y);
        }
    }
    
    cout << result << endl;
    return 0;
}