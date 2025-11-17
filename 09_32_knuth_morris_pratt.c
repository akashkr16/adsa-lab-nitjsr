#include <stdio.h>
#include <string.h>

void computeLPS(char* pat, int M, int lps[]) {
    int len = 0, i = 1;
    lps[0] = 0;
    while (i < M) {
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else if (len != 0)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }
}

void KMP(char* pat, char* txt) {
    int M = strlen(pat), N = strlen(txt);
    int lps[M];
    computeLPS(pat, M, lps);
    int i = 0, j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) { i++; j++; }
        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i])
            j ? (j = lps[j - 1]) : i++;
    }
}

int main() {
    char txt[100], pat[20];
    printf("Enter text: ");
    gets(txt);
    printf("Enter pattern: ");
    gets(pat);
    KMP(pat, txt);
    return 0;
}
