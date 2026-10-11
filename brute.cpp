#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

int main() {
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    int result = 0;
    
    // Brute force: check all pairs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            
            // Check if i is bottom-left and j is top-right
            if (points[i].x < points[j].x && points[i].y < points[j].y) {
                bool is_empty = true;
                
                // Check if any other point is inside or on boundary
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    
                    // Check if point k is inside or on boundary of rectangle
                    if (points[k].x >= points[i].x && points[k].x <= points[j].x &&
                        points[k].y >= points[i].y && points[k].y <= points[j].y) {
                        is_empty = false;
                        break;
                    }
                }
                
                if (is_empty) {
                    result++;
                }
            }
        }
    }
    
    cout << result << endl;
    return 0;
}