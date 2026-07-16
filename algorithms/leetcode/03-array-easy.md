# 1. Two Sum

**Link:** https://leetcode.com/problems/two-sum/
**Difficulty:** Easy
**Pattern:** Array / Hashing

## Approach 1
My brute force method was to just check every possible pair, and return the first that satisfies the requirement of i != j,
[i,j] where nums[i]+nums[j] == target.


## Complexity
- **Time Complexity:** $O(n^2)$ - *Nested for loops*
- **Space Complexity:** $O(1)$ - *declared indexes vector will always have max of 2 elements.*

## Code (C++)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> indexes;
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    indexes.push_back(i);
                    indexes.push_back(j);
                    return indexes;
                }
            }
        }
        return {};
    }
};

```

## Approach 2
We don't need to check every pair since it is given that a unique solution will exist based on the given inputs.
Use a hashmap to store values that we have already seen and at what index they were at. We check the complement 
before inserting the current number. This avoids using the same index twice. If yes, return indices.


## Complexity
- **Time Complexity:** $O(n)$ - *Each hash map lookup and insert is O(1) on average. We loop through the nums array once in the worst case.*
- **Space Complexity:** $O(n)$ - *In the worst case, we store almost all elements in the hash map*

## Code (C++)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map; // number -> index

        for (int i=0; i<nums.size(); i++) {
            int complement = target - nums[i];

            // if the complement does exist in the map
            if (map.find(complement) != map.end()) {
                return {map[complement], i};
            }

            map[nums[i]] = i;
        }
        return {};   
    }
};

```