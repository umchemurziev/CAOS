#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <vector>


std::pair<int64_t, int64_t > pi(unsigned int number_cur, int64_t it, int64_t r)
{
    int64_t x = 0;
    int64_t y = 0;
    int64_t cnt = 0;
    int64_t ap = 0;

    for (int64_t i = 0; i < it; ++i)
    {
        x = rand_r(&number_cur) % (r << 1) - r;
        y = rand_r(&number_cur) % (r << 1) - r;

        ap = pow(x, 2) + pow(y, 2);

        if (ap < pow(r, 2))
        {
            ++cnt;
        }
    }

    return { cnt, it };
}

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    int it = atoi(argv[2]);

    int64_t a = 0;
    int64_t s = 0;
    std::vector< std::future< std::pair< int64_t, int64_t > > > future_val(n);

    for (int64_t i = 0; i < n; ++i)
    {
        future_val[i] = async(std::launch::async, pi, i, static_cast<int64_t>(it), 100);
    }
    std::pair<int, int> res = { 0, 0 };

    for (auto &elem : future_val)
    {
        res = elem.get();
        s += res.second;
        a += res.first;
    }
    double ans = (double(a) * 4) / double(s);

    std::cout << std::setprecision(5) << ans  << "\n";

    return 0;
}
