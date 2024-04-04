#include <iostream>
#include "manager.h"

int main() {
    manager m1 = manager(5);

    m1.writeToStorage("1", "abc", "100");
}