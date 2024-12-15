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
#include <deque>

using namespace std;
using ll = long long;

static ll mx = 0, my = 0;

class Vec2d
{
public:
    ll x, y;
    constexpr Vec2d(ll x, ll y) : x(x), y(y) {}
    Vec2d invers() const { return {-x, -y}; }
    bool operator<(const Vec2d& d) const {
        return x < d.x || x == d.x && y < d.y;
    }
    bool operator==(const Vec2d& d) const {
        return x == d.x && y == d.y;
    }
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
    Coords(ll x, ll y) : x(x), y(y) {}
    bool is_valid() const { return x >= 0 && x < mx && y >= 0 && y < my; }
    Coords operator+(const Vec2d &v) const { return {x + v.x, y + v.y}; }
    Coords operator-(const Vec2d &v) const { return {x - v.x, y - v.y}; }

    bool operator<(const Coords &o) const
    {
        return x < o.x || x == o.x && y < o.y;
    }
    Vec2d operator-(const Coords &o)
    {
        return {x - o.x, y - o.y};
    }

    bool operator==(const Coords& o) const {
        return x == o.x && y == o.y;
    }

    std::string to_string() const {
        return std::to_string(x) + " " + std::to_string(y);
    }

    ll x, y;
};

// ---- Problem specific code ----

vector<string> fields;
Coords rp(0,0);
set<Coords> boxes;
set<Coords> walls;

Vec2d dir(char c) {
    if (c == '^') {
        return {-1, 0};
    }
    if (c == 'v') {
        return {1, 0};
    }
    if (c == '<') {
        return {0, -1};
    }
    if (c == '>') {
        return {0, 1};
    }
    return {0,0};
}

constexpr char box = 'O';


bool bxw(Coords c, set<Coords>& bx, Vec2d dir) {
    auto c2 = c + dir;
    if (walls.count(c2)) {
        return false;
    }
    if (dir == Vec2d{0,-1}) {
        if (boxes.count(c2 + dir)) {
            bx.insert(c2 + dir);
            return bxw(c2 + dir, bx, dir);
        }
        return true;
    }
    if (dir == Vec2d{0,1}) {
        if (boxes.count(c2)) {
            bx.insert(c2);
            return bxw(c2 + dir, bx, dir);
        }
        return true;
    }


    if (boxes.count(c2 + Vec2d(0,-1))) {
        if (bx.count(c2 + Vec2d(0,-1)))
            return true;
        bx.insert(c2 + Vec2d(0,-1));
        return bxw(c2 + Vec2d(0,-1), bx, dir) &&
            bxw(c2, bx, dir);
    }
    if (boxes.count(c2)) {
        if (bx.count(c2))
            return true;
        bx.insert(c2);
        return bxw(c2, bx, dir) &&
            bxw(c2 + Vec2d(0, 1), bx, dir);
    }
    return true;
}


void move(Vec2d dir) {
    set<Coords> bx;
    if (!bxw(rp, bx, dir)) {
        return;
    }
    rp = rp + dir; 
    for(const auto& x : bx) {
        boxes.erase(x);
    }
    for(const auto& x : bx)
        boxes.insert(x + dir);
}

int main(int argc, const char **argv)
{
    constexpr ll magic_mod = 1e9 + 7;

    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }

    string s;
    string moves;
    while(cin >> s) {
        if (s[0]=='#')
            fields.push_back(s);
        else
            moves.append(s);
    }

    mx = fields.size();
    my = fields[0].size();

    for(int x = 0; x < mx; ++x) {
        for(int y = 0; y < my; ++y) {
            if (fields[x][y] == '@') {
                rp = {x,y * 2};
            }
            if (fields[x][y] == box) {
                boxes.insert({x,y * 2});
            }
            if (fields[x][y] == '#') {
                walls.insert({x,y * 2});
                walls.insert({x,y * 2 + 1});
            }
        }
    }

    for (auto m : moves) {
        move(dir(m));
    }

    mx = fields.size() * 2;
    my = fields[0].size();
    ll res = 0;
    for(auto b : boxes) {

                res += 100 * b.x + b.y;
    }

    cout << res << endl;
}