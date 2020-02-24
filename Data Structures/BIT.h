/*
 * Author : Madhur Chauhan
 * Common Names: Fenwick Tree, Binary Indexed Tree
 * Use : Data structures which does prefix/range operation in O(log N) (small constant) with point updates.
 * Time Complexity : O(N) to build
 *					 O(logN) to query a range
 *					 O(logN) to update a point
 * Space Complexity: O(N)
 * Usage Notes: 1. Template arguments: <element type "T",	// ex - int, long long
 *									    operation "op">		// ex - std::plus (for prefix sum) (DEFAULT)
 *				2. BIT uses 0-based indexing for update and query
 *				3. Examples:
 *							BIT<long long> b(1e5, 67); // creates a bit with 10^5 elements initialized to 67
 *													   // defaults to 0
 *							BIT<long long> b(v);   // creates a bit on vector<long long> v
 *							b.query(10);		   // return op(b[0], b[1], b[2], ... , b[10])
 */

template <typename T = int, class op = std::plus<T>>
class BIT {
  public:
	// constructs a BIT with specified size
	BIT(unsigned size, T val = 0) : _bit(size + 1, val) {}

	// constructs a BIT with specified elements
	BIT(const vector<T> &list) : _bit(1) {
		_bit.insert(_bit.end(), list.begin(), list.end());
		int size = _bit.size();
		for (int i = 1; i <= size; ++i) {
			int idx = i + (i & -i);
			if (idx <= size)
				_bit[idx] = func(_bit[idx], _bit[i]);
		}
	}

	void update(int pos, T dif) { // pos is 0-based indexed
		// assert(pos>=0 && pos<_bit.size() && "ERROR: Invalid position");
		for (++pos; pos < (int)_bit.size(); pos += pos & -pos)
			_bit[pos] = func(_bit[pos], dif);
	}

	T query(int pos) const { // pos is 0-indexed, prefix operation of values [0...pos]
		// assert(pos>=0 && pos<_bit.size() && "ERROR: Invalid position");
		T res = _bit[++pos];
		for (pos -= pos & -pos; pos; pos -= pos & -pos)
			res = func(res, _bit[pos]);
		return res;
	}

  private:
	vector<T> _bit; // FT using 1-based indexing
	const op func = op();
};
