#include <iostream>
#include <vector>
#include <algorithm>
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
    
    long long result = 0;
    
    // For each point as potential bottom-left corner
    for (int i = 0; i < n; i++) {
        // Use a set to track y-coordinates of points we've seen so far
        set<int> seen_ys;
        
        // Process points to the right of i
        for (int j = i + 1; j < n; j++) {
            if (points[j].y > points[i].y) {
                // Check if there are any points with y-coordinate between points[i].y and points[j].y
                auto lower = seen_ys.lower_bound(points[i].y + 1);
                auto upper = seen_ys.upper_bound(points[j].y - 1);
                
                if (lower == upper) {
                    // No points in the y-range, so this rectangle is empty
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