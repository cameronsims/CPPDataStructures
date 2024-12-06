#include "Vector.h"
#include "Test.h"

#include <stdio.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace cslib {
    // Inserting 
    int Vector_test1() {
        Vector<float> v;
        // Push a LOT of values
        for (int i = 0; i < 9999; i++) {
            v.push((float)i);
        }

        // Show test 1 status
        return (v.size() == 9999);
    }

    // Checking
    int Vector_test2() {
        // Create a new vector
        Vector<float> v;
        Vector<float> v2;

        // Create some vals
        for (int i = -10; i < 10; i++) {
            // Push-back values
            v.push((float)i);
        }

        // Assign
        v2 = v;

        // Check that they're the same
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != v2[i]) {
                // They're not the same
                return false;
            }
        }

        return true;
    }

    // Contigious Check
    int Vector_test3() {
        // Create a new vector
        Vector<int> v;

        // Create some random vals
        for (int i = 0; i < 9999; i++) {
            v.push(i);
        }
        // Check that all values are contingous
        for (int i = 0; i < v.size() - 1; i++) {
            // If values aren't contigous
            if (v[i] != (v[i + 1] - 1)) {
                return false;
            }
        }

        return true;
    }

    // Swapping
    int Vector_test4() {
        // Inverse the vector
        Vector<float> v(100000);
        // Loop vals
        for (int i = 0; i < 100000 - 1; i++) {
            // Assign to iteration
            v[i] = i;
        }

        // Now we are going to reverse
        float temp;

        for (int i = 0; i < floor(v.size() / 2); i++) {
            // get the index of the opposite side
            const int opp = (v.size() - 1) - i;
            // Swap the values
            temp = v[opp];
            v[opp] = v[i];
            v[i] = temp;


        }

        // Check if it worked
        for (int i = 0; i < v.size() - 1; i++) {
            // If the next value is bigger, than cancel the loop
            if (v[i] < v[i + 1]) {
                return false;
            }
        }
        return true;
    }

    // Out of Bounds
    int Vector_test5() {
        Vector<float> v(10);

        v[16] = 16.0f;
        return (v.size() == 16 + 1);

    }

    // Size test
    int Vector_test6() {
        Vector<float> v6;

        try {
            v6 = Vector<float>(0);
        } catch (OutOfRange err) {

        }
        return v6.size() == 0;
    }

    // Negative Size 
    int Vector_test7() {
        Vector<float> v7;

        try {
            v7 = Vector<float>(-1);
        } catch (const OutOfRange& err) {

        }

        return (v7.size() != -1);
    }

    // Const Iterators
    int Vector_test8() {
        Vector<int> v;
        for (size_t i = 0; i < 9999; i++) {
            v.push(i);
        }

        size_t i = 0;

        for (Vector<int>::ConstIterator it = v.cbegin(); it != v.cend(); ++it) {
            if (*it != i) {
                return false;
            }

            i++;
        }

        return true;
    }

    // Iterators
    int Vector_test9() {
        Vector<uint8_t> v;
        uint8_t* expected = new uint8_t[9999];
        for (size_t i = 0; i < 9999; i++) {
            v.push(i);
            expected[i] = 9998 - i;
        }

        size_t i = 9999 - 1;
        for (Vector<uint8_t>::Iterator it = v.begin(); it != v.end(); ++it) {
            *it = i;
            i--;
        }

        i = 0;
        for (auto it = v.begin(); it != v.end(); ++it) {
            if (*it != expected[i]) {
                return false;
            }
            i++;
        }

        return true;
    }
}

int main() {
    using namespace cslib;

    constexpr size_t TEST_SIZE = 9;
    testf_t test[TEST_SIZE] = {
        Vector_test1,
        Vector_test2,
        Vector_test3,
        Vector_test4,
        Vector_test5,
        Vector_test6,
        Vector_test7,
        Vector_test8,
        Vector_test9
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