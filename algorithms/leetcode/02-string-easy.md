# 242. Valid Anagram

**Link:** https://leetcode.com/problems/valid-anagram/
**Difficulty:** Easy
**Pattern:** String / Hashing

## Interview rule of thumb
- If the alphabet is small and fixed → use an array
- If characters are unbounded or arbitrary → use a hash map
- If simplicity matters more than efficiency → sorting is acceptable

## Approach 1 
My simple approach was to store each string into a hash map <char, int> to count how frequently a letter appears in a word. Then just compare the hashmaps.

## Complexity
- **Time Complexity:** $O(n)$ - *I loop through both strings once to create the hash map.*
- **Space Complexity:** $O(1)$ - *In the worst case, each map contains up to 26 entries (lowercase english alphabet letters)*

## Code (C++)
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        unordered_map<char, int> word;
        for (auto letter : s) {
            word[letter]++;
        }

        unordered_map<char, int> word2;
        for (auto letter : t) {
            word2[letter]++;
        }

        return word == word2;
    }
};

```

## Approach 2 
Since the problem says the strings contain only lowercase English letters, you can avoid a hash map entirely and use a simple array of size 26. For every character in s, increment its count.
For every character in t, decrement its count.
If the strings are anagrams, all counts end at 0.

Only works because the problem limits input to lowercase letters

## Complexity
- **Time Complexity:** $O(n)$ - *I loop through both strings once.*
- **Space Complexity:** $O(1)$ - *the array is always size 26*

## Code (C++)
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        int count[26] = {0};

        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for (int n : count) {
            if (n != 0) {
                return false;
            }
        }

        return true;
    }
};
```
