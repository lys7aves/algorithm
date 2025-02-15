#include <iostream>
#include <set>

using namespace std;

int n;
int dp[110][110], sz[2][110][110];
set<int> S[2], V[2][2], M;

void split()
{
    V[0][0].clear();
    V[0][1].clear();
    V[1][0].clear();
    V[1][1].clear();

    for(int x=0; x<=1; x++){
        for(auto s: S[x]){
            if(V[x][0].size() < S[x].size()/2) V[x][0].insert(s);
            else V[x][1].insert(s);
        }
    }
}

void merge(set<int> &V1, set<int> &V2)
{
    M.clear();

    for(auto v: V1) M.insert(v);
    for(auto v: V2) M.insert(v);
}

bool question(set<int> &Q){
    cout << "? " << Q.size() << ' ';
    for(auto q: Q) cout << q << ' ';
    cout << '\n';
    cout.flush();

    string str;
    cin >> str;
    if(str == "YES") return true;
    else return false;
}

bool question_(int q){
    cout << "? 1 " << q << '\n';
    cout.flush();

    string answer;
    cin >> answer;
    if(answer == "YES") return true;
    else return false;
}

void correct(int x, int y){
    string answer;

    cout << "! " << x << '\n';
    cout.flush();

    cin >> answer;
    if(answer == ":)") return;

    cout << "! " << y << '\n';
    cout.flush();

    cin >> answer;
    if(answer == ":)") return;
}

void find_answer(int a, int b, int c, bool z){
    int i, j;

    if(z){
        z = question_(b);
        if(z) correct(a, b);
        else{
            z = question_(b);
            if(z){
                z = question_(a);
                if(z) correct(a, c);
                else correct(b, c);
            }
            else correct(a, c);
        }
    }
    else{
        z = question_(b);
        if(z) correct(b, c);
        else{
            z = question_(b);
            if(z){
                z = question_(a);
                if(z) correct(a, b);
                else correct(b, c);
            }
            else correct(a, c);
        }
    }
}

int DP(int x, int y)
{
    if(dp[x][y]) return dp[x][y];
    if(x <= 2) return dp[x][y];
}

int main()
{
    int i, j;
    bool z;

    cin >> n;

    DP(100, 100);

    if(n <= 2){
        correct(1, 2);
        return 0;
    }
    if(n == 3){
        z = question_(1);
        find_answer(1, 2, 3, z);
        return 0;
    }

    for(i=1; i<=n/2; i++) S[0].insert(i);
    for(i=n/2+1; i<=n; i++) S[1].insert(i);
    split();

    z = question(S[0]);
    if(!z){
        M = S[0];
        S[0] = S[1];
        S[1] = M;
    }

    while(1){
        if(S[0].size() == 2 && S[1].size() == 1) break;

        split();
        merge(V[0][1], V[1][0]);

        z = question(M);

        if(z){
            S[0] = M;
            S[1] = V[0][0];
        }
        else{
            merge(V[0][0], V[1][1]);
            S[0] = M;
            S[1] = V[0][1];
        }
    }

    int a, b, c;
    a = *(S[1].begin());
    b = *(S[0].begin());
    c = *(S[0].rbegin());
    find_answer(a, b, c, false);

    return 0;
}