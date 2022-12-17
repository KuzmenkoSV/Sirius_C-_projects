#include <iostream>
#include <chrono>

bool isprime(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;

    return true;
}
int main(int argc, char *argv[]) 
{
    auto start = std::chrono::steady_clock::now();
    int n = atoi(argv[1]);
    int count = 0;

    for (int i = 2; i <= n; ++i)
        if (isprime(i)) ++count;

    std::cout << count << std::endl;
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1e9 << "seconds" << std::endl;
    return 0;
}