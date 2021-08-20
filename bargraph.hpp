#pragma once

#include <stdio.h>

#include <vector>

template <typename ValueType>
class BarGraph
{
  public:
    std::vector<ValueType> history_; // is actually a ring buffer.
    int next_;   // index to the slot where the next insertion will go
    int length_; // total # of data points that have ever been added
    explicit BarGraph(int capacity) : next_(0), length_(0)
    {
        history_.resize(capacity);
        std::fill(history_.begin(), history_.end(), 0);
    }
    // The last value is in [0], so on and so forth
    // Note: if there are not enough data, this function will return as much
    // as is available
    std::vector<float> GetLastNValues(int x)
    {
        std::vector<float> ret;
        const int N = static_cast<int>(history_.size());

        int imax = x;
        imax = std::min(imax, length_);
        imax = std::min(imax, N);

        int idx = (next_ - 1 + N) % N;
        for (int i = 0; i < imax; i++)
        {
            ret.push_back(history_[idx]);
            idx = (idx - 1 + N) % N;
        }
        return ret;
    }
    void AddValue(ValueType x)
    {
        history_[next_] = x;
        next_ = (next_ + 1) % history_.size();
        length_++;
    }
};