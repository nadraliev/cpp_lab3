#include <iostream>
#include "deque.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    deque<int> d = deque<int>();
    d.emplace_back(1);
    d.emplace_back(2);
    d.emplace_back(3);
    printf("%d\n", d.dequeu_back());
    for (deque<int>::reverse_iterator iter = d.rbegin(); iter != d.rend(); iter++) {
        printf("%d\n", *iter);
    }
    return 0;
}