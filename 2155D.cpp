#include <unordered_set>
#include <unordered_map>
#include <span>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <array>
#include <math.h>
#include <iomanip>
#include <queue>
#include <random>

using namespace std;
using ll = long long;

std::random_device rd;
std::mt19937 g(rd());

/*
n / k  * (k * (k - 1)) / 2 = n * (k - 1) / 2
*/

void solve()
{
    int n;
    cin >> n;

    set<pair<int, int>> q;
    for (int i = 2; i <= n; i++)
    {
        int e = i;
        for (int j = 1; j <= n; j += e)
        {
            if (j + e - 1 > n) break;
            //cout << j << " , " << j + e << '\n';
            for (int a = j; a < j + e; a++)
            {
                for (int b = a + 1; b < j + e; b++)
                {
                    //cout << j << " , " << j + e - 1 << '\n';
                    if (a <= n && b <= n && (q.find({a,b}) == q.end()))
                    {
                        cout << a << " " << b << std::endl;
                        int ans;
                        cin >> ans;
                        if (ans == 1)
                        {
                            return;
                        }
                        q.insert({a,b});
                        if (ans == -1)
                        {
                            cout << "ERROR!";
                            std::exit(1);
                            return;
                        }
                    }
                    else
                        continue;
                }
            }
        }
    }
}

int main()
{
    int tests;
    cin >> tests;
    while (tests--)
    {
        solve();
    }
}