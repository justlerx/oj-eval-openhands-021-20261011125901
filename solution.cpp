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

class FenwickTree {
private:
    vector<int> tree;
    int size;
    
public:
    FenwickTree(int n) : size(n), tree(n + 1, 0) {}
    
    void update(int idx, int delta) {
        idx++;
        while (idx <= size) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }
    
    int query(int idx) {
        idx++;
        int result = 0;
        while (idx > 0) {
            result += tree[idx];
            idx -= idx & -idx;
        }
        return result;
    }
    
    int range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
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
    
    // Coordinate compression for y
    vector<int> ys;
    for (const auto& p : points) {
        ys.push_back(p.y);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    
    map<int, int> y_to_idx;
    for (int i = 0; i < ys.size(); i++) {
        y_to_idx[ys[i]] = i;
    }
    
    long long result = 0;
    
    // For each point as potential bottom-left corner
    for (int i = 0; i < n; i++) {
        // For each point to the right of i that could be top-right
        for (int j = i + 1; j < n; j++) {
            if (points[j].y > points[i].y) {
                // Check if there are any points inside the rectangle
                bool has_inside = false;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    
                    // Check if point k is inside or on boundary of rectangle
                    if (points[k].x >= points[i].x && points[k].x <= points[j].x &&
                        points[k].y >= points[i].y && points[k].y <= points[j].y) {
                        has_inside = true;
                        break;
                    }
                }
                
                if (!has_inside) {
                    result++;
                }
            }
        }
    }
    
    cout << result << endl;
    return 0;
}