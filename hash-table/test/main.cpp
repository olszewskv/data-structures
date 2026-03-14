#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

vector<int> TwoSum_1(vector<int> nums, int target) {
    cout << "Array : " << nums;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] == target - nums[i]) {
                printf("{%d, %d}", i, j);
                return {};
            }
        }
    }
    printf("No matches");
    return {};
}

ostream operator<<(const ostream & lhs, const vector<int> & rhs);

int main() {

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    TwoSum_1(nums, target);

    return 0;
}
