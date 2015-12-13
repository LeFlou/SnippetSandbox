#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

int QuadraticSolution(const std::vector<int> spots)
{
    int best = 0;
    const size_t size = spots.size();
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            const auto gain = spots[j] - spots[i];
            if (gain > best)
            {
                best = gain;
            }
        }
    }
    
    return best;
}

// O(n log n)
int LinearithmicSolution(const std::vector<int>& spots)
{
    if (spots.size() <= 1)
    {
        return 0;
    }
    
    const size_t halfSize = spots.size() / 2;
    std::vector<int> left(spots.begin(), spots.begin() + halfSize);
    std::vector<int> right(spots.begin() + halfSize, spots.end());
    
    const auto leftBest = LinearithmicSolution(left);
    const auto rightBest = LinearithmicSolution(right);
    
    const auto crossBest = *std::max_element(right.begin(), right.end()) - *std::min_element(left.begin(), left.end());

    return std::max({ leftBest, rightBest, crossBest });
}

int main()
{
    const auto spots = std::vector<int> { 5, 15, 17, -35, 0, -6 };
    assert(QuadraticSolution(spots) == 35);
    assert(LinearithmicSolution(spots) == 35);
    return 0;
}