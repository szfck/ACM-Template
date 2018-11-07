long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
