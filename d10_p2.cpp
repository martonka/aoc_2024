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
#include <unordered_map>
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
    Vec2d invers() const { return {-x, -y}; }
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

    bool operator<(const Coords &o) const
    {
        return x < o.x || x == o.x && y < o.y;
    }
    Vec2d operator-(const Coords &o)
    {
        return {x - o.x, y - o.y};
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

vector<string> fields;
map<Coords, int> dests;

ll trail_count(Coords c ) {
    auto t = fields[c.x][c.y];
    if (t == '9') { 
        dests.insert({c,0}).first->second+=1;
        return 1;
    }
    t +=1;
    ll res = 0;
    for(const auto d: all_dirs) {
        auto c2 = c + d;
        if (!c2.is_valid() || fields[c2.x][c2.y] != t) 
            continue;
        res += trail_count(c2);
    }
    return res;
}

int main(int argc, const char **argv)
{
    // 6382582218784
    constexpr ll magic_mod = 1e9 + 7;
    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }

    string s;

    while(cin >> s) {
        fields.push_back(s);
    }

    mx = fields.size();
    my = fields[0].size();


    ll res = 0;
    ll res2 = 0;
    for(int x = 0; x < mx; ++x) {
        for(int y = 0; y < my; ++y) {
            if (fields[x][y] != '0')
                continue;
            res += trail_count({x,y});
            res2 += dests.size();
            dests.clear();        
        }
    }        

    cout << res << endl;
    cout << res2 << endl;
}