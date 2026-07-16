# 49. Group Anagrams

**Link:** https://leetcode.com/problems/group-anagrams/
**Difficulty:** Medium
**Pattern:** Array / Hashing

## Approach
Since we know each string is only comprised of lower case english letters. Instead of sorting, count freq of each letter in each string and store in a hashmap.
For each word, I create a frequency count of the 26 lowercase letters. I then convert that frequency count into a unique string key and use it as the key in an unordered_map. Words with identical frequency counts produce the same key, so they are placed into the same group. After processing all the words, I iterate through the hash map and collect each group into the final result.

## Interview rule of thumb
- Use unordered_map when you need fast lookups and don't care about key order
- Use map when you need the keys kept in sorted order or you need operations like finding the next larger/smaller key

## Complexity
- **Time Complexity:** $O(m * n)$ - *m = strs.length & n = average length of each string. For each string: Counting letters takes O(m). Building the key takes O(26). Hash map insert/push is O(1) avg*


- **Space Complexity:** $depends$ - 
*We store the hash map of grouped strings, the strings themselves in those groups, a 26-sized count temp array per iteration.The dominant space is the hash map output storage because all strings are ultimately stored in the groups.*

### Auxiliary space 
- measures the **extra working memory** an algorithm uses **excluding the memory required for the final output**.

- **Total space (including the returned result):** `O(m * n)`
  - The output contains all `m` strings, each of average length `n`, so simply storing the grouped anagrams requires `O(m * n)` space.

- **Auxiliary space (excluding the returned result):** `O(m)`
  - If we ignore the memory needed for the final answer, the algorithm only uses extra space for the hash map (up to one entry per string in the worst case). The 26-element frequency array is constant size, so it contributes only `O(1)` space.

## Code (C++)
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // hashmap that maps letter counts string to an array of words
        unordered_map<string, vector<string>> groups;

        for (const string& str : strs) {
            // a ... z 
            vector<int> counts(26,0);
            
            // increment count of that letter if it exists in the str
            for (char c : str) {
                counts[c - 'a']++;
            }

            string key;

            for (auto x : counts) {
                key += to_string(x);
                key += '#'; // needed for unique keys / remove ambiguity
            }

            groups[key].push_back(str);
        }

        vector<vector<string>> answer;

        for (const auto& pair : groups) {
            answer.push_back(pair.second); // iterate over groups map and only return string vectors
        }

        return answer;
    }
};

```
