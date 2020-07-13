
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

int main()
{
    std::vector<int> vec(10000000);
    std::iota(vec.begin(), vec.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    std::sort(vec.begin(), vec.end());
    return 0;
}
