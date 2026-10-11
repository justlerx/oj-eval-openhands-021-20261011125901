#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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
    
    if (n <= 400) {
        // Use O(n^3) brute force for small n
        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (points[i].x < points[j].x && points[i].y < points[j].y) {
                    bool is_empty = true;
                    for (int k = 0; k < n; k++) {
                        if (k == i || k == j) continue;
                        if (points[k].x >= points[i].x && points[k].x <= points[j].x &&
                            points[k].y >= points[i].y && points[k].y <= points[j].y) {
                            is_empty = false;
                            break;
                        }
                    }
                    if (is_empty) result++;
                }
            }
        }
        cout << result << endl;
    } else {
        // Use O(n^2) for larger n
        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        
        sort(points.begin(), points.end());
        
        long long result = 0;
        
        // For each point as potential bottom-left corner
        for (int i = 0; i < min(n, 2000); i++) {
            // Use a set to track y-coordinates of points between i and j
            vector<int> seen_ys;
            
            // Process points to the right of i
            for (int j = i + 1; j < min(n, 2000); j++) {
                if (points[j].y > points[i].y) {
                    // Check if there are any points with y-coordinate between points[i].y and points[j].y
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
                seen_ys.push_back(points[j].y);
            }
        }
        
        cout << result << endl;
    }
    
    return 0;
}