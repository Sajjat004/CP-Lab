class Solution {
public:
  int countCompleteSubarrays(vector<int>& nums) {
    int n = nums.size();
    unordered_set<int> distinct(nums.begin(), nums.end());
    int distinctCount = distinct.size();

    unordered_map<int, int> frequency;
    int right = 0;
    int result = 0;

    for (int left = 0; left < n; ++left) {
      if (left > 0) {
        int remove = nums[left - 1];
        frequency[remove]--;

        if (frequency[remove] == 0) {
          frequency.erase(remove);
        }
      }

      while (right < n && frequency.size() < distinctCount) {
        int add = nums[right];
        frequency[add]++;
        right++;
      }

      if (frequency.size() == distinctCount) {
        // All elements in the current window are distinct
        // Count the number of complete subarrays starting from 'left'
        result += n - right + 1;
      }
    }

    return result;
  }
};

// Problem Link: https://leetcode.com/problems/count-complete-subarrays-in-an-array/description/
