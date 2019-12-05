# include <bits/stdc++.h>

using namespace std;

int main() {
    int pb, qb, cb, nb, db, fib;
    cin >> pb >> qb >> db >> cb >> fib >> nb;
    if (pb * qb != nb || (qb - 1) * (pb - 1) != fib || __gcd(db, fib) != 1 || (cb * db) % fib != 1){
        cout << "bad";
    }
}

