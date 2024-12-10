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

int main(int argc, const char **argv)
{
    // 6382582218784
    constexpr ll magic_mod = 1e9 + 7;
    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }

    string s;

    cin >> s;
    vector<ll> nums;
    {
        int idx = -1;
        for (int i = 0; i < s.size(); i += 2)
        {
            ++idx;
            for (int j = 0; j < s[i] - '0'; ++j)
            {
                nums.push_back(idx);
            }
            if (i + 1 < s.size())
            {
                for (int j = 0; j < s[i + 1] - '0'; ++j)
                {
                    nums.push_back(-1);
                }
            }
        }
    }

    int id_last = 10000000;
    int tl = nums.size() - 1;
    for (;;)
    {

        while (tl >= 0 && nums[tl] == -1)
            --tl;

        int id = nums[tl];
        if (id == 0)
            break;

        int tl2 = tl;

        while (tl2 >=0 && nums[tl2] == id)
        {
            --tl2;
        }

        if (id > id_last) {
            tl = tl2;
            continue;
        }
        id_last = id;

        int len = tl - tl2;

        int sl = 0;
        for (;;)
        {
            while (sl <= tl2 && nums[sl] != -1)
            {
                ++sl;
            }
            int sl2 = sl;
            while (sl2 <= tl2 && nums[sl2] == -1)
            {
                ++sl2;
            }
            if (sl2 > tl2)
                break;

            int slen = sl2 - sl;
            if (slen >= len)
            {
                for (int i = 0; i < len; ++i)
                {
                    swap(nums[sl + i], nums[tl2 + 1 + i]);
                }
                break;
            }
            sl = sl2;
        }
        tl = tl2;

        // cerr << "xxxxxxx" << endl;
        // for(auto& x : nums) {
        //     cerr << (x == -1 ? " " : to_string(x)) ;
        // }
    }

    ll res = 0;
    for (ll idx = 0; idx < nums.size(); ++idx)
    {

        res += (idx)*max(0ll, nums[idx]);
    }
    cout << res << endl;
}