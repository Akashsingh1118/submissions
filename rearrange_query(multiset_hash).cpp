#include <iostream>
#include <vector>
#include <random>
using namespace std;

/**
 * problem link - https://atcoder.jp/contests/abc367/tasks/abc367_f
 * No idea
 */
const long long mod = (1LL << 61) - 1;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        A[i]--;
    }
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
        B[i]--;
    }

    vector<long long> hash(N);
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> dis(1, mod - 1);

    for (int i = 0; i < N; i++)
    {
        hash[i] = dis(gen);
    }

    vector<long long> cumA(N + 1, 0), cumB(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        cumA[i + 1] = (cumA[i] + hash[A[i]]) % mod;
        cumB[i + 1] = (cumB[i] + hash[B[i]]) % mod;
    }

    for (int i = 0; i < Q; i++)
    {
        int l, r, L, R;
        cin >> l >> r >> L >> R;
        long long hashA = (cumA[r] - cumA[l - 1] + mod) % mod;
        long long hashB = (cumB[R] - cumB[L - 1] + mod) % mod;
        if (hashA == hashB)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}
