#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>

using namespace __gnu_pbds;

template<typename T> using ordered_set =
tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using ordered_multiset =
tree<T, null_type, std::less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using decreasing_ordered_set =
tree<T, null_type, std::greater<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using decreasing_ordered_multiset =
tree<T, null_type, std::greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define ook(x) order_of_key(x)
#define fbo(x) find_by_order(x)
