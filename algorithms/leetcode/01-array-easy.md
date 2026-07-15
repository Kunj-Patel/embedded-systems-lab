# 217. Contains Duplicate

**Link:** https://leetcode.com/problems/contains-duplicate/

**Difficulty:** Easy

**Pattern:** Array / Hashing

## Approach 1

Brute for method is to use nested for loops to check every element against every other element until the first duplicate occurs at which point return false.

## Complexity
- **Time Complexity:** $O(n^2)$ - *n is the number of elements in the nums array. In the worst case, no duplicates so the code must compare every pair.*

- **Space Complexity:** $O(1)$ - *Only use a few variables, no data structure grows with input size.*

## Code (C++)
```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        int size = nums.size();
        for (int i=0; i<size; i++) {
            for (int j=i+1; j < size; j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

## Approach 2

We can use a hash set to efficiently keep track of the values we have already encountered.
As we iterate through the array, we check whether the current value is already present in the set.
If it is, that means we've seen this value before, so a duplicate exists.
Using a hash set allows constant-time lookups, making this approach much more efficient than comparing every pair.

## Complexity
- **Time Complexity:** $O(n)$ - *You loop through the array once.
For each element, count() and insert() are average O(1) operations in an unordered_set.
So overall: O(n) average time.*

In theory, hash collisions can make operations degrade, but in interview settings we usually treat unordered_set as O(1) average.

- **Space Complexity:** $O(n)$ - *In the worst case, all elements are unique.
Then the hash set stores all n numbers.
So extra space grows linearly with input size*

## Code (C++)
```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (auto num : nums) {
            if (seen.count(num)) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
};
```