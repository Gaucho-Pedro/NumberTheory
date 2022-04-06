/**F(x)=x^(32)⊕a*x(t)⊕1, где t-номер студента в списке\n\n
 * f(x)=x^(16)+x^(12)+x^(3)+x+1 => 0001000000001011 => 0x100B
 */
#include "stdio.h"

void rec(int n, unsigned short *seq) {
    unsigned short tmp;
    for (int i = 0; i < n; i++) {
        if (tmp & 0x8000) {
            tmp = (seq[10] << 1) ^ 0x100B;
        } else {
            tmp = seq[10] << 1;
        }
        tmp ^= seq[0];
        for (int j = 0; j < 31; j++) {
            seq[j] = seq[j + 1];
        }
        seq[31] = tmp;
    }
}

int rec1(int n, unsigned short *seq, int currentIndex) {
    unsigned short tmp;
    for (int i = 0; i < n; i++) {
        if (tmp & 0x8000) {
            tmp = (seq[(10 + currentIndex) & 31] << 1) ^ 0x100B;
        } else {
            tmp = seq[(10 + currentIndex) & 31] << 1;
        }
        tmp ^= seq[currentIndex & 31];
        seq[(currentIndex & 31)] = tmp;
        currentIndex++;
    }
    return currentIndex;
}

int main() {

    int t = 10;
    unsigned short seq[32] = {0};
    for (int i = 0; i < 32; i++) {
        seq[i] = t + i;
    }

    printf("\n<<<<<Method 1>>>>>\n");
    rec(95, seq);
    for (int i = 0; i < 32; i++) {
        printf("Element %d: %hu\n", i + 64, seq[i]);
    }

    printf("\n<<<<<Method 2>>>>>\n");
    for (int i = 0; i < 32; i++) {
        seq[i] = t + i;
    }
    int currentIndex = 0;
    currentIndex = rec1(63, seq, currentIndex);
    for (int i = 64; i < 96; i++) {
        currentIndex = rec1(1, seq, currentIndex);
        printf("Element %d: %hu\n", i, seq[(currentIndex - 1) & 31]);
    }
}