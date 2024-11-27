#include "Stack.h"
#include "Test.h"

#include <stdio.h>
#include <string.h>

namespace cslib {
    // Push test
    int Stack_test1() {
        constexpr size_t n = 1000;
        Stack<int> s;
        int expected[n];

        for (size_t i = 0; i < n; i++) {
            s.push(i);
            expected[n - i - 1] = i;
        }

        for (size_t i = 0; i < n; i++) {
            int val = s.pop();
            if (expected[i] != val) {
                return false;
            }
        }

        return true;
    }

    // Nothing test
    int Stack_test2() {
        // Empty stack
        Stack<int> s;
        
        CS_RANGE_TEST( s.pop(), StackUnderflow );
        CS_RANGE_TEST( s.top(), StackUnderflow);

        return true;
    }

    // Copy test
    int Stack_test3() {
        // Push
        constexpr size_t n = 1024;
        Stack<int> s1;
        for (size_t i = 0; i < n; i++) {
            s1.push(i);
        }

        Stack<int> s2 = s1;

        while (!s1.empty()) {
            int left = s1.pop();
            int right = s2.pop();

            if (left != right) {
                return false;
            }
        }

        return true;
    }


}



typedef int(*testf_t)(void);

int main() {
    using namespace cslib;

    constexpr size_t TEST_SIZE = 3;
    testf_t test[TEST_SIZE] = {
        Stack_test1,
        Stack_test2,
        Stack_test3
    };
    
    for (int i = 0; i < TEST_SIZE; i++) {
        int result = test[i]();
        cslib::Datastructure_test(i + 1, result);
        if (!result) {
            return i + 1;
        }
    }

    return 0;
}