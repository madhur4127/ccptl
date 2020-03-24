/*
 * Description: A general container which allows order statistics on a 
 *              set/map in logarithmic time.
 * Time Complexity: Additional to std::set/map, O(log N) for order statistics
 * Usage Notes: - 1st template argument is key, 2nd is value, third is comparator. Thus
 *                ordered set can be used as a set and map by making 2nd template arg to
 *                be null_type and a type respectively.
 *                  ordered_set<int,null_type, less<int>>; // std::set<int>
 *                  ordered_set<int,int      , less<int>>; // std::map<int,int>
 *              - For complete description of template argument: codeforces.com/blog/entry/11080
 *
 *              Order Statistics:
 *              - find_by_order(k): returns an iterator to the k-th largest element (counting from zero)
 *              - order_of_key(item) : returns the number of items that are strictly smaller than our item
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef 
__gnu_pbds::tree<
  int,
  null_type,
  less<int>,
  rb_tree_tag,
  tree_order_statistics_node_update>
ordered_set;

/*
  template<
	  typename Key, // Key type
	  typename Mapped, // Mapped-policy
	  typename Cmp_Fn = std::less<Key>, // Key comparison functor
	  typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
	  template<
		  typename Const_Node_Iterator,
		  typename Node_Iterator,
		  typename Cmp_Fn_,
		  typename Allocator_
	  >
	  class Node_Update = null_node_update, // A policy for updating node invariants
	  typename Allocator = std::allocator<char> // An allocator type
  > class tree;
*/
