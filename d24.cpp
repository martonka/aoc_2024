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
#include <iomanip>
#include <sstream>

using namespace std;
using ll = long long;

// ---- Problem specific code ----

unordered_map<string, int> name_to_id;
unordered_map<int, string> id_to_name;

constexpr int digc = 45;

int get_id(const string &name)
{
    static int ni = 0;
    auto it = name_to_id.insert({name, ni});
    if (it.second)
    {
        ++ni;
    }
    return it.first->second;
}

const string &get_name(int id)
{
    return id_to_name[id];
}

string pf(const string &c, int idx)
{
    std::stringstream ss;
    ss << c << std::setw(2) << std::setfill('0') << idx;
    std::string s = ss.str();
    return s;
}

string inX(int idx)
{
    return pf("x", idx);
}

string inY(int idx)
{
    return pf("y", idx);
}

string out(int idx)
{
    return pf("z", idx);
}

struct Rule
{
    enum class OP
    {
        AND,
        OR,
        XOR
    };
    int p1, p2;
    OP op;
    int res;
};

class Network
{
    vector<Rule> odr_rules;
    vector<int> reg;

public:
    Network(const vector<Rule> &rules)
    {
        reg = vector<int>(name_to_id.size(), 0);
        // todo order
        map<int, vector<int>> rule_idx;
        vector<int> wait(rules.size(), 0);
        for (int i = 0; i < rules.size(); ++i)
        {
            const auto &rule = rules[i];
            if (rule.p1 >= digc * 2)
            {
                rule_idx[rule.p1].push_back(i);
                wait[i] += 1;
            }
            if (rule.p2 >= digc * 2)
            {
                rule_idx[rule.p2].push_back(i);
                wait[i] += 1;
            }
        }
        vector<int> gg;
        for (int i = 0; i < rules.size(); ++i)
        {
            if (wait[i] == 0)
            {
                gg.push_back(i);
            }
        }
        while (gg.size())
        {
            auto idx = gg.back();
            gg.pop_back();
            odr_rules.push_back(rules[idx]);
            for (auto &dep : rule_idx[rules[idx].res])
            {
                if (--wait[dep] == 0)
                {
                    gg.push_back(dep);
                }
            }
        }
        int y = 0;
    }

    void run_rules()
    {
        for (const auto &r : odr_rules)
        {
            switch (r.op)
            {
            case Rule::OP::AND:
                reg[r.res] = reg[r.p1] & reg[r.p2];
                break;
            case Rule::OP::OR:
                reg[r.res] = reg[r.p1] | reg[r.p2];
                break;
            case Rule::OP::XOR:
                reg[r.res] = reg[r.p1] ^ reg[r.p2];
                break;

            default:
                break;
            }
        }
    }


    ll calc(ll a, ll b)
    {
        for (int i = 0; i < digc; ++i)
        {
            reg[i] = (a & (1ll << i)) >> i;
            reg[i + digc] = (b & (1ll << i)) >> i;
        }
        run_rules();
        ll res = 0;
        for (int i = 0; i < digc + 1; ++i)
        {
            if (reg[i + digc * 2])
            {
                res += 1ll << i;
            }
        }
        return res;
    }

    ll test_digits(ll a, ll b)
    {
        ll r = calc(a, b);
        return r ^ (a + b);
    }
    ll test_digits()
    {
        ll res = 0;
        ll ao = (1ll << digc) - 1;
        res |= test_digits(ao, 0ll);
        res |= test_digits(0ll, ao);
        res |= test_digits(ao, ao);
        //res |= test_digits( 1ll << 44, 0ll << 29);
        return res;
    }

    void print_digits()
    {
        auto td = test_digits();
        ll ec = 0;
        for (int i = 0; i < digc + 1; ++i)
        {
            if ((1ll << i) & td)
            {
                cout << "Dig " << i << " Wrong" << endl;
                ++ec;
            }
        }
        cout << "EC: " << ec << endl;
    }
};

void test_swaps(const vector<Rule> &rules, const map<int, int> &sw)
{
    auto r2 = rules;
    for (auto &r : r2)
    {
        if (sw.count(r.res))
        {
            r.res = sw.at(r.res);
        }
    }
    Network nw2(r2);
    nw2.print_digits();
}

void test_swaps(const vector<Rule> &rules, const vector<pair<string, string>> &sw)
{
    map<int, int> swaps;
    for (const auto &[a, b] : sw)
    {
        swaps[get_id(a)] = get_id(b);
        swaps[get_id(b)] = get_id(a);
    }
    test_swaps(rules, swaps);
}

int main(int argc, const char **argv)
{
    if (argc >= 3 && argv[1] == string("<"))
    {
        freopen(argv[2], "r", stdin);
    }
    for (int i = 0; i < digc; ++i)
    {
        get_id(inX(i));
    }
    for (int i = 0; i < digc; ++i)
    {
        get_id(inY(i));
    }
    for (int i = 0; i < digc; ++i)
    {
        get_id(out(i));
    }
    vector<Rule> rules;
    string p1, ot, p2, _, target;
    while (cin >> p1 >> ot >> p2 >> _ >> target)
    {
        Rule::OP op = Rule::OP::AND;
        if (ot == "OR")
            op = Rule::OP::OR;
        if (ot == "XOR")
            op = Rule::OP::XOR;
        Rule r;
        r.p1 = get_id(p1);
        r.p2 = get_id(p2);
        r.op = op;
        r.res = get_id(target);
        rules.push_back(r);
    }

    Network nwO(rules);

    {
        auto r2 = rules;
    }
    //nwO.print_digits();
    test_swaps(rules, {{"wpd", "z11" }, {"skh", "jqf"}, {"mdd", "z19"}, {"wts", "z37"} });

}