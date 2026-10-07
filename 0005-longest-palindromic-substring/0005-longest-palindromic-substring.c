#include <string.h>
#include <stdlib.h>

// Helper function to expand around the center and return the length of the palindrome
int expandAroundCenter(char *s, int left, int right, int len) {
    while (left >= 0 && right < len && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

char* longestPalindrome(char* s) {
    if (s == NULL || *s == '\0') {
        return "";
    }
    
    int start = 0, end = 0;
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        // Palindromes can be odd or even length
        int len1 = expandAroundCenter(s, i, i, len);       // Odd length palindrome center
        int len2 = expandAroundCenter(s, i, i + 1, len);   // Even length palindrome center
        
        int max_len = len1 > len2 ? len1 : len2;

        if (max_len > end - start) {
            start = i - (max_len - 1) / 2;
            end = i + max_len / 2;
        }
    }

    // Allocate memory for the longest palindrome substring + null terminator
    int palindrome_len = end - start + 1;
    char *result = (char*)malloc((palindrome_len + 1) * sizeof(char));
    
    strncpy(result, s + start, palindrome_len);
    result[palindrome_len] = '\0';

    return result;
}