#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

/*  Hex (text) – HW4 starter (finalized)
    - Board drawing (ASCII)
    - Legal position check (Blue starts)
    - Winner detection via Union-Find with virtual borders
    - Simple REPL to play/test positions

    Coordinates: rows 0..N-1 (top->bottom), cols 0..N-1 (left->right)
    Stones: '.' empty, 'B' blue, 'R' red
*/

struct union_find {
    vector<int> parent, rnk;
    explicit union_find(int n) : parent(n), rnk(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find_set(int v) {
        if (parent[v] == v) return v;
        parent[v] = find_set(parent[v]);
        return parent[v];
    }
    void unite(int a, int b) {
        a = find_set(a); b = find_set(b);
        if (a == b) return;
        if (rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
    }
};

struct hex_board {
    int n;
    vector<char> cells; // '.' empty, 'B', 'R'

    explicit hex_board(int n_) : n(n_), cells(n_*n_, '.') {}

    int idx(int r, int c) const { return r * n + c; }

    bool in_bounds(int r, int c) const {
        return 0 <= r && r < n && 0 <= c && c < n;
    }

    // neighbors for even-row offset hex grid
    // even row:    (-1,0),(-1,-1),(0,-1),(0,1),(1,0),(1,-1)
    // odd row:     (-1,0),(-1,1),(0,-1),(0,1),(1,0),(1,1)
    vector<pair<int,int>> neighbors(int r, int c) const {
        static const int dr_even[6] = {-1,-1, 0, 0, 1, 1};
        static const int dc_even[6] = { 0,-1,-1, 1, 0,-1};
        static const int dr_odd [6] = {-1,-1, 0, 0, 1, 1};
        static const int dc_odd [6] = { 0, 1,-1, 1, 0, 1};
        const bool is_even = (r % 2 == 0);
        vector<pair<int,int>> res;
        res.reserve(6);
        for (int k = 0; k < 6; ++k) {
            int nr = r + (is_even ? dr_even[k] : dr_odd[k]);
            int nc = c + (is_even ? dc_even[k] : dc_odd[k]);
            if (in_bounds(nr, nc)) res.emplace_back(nr, nc);
        }
        return res;
    }

    bool place(int r, int c, char who) {
        if (!in_bounds(r, c) || cells[idx(r,c)] != '.') return false;
        if (who != 'B' && who != 'R') return false;
        cells[idx(r,c)] = who;
        return true;
    }

    int count(char who) const {
        return (int)std::count(cells.begin(), cells.end(), who);
    }

    void print() const {
        // Column headers
        cout << "   ";
        for (int c = 0; c < n; ++c) {
            cout << c;
            if (c < n - 1) cout << (c + 1 < 10 ? "  " : " ");
        }
        cout << "\n";
        for (int r = 0; r < n; ++r) {
            // left offset to visualize hex staggering
            cout << string(r*2, ' ');
            cout << setw(2) << r << " ";
            for (int c = 0; c < n; ++c) {
                cout << cells[idx(r,c)];
                if (c != n-1) cout << " - ";
            }
            cout << "\n";
            if (r != n-1) {
                cout << string(r*2 + 3, ' ');
                for (int c = 0; c < n-1; ++c) cout << "\\ / ";
                cout << "\\\n";
            }
        }
        cout << "\n";
    }

    // Build DSU connections for one color, add virtual borders:
    // Blue: connect col 0 to L, col n-1 to R, link adjacent blues; win if L~R
    // Red:  connect row 0 to T, row n-1 to B, link adjacent reds;  win if T~B
    bool has_winner(char who) const {
        const int board_sz = n * n;
        if (who == 'B') {
            const int L = board_sz, R = board_sz + 1;
            union_find uf(board_sz + 2);
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < n; ++c) {
                    if (cells[idx(r,c)] != 'B') continue;
                    int v = idx(r,c);
                    if (c == 0) uf.unite(v, L);
                    if (c == n-1) uf.unite(v, R);
                    for (auto [nr, nc] : neighbors(r, c)) {
                        if (cells[idx(nr,nc)] == 'B') uf.unite(v, idx(nr,nc));
                    }
                }
            }
            return uf.find_set(L) == uf.find_set(R);
        } else if (who == 'R') {
            const int T = board_sz, B = board_sz + 1;
            union_find uf(board_sz + 2);
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < n; ++c) {
                    if (cells[idx(r,c)] != 'R') continue;
                    int v = idx(r,c);
                    if (r == 0) uf.unite(v, T);
                    if (r == n-1) uf.unite(v, B);
                    for (auto [nr, nc] : neighbors(r, c)) {
                        if (cells[idx(nr,nc)] == 'R') uf.unite(v, idx(nr,nc));
                    }
                }
            }
            return uf.find_set(T) == uf.find_set(B);
        }
        return false;
    }

    // Legal position under "Blue starts" rule:
    // - counts: blue_count == red_count OR blue_count == red_count + 1
    // - cannot have both winners
    bool is_legal_position() const {
        int b = count('B'), r_ = count('R');
        if (!(b == r_ || b == r_ + 1)) return false;
        bool bw = has_winner('B');
        bool rw = has_winner('R');
        if (bw && rw) return false;
        // If Blue has won, b must be r_ + 1; if Red has won, b must be r_
        if (bw && !(b == r_ + 1)) return false;
        if (rw && !(b == r_)) return false;
        return true;
    }
};

static void print_help() {
    cout << "Commands:\n"
         << "  n <size>          : new empty board (e.g., n 11)\n"
         << "  b <r> <c>         : place Blue at (r,c)\n"
         << "  r <r> <c>         : place Red  at (r,c)\n"
         << "  show              : print board\n"
         << "  check             : check legality + winner\n"
         << "  clear             : clear board (same size)\n"
         << "  help              : this help\n"
         << "  q                 : quit\n";
}

int main() {
    // Ensure prompts flush in all environments.
    std::cout.setf(std::ios::unitbuf);

    int n = 11;
    hex_board board(n);
    cout << "HEX " << n << "x" << n << " (Blue = E-W, Red = N-S). Blue moves first.\n";
    print_help();
    board.print();
    cout << "Type 'help' for commands.\n";

    string cmd;
    while (true) {
        cout << "> " << std::flush;
        if (!(cin >> cmd)) break;
        if (cmd == "q") break;
        else if (cmd == "help") {
            print_help();
        } else if (cmd == "n") {
            int ns; cin >> ns;
            if (ns < 2 || ns > 26) { cout << "Choose size in [2..26].\n"; continue; }
            n = ns; board = hex_board(n);
            cout << "New " << n << "x" << n << " board.\n";
        } else if (cmd == "clear") {
            board = hex_board(n);
            cout << "Cleared.\n";
        } else if (cmd == "show") {
            board.print();
        } else if (cmd == "b" || cmd == "r") {
            int r, c; cin >> r >> c;
            char who = (cmd == "b" ? 'B' : 'R');
            if (!board.place(r, c, who)) {
                cout << "Illegal placement.\n";
            }
        } else if (cmd == "check") {
            bool legal = board.is_legal_position();
            bool bw = board.has_winner('B');
            bool rw = board.has_winner('R');
            cout << "Legal: " << (legal ? "yes" : "no") << "\n";
            cout << "Blue winner: " << (bw ? "yes" : "no") << "\n";
            cout << "Red  winner: " << (rw ? "yes" : "no") << "\n";
            if (!legal) cout << "(Hint: Blue starts; counts must be B==R or B==R+1. Both sides cannot win.)\n";
        } else {
            cout << "Unknown command. Type 'help'.\n";
        }
        if (cmd != "show") board.print();
    }
    return 0;
}
