#include <bits/stdc++.h>

using namespace std;

bool check_prime(long long p) {
    long long sq = sqrt(p);
    for (long long i = 2; i <= sq; i++) {
        if (p % i == 0) {
            return false;
        }
    }
    return true;
}


long long random_prime() {
    long long p = rand() % 10000 + 100;
    while (!check_prime(p)) {
        p++;
    }
    return p;
}

long long find_d(long long from, long long fi) {
    from++;
    while (__gcd(fi, from) != 1 || from % 2 == 0) {
        from++;
    }
    return from;
}

long long find_c(long long d, long long fi) {
    long long c = 2;
    while ((c * d) % fi != 1) {
        c++;
        if (c > 1000000) {
            return -1;
        }
    }
    return c;
}

long long bin_pow(long long a, long long b, long long mo) {
    if (b == 1) {
        return a % mo;
    } else if (b % 2 == 1) {
        return (bin_pow(a, b - 1, mo) * a) % mo;
    } else {
        long long ans = bin_pow(a, b / 2, mo) % mo;
        return (ans * ans) % mo;
    }
}

long long encAndDec(long long text, long long d, long long n) {
    return bin_pow(text, d, n) % n;
}


int main() {
    srand(time(0));
    long long text;
    cin >> text;

/*    tryAgainForAlice:

    long long pa = random_prime();
    long long qa = random_prime();
    long long na = pa * qa;
    long long fia = (pa - 1) * (qa - 1);
    long long da = 1;
    long long ca;
    while (true) {
        da = find_d(da, fia);
        if (da >= fia || da >= 10000) {
            goto tryAgainForAlice;
        }
        ca = find_c(da, fia);
        if (ca != -1)
            break;
    }*/
/*
    if((c * d) % fi != 1){
        cout << "cd mod fi";
    }
    if(d >= fi){
        cout <<"d < fi";
    }

    if(__gcd(d , fi) != 1){
        cout << "__gcd(d, fi) == 1";
    }
*/


    tryAgainForBob:

    long long pb = random_prime();
    long long qb = random_prime();
    long long nb = pb * qb;
    long long fib = (pb - 1) * (qb - 1);
    long long db = 1;
    long long cb;
    while (true) {
        db = find_d(db, fib);
        if (db >= fib || db >= 10000) {
            goto tryAgainForBob;
        }
        cb = find_c(db, fib);
        if (cb != -1)
            break;
    }
   // pb = 29, qb = 31, nb = 899, fib = 840, db = 11, cb = 611;
    long long textEncForBob = encAndDec(text, db, nb);
    long long textDecBob = encAndDec(textEncForBob, cb, nb);
    cout << text<<' '<<textEncForBob<<' '<<textDecBob<<'\n';
}