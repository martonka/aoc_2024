#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <tuple>
#include <numeric>
#include <unordered_set>
#include <set>
#include <array>

using namespace std;
using ll = long long;

static int mx = 0, my = 0;

class Vec2d
{
public:
    int x, y;
    constexpr Vec2d(int x, int y) : x(x), y(y) {}
};

constexpr std::array<Vec2d, 4> all_dirs = {
    Vec2d{-1, 0},
    Vec2d{0, 1},
    Vec2d{1, 0},
    Vec2d{0, -1},
};

class Coords
{
public:
    Coords(int x, int y) : x(x), y(y) {}
    bool is_valid() const { return x >= 0 && x < mx && y >= 0 && y < my; }
    Coords operator+(const Vec2d &v) const { return {x + v.x, y + v.y}; }

    bool operator<(const Coords& o) const {
         return x < o.x || x == o.x && y < o.y;
    }

    // bool operator!=(const Coords& o) const {
    //     return q != o.q || r != o.r;
    // }
    // std::string to_string() const {
    //     return std::to_string(q) + " " + std::to_string(r);
    // }

    // int distanceFrom(const Coords& o) const {
    //     int qd = q - o.q;
    //     int rd = r - o.r;
    //     return std::max(std::abs(qd), std::max(std::abs(rd), std::abs(qd + rd)));
    // }

    int x, y;
    // friend inline std::ostream& operator<<(std::ostream& oss, const Coords& c);
};


set<Coords> fields(const vector<string>& tb, Coords p) {
    set<Coords> vis;
    int dir = 0;
    for(;;) {
        vis.insert(p);
        auto p2 = p + all_dirs[dir];
        if (!p2.is_valid()) {
            return vis;
        } 
        if (tb[p2.x][p2.y] == '#') {
            dir += 1;
            dir %=4;
        } else {
            p = p2;
        }

    }
}

struct MyHashFunction
{
    size_t operator()(const tuple<int , int , int>&x) const
   {
       return get<0>(x) * 1000 +  get<1>(x) * 4 + get<2>(x);
   }
};

bool stuck(const vector<string>& tb, Coords p) {
    int dir = 0;
    unordered_set<tuple<int,int,int>, MyHashFunction> vis;
    for(;;) {
        tuple<int, int , int> cs = {p.x, p.y, dir};
        if (vis.count(cs)) {
            return true;
        } 
        vis.insert(cs);
        auto p2 = p + all_dirs[dir];
        if (!p2.is_valid())
            return false;
        if (tb[p2.x][p2.y] == '#') {
            dir += 1;
            dir %=4;
        } else {
            p = p2;
        }

    }
}

int main(int argc, const char **argv)
{
    constexpr ll magic_mod = 1e9 + 7;
    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }
    vector<string> tb;
    string s;
    while ((cin >> s) && s.size())
    {
        tb.push_back(s);
    }

    int dir = 0;

    mx = tb.size();
    my = tb[0].size();
    Coords p{0,0};
    for (int x = 0; x < mx; ++x)
        for (int y = 0; y < my; ++y)
        {
            if (tb[x][y] == '^') {
                p = {x,y};
            }
        }

    int res = 0;    
    auto ff = fields(tb, p);
    for(auto x : ff) {
            if (tb[x.x][x.y] == '.') {
                
                tb[x.x][x.y] = '#';
                if (stuck(tb,p)) {
                    res +=1;
                }
                tb[x.x][x.y] = '.';
            }
    }

    cout << res << endl;
}