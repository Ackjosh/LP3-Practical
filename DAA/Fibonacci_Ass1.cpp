#include <bits/stdc++.h>
using namespace std;

int fiborec(int n){
    if(n <= 1){
        return n;
    }
    return fiborec(n-1) + fiborec(n-2);
}

int fiboiterative(int n){
    if(n<=1) return 1;

    int prev2 = 0, prev1 = 1;
    for(int i=2; i<=n; i++){
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main(){
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    cout << "The " << n << "th fibonacci number is: " << fiborec(n) << endl;
    cout << "The " << n << "th fibonacci number is: " << fiboiterative(n) << endl;

    return 0;
}