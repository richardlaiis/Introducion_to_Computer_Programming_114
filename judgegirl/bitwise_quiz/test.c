#include <stdio.h>
#include <stdint.h>
#include <inttypes.h> // For PRIu64

// Convert Gray code to binary
uint64_t gray_to_bin(uint64_t gray) {
    uint64_t bin = 0;
    for (; gray; gray >>= 1)
        bin ^= gray;
    return bin;
}

// Convert binary to Gray code
uint64_t bin_to_gray(uint64_t x) {
    return x ^ (x >> 1);
}

// Find closest M to N with allowed bits (mask)
uint64_t closest_masked(uint64_t N, uint64_t mask) {
    uint64_t M = 0;
    for (int i = 63; i >= 0; i--) {
        uint64_t bit = (uint64_t)1 << i;
        if (mask & bit) {  // allowed to set
            if (N & bit)
                M |= bit;  // match N
        }
        // else bit is forced to 0
    }
    return M;
}

// Find closest Gray code with mask r
uint64_t find_closest_gray(uint64_t n, uint64_t r) {
    uint64_t N = gray_to_bin(n);
    uint64_t mask = ~r;
    uint64_t M = closest_masked(N, mask);
    return bin_to_gray(M);
}

int main() {
    uint64_t n, r;
    printf("Enter Gray code n: ");
    if (scanf("%" SCNu64, &n) != 1) return 1;
    printf("Enter bitmask r: ");
    if (scanf("%" SCNu64, &r) != 1) return 1;

    uint64_t m = find_closest_gray(n, r);

    uint64_t N = gray_to_bin(n);
    uint64_t M = gray_to_bin(m);

    printf("Closest Gray code m: %" PRIu64 "\n", m);
    printf("Binary N: %" PRIu64 ", Binary M: %" PRIu64 "\n", N, M);
    printf("Difference |N-M|: %" PRIu64 "\n", N > M ? N - M : M - N);

    return 0;
}

