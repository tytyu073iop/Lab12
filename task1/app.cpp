#include <iostream>
#include <set>

int main() {
    std::cout << "Enter N:";
    size_t N = 0; //NOLINT
    std::cin >> N;
    std::set<size_t> s;
    for (size_t i = 2; i <= N; i++) {
        s.insert(i);
    }
    for (auto i = s.begin(); i != s.end(); i++) {
        // std::cout << "\tDEBUG: " << "Cycle began\n";
        auto j = i;
        for (j++; j != s.end();) {
        // std::cout << "\tDEBUG: " << "Cycle " << *j << "began\n";
            if (*j % *i == 0) {
                auto q = j++;
                s.erase(q);
            } else {
                j++;
            }
        }
    }
    if (s.empty()) {
        std::cout << "No numbers\n";
        return 0;
    }
    std::cout << "Numbers:\n";
    for_each(s.begin(), s.end(), [](const auto& i){ std::cout << i << ' '; });
    return 0;
}
