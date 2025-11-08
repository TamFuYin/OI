#include <bits/stdc++.h>
using namespace std;

struct Simplex {
    int m, n;
    vector<vector<double>> a;
    vector<int> B, N;

    Simplex(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c) {
        m = (int)A.size();
        n = (int)A[0].size();
        a.assign(m+1, vector<double>(n+1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) a[i][j] = A[i][j];
            a[i][n] = b[i];
        }
        for (int j = 0; j < n; j++) a[m][j] = -c[j];
        B.resize(m);
        N.resize(n+1);
        for (int i = 0; i < m; i++) B[i] = n+i;
        for (int j = 0; j < n; j++) N[j] = j;
        N[n] = -1;
    }

    void pivot(int r, int s) {
        double inv = 1.0 / a[r][s];
        for (int j = 0; j <= n; j++) if (j != s) a[r][j] *= inv;
        a[r][s] = inv;
        for (int i = 0; i <= m; i++) if (i != r && fabs(a[i][s]) > 1e-12) {
            double d = a[i][s];
            a[i][s] = 0;
            for (int j = 0; j <= n; j++) a[i][j] -= d * a[r][j];
        }
        swap(B[r], N[s]);
    }

    tuple<int,double,vector<double>> solve(bool want_x) {
        int r, s;
        while (true) {
            s = -1;
            for (int j = 0; j < n; j++) if (s == -1 || a[m][j] < a[m][s]) s = j;
            if (a[m][s] >= -1e-12) break;
            r = -1;
            for (int i = 0; i < m; i++) {
                if (a[i][s] > 1e-12) {
                    if (r == -1 || a[i][n] / a[i][s] < a[r][n] / a[r][s]) r = i;
                }
            }
            if (r == -1) return std::make_tuple(-1, 0.0, vector<double>()); // Unbounded
            pivot(r, s);
        }
        vector<double> x;
        if (want_x) {
            x.assign(n, 0);
            for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = a[i][n];
        }
        return std::make_tuple(0, a[m][n], want_x ? x : vector<double>());
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    if (!(cin >> n >> m >> t)) return 0;
    vector<double> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    vector<vector<double>> A(m, vector<double>(n));
    vector<double> b(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) cin >> A[i][j];
        cin >> b[i];
    }

    Simplex solver(A, b, c);
    auto res = solver.solve(t == 1);
    int status = std::get<0>(res);
    double val = std::get<1>(res);
    vector<double> x = std::get<2>(res);

    if (status == -1) {
        cout << "Unbounded\n";
    } else if (status == 1) {
        cout << "Infeasible\n";
    } else {
        cout << fixed << setprecision(6) << val << "\n";
        if (t == 1) {
            for (int i = 0; i < (int)x.size(); i++) {
                cout << fixed << setprecision(6) << x[i] << (i+1 == (int)x.size() ? '\n' : ' ');
            }
        }
    }
}
