/*
 * Author: Madhur Chauhan
 * Use: Generates all permutations of a given vector efficiently NOT IN LEXICOGRAPHIC ORDER.
 * Time Complexity:  O(n!)
 * Space Complexity: O(n)
 * Usage notes:
 *          1. Generating all permutations
 *              vector<int> v(n);
 *              for(int i=0; i<n; ++i) v[i] = i;
 *              all_permutations(v);
 *          2. Using permutations: Change the lines of the following type to use each permutation:
 *                 // output (arr)
 *          3. Permutations will be stored in arr
 */
template <typename T> // T must support random access like vector/array unlike list/queue/stack
void all_permutations(T arr) {
    int n = arr.size();
    std::vector<int> c(n, 0);

    // first permutation is in Arr
    // output(arr)

    for (int i = 0; i < n;) {
		if (c[i] < i) {
			if (i & 1)
				swap(arr[c[i]], arr[i]);
			else
				swap(arr[0], arr[i]);

            // next permutation is in arr
            // output (arr)

            c[i] += 1;
			i = 0;
		} else {
			c[i++] = 0;
		}
	}
}
