#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <random>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------
int getBitLength(long long number) { 
int x;
if (number == 0) {
    return 0;
}
x = (int)ceil((log2(number) + 1) / 8) * 8;
return (int)ceil((log2(number) + 1) / 8) * 8;
}
// Функция для построения таблицы простых чисел с помощью решета Эратосфена
vector<long long> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<long long> primes;

    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }

    for (int p = 2; p <= n; ++p) {
        if (isPrime[p])
            primes.push_back(p);
    }

    return primes;
}
//Генерация случайных чисел
long long randomNum(long long a, long long b)
{
    long long mn = min(a, b), mx = max(a, b);

    mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count()); 
    return gen() % (mx - mn + 1) + mn;
}
// Функция для нахождения наибольшего общего делителя двух чисел
long long NOD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
// Функция для вычисления a^b mod n
long long powMod(long long a, long long b, long long n) {
    long long result = 1;
    a = a % n;

    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % n;
        b /= 2;
        a = (a * a) % n;
    }

    return result;
}


bool testVer(long long n, int k)
{
    if (n == 2)
        return true;

    if (n % 2 == 0 or n < 2)
        return false;

    long long t = n - 1, s = 0;

    while (t % 2 == 0)
    {
        t /= 2;
        ++s;
    }

    for (int i = 0; i < k; ++i)
    {
        long long a = randomNum(2, n - 2);
        long long x = powMod(a, t, n);

        if (x == 1 or x == n - 1)
            continue;

        for (int j = 0; j < s - 1; ++j)
        {
            x = powMod(x, 2, n);

            if (x == 1)
                return false;

            if (x == n - 1)
                break;
        }
    }

    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------
// Функция для проверки числа на простоту по тесту Миллера
bool millerTest(long long n, long long d, const vector<long long>& primes, int t) {
    srand(time(nullptr)); // Инициализация генератора случайных чисел с использованием времени
    vector<long long> aj;
    for (int i = 0; i < t; ++i) {
        long long a;
        a = randomNum(2, n-2); // Генерация случайного числа a в диапазоне [2, n - 1]
        aj.push_back(a);
        long long x = powMod(a, d, n);
        if (x != 1)
            return false;
    }
    for (long long prime : primes){
        for (auto i:aj) {
            long long z = d / prime;
            if (powMod(i, (z), n) != 1)
                continue;
            else {
                return false;
                break;
            }
        }
    }

    return true;
}
// Функция для построения простого числа заданной длины на основе теста Миллера
pair <long long, int> generatePrimeMiller(int bitLength, const vector<long long>& primes, int t) {
    srand(time(nullptr)); // Инициализация генератора случайных чисел с использованием времени
    int count = 0;
    vector <int> counts;
    // Строим число m=q1^a1*q2^a2*...*qk^ak
    long long m;
    while (true) {
        while (true) {
            m = 1;
            for (auto i = 0; i < t; i++) {
                int q = primes[randomNum(0, primes.size() - 1)]; // Случайно выбираем простое число из списка простых чисел
                int a = randomNum(1, 3); // Случайная степень

                long long poweredPrime = 1;
                for (auto i = 0; i < a; ++i) {
                    poweredPrime *= q;
                }

                m *= poweredPrime;

            }
            if (getBitLength(m) == (bitLength - 1)) break;
        }

        long long n = 2 * m + 1; // Вычисляем значение n=2m+1
        long long d = n - 1;

        if (millerTest(n, d, primes, t)) {
            return make_pair(n, count);
        }
        else if (testVer(n, 5)) count++;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------

// Функция для проверки числа на простоту по тесту Миллера
bool poklingtonTest(long long n, long long F, long long R, const vector<long long>& primes, int t) {
    for (int i = 0; i < t; ++i) {
        int a = randomNum(2, n - 2); 
        long long x = powMod(a, n - 1, n);
        if (x != 1)
            return false;
    }

    for (long long prime : primes) {
        if (NOD(prime, F) == 1) { 
            long long z = (n - 1) / prime;
            bool conditionMet = false;
            for (int i = 0; i < t; ++i) {
                int a = randomNum(2, n - 2); 
                long long res = powMod(a, z, n);
                if (res == 1) {
                    conditionMet = true;
                    break;
                }
            }
            if (!conditionMet) // Если условие не выполнено для хотя бы одного случайного числа, возвращаем false
                return false;
        }
    }

    return true; // Если все условия выполнены, возвращаем true
}
// Функция для построения простого числа заданной длины на основе теста Поклингтона
long long generatePrimePoklington(int bitLength, const vector<long long>& primes, int t) {
    int bitLengthF = 48;
    // Строим число m=q1^a1*q2^a2*...*qk^ak
    unsigned long long F;
    while (true) {
        F = 1;
        for (int i = 0; i < t; ++i) {
            int q = primes[randomNum(0, primes.size() - 1)]; // Случайно выбираем простое число из списка простых чисел
            int a = randomNum(1, 3); // Случайная степень

            long long poweredPrime = 1;
            for (auto i = 0; i < a; ++i) {
                poweredPrime *= q;
            }
            F *= poweredPrime;
        }
        if (getBitLength(F) == bitLengthF) break;
    }
    unsigned long long R;
    do {
        R = randomNum(2, F); 
    } while (R % 2 !=0 and getBitLength(R)!=(bitLengthF-1)); // Проверяем, чтобы число было четным

    unsigned long long n = F * R + 1;

    if (poklingtonTest(n, F, R, primes, t))
        return n; 
    else return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------



// Генерация простого числа по госту
long long GOST(int bitLength, vector <long long>& primes) {
    auto prime = primes[randomNum(0, primes.size() - 1)];;
    double common = pow(2.0, bitLength - 1) / prime;
    long long N = ceil(common) + ceil(common * randomNum(0, RAND_MAX) / static_cast<double>(RAND_MAX));
    N = (N % 2 == 0) ? N : N + 1; 
    for (long long u = 0; true; u += 2){
        long long p = (N + u) * prime + 1;

        if (p > pow(2, bitLength))
            break;

        if (powMod(2, p - 1, p) == 1 and powMod(2, N + u, p) != 1)
            return p;
    }
}



int main() {
    system("chcp 1251");
    int limit = 500;
    vector<long long> primes = sieveOfEratosthenes(limit);
    int k = 0;
    int bitLength = 25; 
    int t = 3;
    long long prime;
    cout << setw(8) << "Число" << setw(16) << "ВерТест" << setw(20) << "Число отвергнутых" << endl;
    cout << "---------------------------------------------" << endl;
    for (auto i = 0; i < 10; i++) {
        prime = 0;
        auto result = generatePrimeMiller(bitLength, primes, t);
        prime = result.first;
        k = result.second;
        
        char testProbRes = testVer(prime, t) ? '+' : '-';
        cout << setw(8)<<prime << setw(13)<<  testProbRes << setw(16)<<  k << endl;
    }
    return 0;
}
