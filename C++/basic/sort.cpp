#include <algorithm>
#include <vector>


using namespace std;

// 按照一般逻辑,
// decreasing和decreasing2应该是等效的才是,
// 但是对于传入sort函数的这两个自定义算子
// 出现的结果却是不一样的.
// 出现这个结果是快排在排序时已经对等于情况有做操作,
// 所以, 虽然传入的逻辑是一样的,
// 却会导致排序的结果不一致(事实上对不使用pair或者其它struct的感知不出来)
// 为了保持逻辑的严谨性,
// 在定义compare的时候我们不应该包含'=='逻辑,
// 就下面的代码来说的话,
// 我们应该使用decreadsing 2.

bool decreasing(const pair<int, int>& lhs,
                const pair<int, int>& rhs) {
    return lhs.first >= rhs.first;
}

bool decreasing2(const pair<int, int>& lhs,
                 const pair<int, int>& rhs) {
    return rhs.first < lhs.first;
}

int main() {
    vector<pair<int, int>> vec{
        {1, 3}, {1, 4}, {4, 5}};
    sort(begin(vec),
         end(vec),
         decreasing);  // after sorting {{4, 5},
                       // {1, 4}, {1, 3}}
    vector<pair<int, int>> vec2{
        {1, 3}, {1, 4}, {4, 5}};
    sort(begin(vec2),
         end(vec2),
         decreasing2);  // after sorting {{4, 5},
                        // {1, 3}, {1, 4}}
    return 0;
}