// -----------------------------
//   C++20 Problem Template
//   Fast I/O + Debug + Utils
// -----------------------------
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using ld  = long double;

template<class T> using Vec = vector<T>;
template<class K, class V> using HashMap = unordered_map<K,V>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

// -------- Fast IO ----------
struct FastIO {
    FastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }
} fastio;

// -------- Debug (toggle) ----
#ifdef LOCAL
  #define dbg(x) cerr << "[DBG] " << #x << " = " << (x) << "\n"
#else
  #define dbg(x) ((void)0)
#endif

// -------- Math helpers ------
template<class T> inline T gcd_t(T a, T b){ while(b){ T t=a%b; a=b; b=t; } return a; }
template<class T> inline T lcm_t(T a, T b){ return a / gcd_t(a,b) * b; }
template<class T> inline bool chmin(T& a, const T& b){ if(b < a){ a = b; return true; } return false; }
template<class T> inline bool chmax(T& a, const T& b){ if(a < b){ a = b; return true; } return false; }

// -------- String helpers ----
// trim (both ends)
inline string trim(string s){
    auto L = s.find_first_not_of(" \t\n\r");
    auto R = s.find_last_not_of(" \t\n\r");
    if(L==string::npos) return "";
    return s.substr(L, R-L+1);
}
// lowercase
inline string to_lower(string s){ for(char& c: s) c = (char)tolower(c); return s; }
// split by delimiter (keeps non-empty)
inline vector<string> split(const string& s, char delim){
    vector<string> out; string cur;
    for(char c: s){
        if(c==delim){ if(!cur.empty()) out.push_back(cur); cur.clear(); }
        else cur.push_back(c);
    }
    if(!cur.empty()) out.push_back(cur);
    return out;
}

// KMP prefix function (also used for substring search)
vector<int> prefix_function(const string& s){
    int n = (int)s.size();
    vector<int> pi(n);
    for(int i=1;i<n;i++){
        int j = pi[i-1];
        while(j>0 && s[i]!=s[j]) j = pi[j-1];
        if(s[i]==s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
// Check if pattern t occurs in s using KMP
bool contains_kmp(const string& s, const string& t){
    string u = t + "#" + s;
    auto pi = prefix_function(u);
    for(int v: pi) if(v == (int)t.size()) return true;
    return false;
}

// Longest Palindromic Substring (Manacher’s O(n))
string longest_palindrome(const string& s){
    string t = "^";
    for(char c: s){ t += "#"; t += c; }
    t += "#$";
    int n = (int)t.size();
    vector<int> p(n);
    int center = 0, right = 0, bestLen = 0, bestCenter = 0;
    for(int i=1;i<n-1;i++){
        int mir = 2*center - i;
        if(i < right) p[i] = min(right - i, p[mir]);
        while(t[i + 1 + p[i]] == t[i - 1 - p[i]]) p[i]++;
        if(i + p[i] > right){ center = i; right = i + p[i]; }
        if(p[i] > bestLen){ bestLen = p[i]; bestCenter = i; }
    }
    int start = (bestCenter - bestLen)/2;
    return s.substr(start, bestLen);
}

// -------- DSU (Disjoint Set Union) ----
struct DSU {
    vector<int> p, rnk, sz;
    DSU(int n=0){ init(n); }
    void init(int n){ p.resize(n); rnk.assign(n,0); sz.assign(n,1); iota(all(p),0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return false;
        if(rnk[a]<rnk[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
        if(rnk[a]==rnk[b]) rnk[a]++;
        return true;
    }
    int size(int x){ return sz[find(x)]; }
};

// -------- Read helpers --------
template<class T> void read_vec(vector<T>& v, int n){ v.resize(n); for(int i=0;i<n;i++) cin >> v[i]; }
template<class T> void print_vec(const vector<T>& v, char sep=' '){
    for(int i=0;i<(int)v.size();i++){ if(i) cout << sep; cout << v[i]; }
    cout << "\n";
}

// -------- Solve a sample task --------
// Example: Given a string, print:
// 1) longest palindrome
// 2) whether it contains the word "recruit" (case-insensitive)
// 3) distinct words count (case-insensitive)
void solve_one(){
    string s; 
    // read whole line including spaces
    getline(cin, s);
    s = trim(s);
    if(s.empty()){ cout << "EMPTY\n"; return; }

    string lp = longest_palindrome(s);
    auto words = split(to_lower(s), ' ');
    unordered_set<string> uniq(all(words));
    bool hasRecruit = contains_kmp(to_lower(s), "recruit");

    cout << lp << "\n";
    cout << (hasRecruit ? "YES" : "NO") << "\n";
    cout << uniq.size() << "\n";
}

void solve(){
    // If input is multiple lines, change t and loop.
    // For demo: read one full line and process.
    solve_one();
}

int main(){
    // If your judge feeds with trailing newlines, use this to ensure getline works
    // after previous formatted reads: (not needed here but handy to keep)
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Timing (optional)
    // auto st = chrono::high_resolution_clock::now();

    solve();

    // auto en = chrono::high_resolution_clock::now();
    // cerr << "Time: " << chrono::duration<double,milli>(en-st).count() << " ms\n";
    return 0;
}
