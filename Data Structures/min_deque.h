#include <deque>
template <typename T>
class min_deque {
  public:
    min_deque() : _dq{} {}
    void push_back(const T &temp) {
        int ct = 1;
        while (!_dq.empty() && std::less_equal<T>()(temp, _dq.back().first)) {
            ct += _dq.back().second;
            _dq.pop_back();
        }
        _dq.push_back({temp, ct});
    }
    void push_front(const T &temp) {
        if (_dq.empty() || std::less<T>()(temp, _dq.front().first)) {
            _dq.push_front({temp, 1});
        } else if (std::equal<T>(temp, _dq.front().first)) {
            _dq.front().second++;
        }
    }
    T min() {
        assert(!_dq.empty() && "Empty queue");
        return _dq.front();
    }
    void pop_front() {
        assert(!_dq.empty() && "Empty deque.");
        if (_dq.front().second == 1)
            _dq.pop_front();
        else
            _dq.front().second--;
    }
    void pop_back() {
        assert(!_dq.empty() && "Empty deque.");
        if (_dq.back().second == 1)
            _dq.pop_back();
        else
            _dq.back().second--;
    }
    T front() { return _dq.front().first; }
    T back() { return _dq.back().first; }

  private:
    std::deque<std::pair<T, unsigned>> _dq;
};
