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

set<Coords> fields(const vector<string> &tb, Coords p)
{
    set<Coords> vis;
    int dir = 0;
    for (;;)
    {
        vis.insert(p);
        auto p2 = p + all_dirs[dir];
        if (!p2.is_valid())
        {
            return vis;
        }
        if (tb[p2.x][p2.y] == '#')
        {
            dir += 1;
            dir %= 4;
        }
        else
        {
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
    mx = tb.size();
    my = tb.front().size();

    map<char, vector<Coords>> cats;

    set<Coords> notgood;
    set<Coords> result;

    for (int x = 0; x < mx; ++x)
        for (int y = 0; y < my; ++y)
        {
            if (tb[x][y] != '.')
            {
                cats.insert({tb[x][y], {}}).first->second.push_back({x, y});
                //notgood.insert({x, y});
            }
        }
    for (const auto &[k, v] : cats)
    {
        for (int i1 = 0; i1 < v.size(); ++i1)
        {
            for (int i2 = i1 + 1; i2 < v.size(); ++i2)
            {
                auto a = v[i1];
                auto b = v[i2];
                auto d = a - b;
                for(auto cc = a; cc.is_valid(); cc = cc + d) {
                    result.insert(cc);
                }
                for(auto cc = b; cc.is_valid(); cc = cc + d.invers()) {
                    result.insert(cc);
                }
            }
        }
    }

    cout << result.size() << endl;
}