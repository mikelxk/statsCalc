#include <algorithm>
#include <concepts>
#include <iostream>
#include <ranges>
#include <valarray>

template <typename T>
class stats {
public:
    T Min;
    T Max;
    T Range;
    T Sum;
    T Mode;
    double Mean;
    double Median;
    double popVariance;
    double sampleVariance;
    //standard deviation
    double popσ;
    double sampleσ;
    size_t Cnt{};
    stats(std::ranges::range auto rng, bool pop = true)
    {
        //vector<T> and array<T>
        if constexpr (
            requires { rng.data(); } and requires { rng.size(); }) {
            val = std::valarray<T>(rng.data(), rng.size());
        }
        Min = val.min();
        Max = val.max();
        Range = Max - Min;
        Cnt = val.size();
        Sum = val.sum();
        Mean = (double)Sum / Cnt;
        Median = getMedian(val);
        Mode = getMode(val);
        sampleVariance = getVariance(Cnt -1);
        popVariance = getVariance(Cnt);
        sampleσ = sqrt(sampleVariance);
        popσ = sqrt(popVariance);

    }
    auto getMedian(std::valarray<T> _val)
    {
        std::sort(std::begin(_val), std::end(_val));
        if (Cnt % 2 == 0) {
            return (_val[Cnt / 2 - 1] + _val[Cnt / 2]) / 2.0;
        }
        return _val[Cnt / 2];
    }
    T getMode(std::valarray<T> _val)
    {
        // Sort the array
        int n = _val.size();
        std::sort(std::begin(_val), std::end(_val));

        //finding max frequency
        int max_count = 1, res = _val[0], count = 1;
        for (int i = 1; i < n; i++) {
            if (_val[i] == _val[i - 1])
                count++;
            else {
                if (count > max_count) {
                    max_count = count;
                    res = _val[i - 1];
                }
                count = 1;
            }
        }
        // when the last element is most frequent
        if (count > max_count) {
            max_count = count;
            res = _val[n - 1];
        }
        return res;
    }
    double getVariance(int n)
    {
        std::valarray<double> spread(Cnt);
        for (auto &ele : spread) {
            ele = (ele - Mean) * (ele - Mean);
        }
        return spread.sum() / n;
    }

private:
    std::valarray<T> val;
};
template <typename T>
std::ostream &operator<<(std::ostream &os, stats<T> &st)
{
    os << "Count: " << st.Cnt << '\n'
       << "Sum:   " << st.Sum << '\n'
       << "Min:   " << st.Min << '\n'
       << "Max:   " << st.Max << '\n'
       << "Range: " << st.Range << '\n'
       << "Median:" << st.Median << '\n'
       << "Mode:  " << st.Mode << '\n'
       << "Mean:  " << st.Mean << '\n'
       << "Variance(pop):    " << st.popVariance << '\n'
       << "Variance(sam):    " << st.sampleVariance << '\n'
       << "Standard dev(pop):" << st.popσ << '\n'
       << "Standard dev(sam):" << st.sampleσ << '\n';
    ;
    return os;
}