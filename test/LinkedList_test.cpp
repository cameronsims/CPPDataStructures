#include "LinkedList.h"
#include "Test.h"

#include <stdio.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

struct Vector2{
    double x = 0.0, y = 0.0;
};

namespace cslib {
    // Create cont. data
    int LinkedList_test1() {
        cslib::LinkedList<float> ll;

        const size_t n = 256;

        for (size_t i = 0; i < n; i++) {
            float f = (float)i;
            ll.append(f);
            if (ll.size() != i + 1) {
                return false;
            }

        }

        // Get size 
        if (ll.size() != n) {
            return false;
        }

        for (size_t i = 0; i < n; i++) {
            float data = ll[i];
            if (data != (float)i) {
                return false;
            }
        }

        return true;
    }
    
    // Edit cont. data
    int LinkedList_test2() {
        // Size
        constexpr size_t n = 1024;

        // Create a list
        size_t expected[n];
        for (size_t i = 0; i < n; i++) {
            expected[i] = (n - i) - 1;
        }

        // Linked list
        LinkedList<size_t> ll;
        for (size_t i = 0; i < n; i++) {
            ll.append(i);
        }

        // Change data to be inversed.
        for (size_t i = 0; i < n; i++) {
            ll[i] = (n - i) - 1;
            if (ll[i] != expected[i]) {
                return false;
            }
        }

        return true;
    }

    // C-Style adding
    int LinkedList_test3() {
        try {
            LinkedList<char*> ll;
            constexpr size_t n = 1024;
            for (size_t i = 0; i < n; i++) {
                char* str = new char[5];
                sprintf_s(str, 5, "%04llu", i);
                str[4] = '\0';

                ll.append(str);
            }

            for (size_t i = 0; i < n; i++) {
                delete[] ll[i];
            }

            return true;
        } catch (cslib::Exception& e) {
            e;
            return false;
        }
    }

    // Edit order 
    int LinkedList_test4() {
        LinkedList<char> ll;
        char str[] = "Hello World!";
        const size_t n = strlen(str);
        for (size_t i = 0; i < n; i++) {
            ll.append(str[i]);
        }

        for (size_t i = 0; i < (n/2); i++) {
            size_t j = n - i - 1;
            ll.swap(i, j);
        }

        char* newstr = new char[n + 1];
        char* expected = new char[n + 1];
        for (size_t i = 0; i < ll.size(); i++) {
            newstr[i] = ll[i];
            expected[i] = str[n - i - 1];
        }
        newstr[n] = '\0';
        expected[n] = '\0';

        // Check if the frequency of both is the same...
        return (strcmp(newstr, expected) == 0);
    }

    // Insert
    int LinkedList_test5() {
        // Expected
        constexpr size_t n = 1024;
        int expected[n];
        LinkedList<int> ll;

        for (size_t i = 0; i < n; i++) {
            expected[i] = i + 1;
        }

        // Insert at the end.
        for (size_t i = 0; i < n / 2; i++) {
            int data = 2 * i + 2;
            ll.insert(data, i);
        }

        // Now insert inbetween
        for (size_t i = 0; i < n / 2; i++) {
            int data = 2 * i + 1;
            ll.insert(data, 2*i);
        }

        // Now start understanding
        for (size_t i = 0; i < n; i++) {
            if (ll[i] != expected[i]) {
                return false;
            }
        }

        return true;
    }

    // Delete
    int LinkedList_test6() {
        // Create linked list
        LinkedList<Vector2> ll;

        // Data 
        constexpr size_t n = 360;
        constexpr size_t m = 16;
        constexpr double thetas[m] = {
            M_PI * 0.0, 
            M_PI / 6, M_PI / 4, M_PI / 3, 
            M_PI / 2,
            2*M_PI / 3, 3*M_PI / 4, 5*M_PI / 6, 
            M_PI,
            7* M_PI / 6, 5* M_PI / 4, 4* M_PI / 3,
            3 * M_PI / 2,
            5 * M_PI / 3, 7 * M_PI / 4, 11* M_PI / 6
        };

        // Add unit vectors
        for (size_t i = 0; i < n; i++) {
            double theta = thetas[i % m];
            Vector2 v;
            v.x = cos(theta);
            v.y = sin(theta);

            ll.append(v);
        }

        // Remove every non (0) answer
        for (size_t i = 0; i < ll.size(); i++) {
            // If the answer isn't x = 1 and y = 0...
            if (ll[i].x != 1.00 || ll[i].y != 0.00) {
                // Delete, move back
                ll.remove(i);
                i--;
            }
        }

        // Check
        size_t i = 0;
        for (cslib::LinkedList<Vector2>::Iterator it = ll.begin(); it != ll.end(); ++it) {
            if (it->x != 1 && it->y != 0) {
                return false;
            }
            
            i++;
        }

        return true;
    }

    // Iterators 
    int LinkedList_test7() {
        // Add
        constexpr size_t n = 1024;
        LinkedList<int> ll;
        int arr[n];
        for (size_t i = 0; i < n; i++) {
            ll.append(n - i - 1);
            arr[i] = n - i - 1;
        }

        // Check if they're the same
        size_t i = 0;
        for (LinkedList<int>::Iterator it = ll.begin(); it != ll.end(); ++it) {
            if (*it != arr[i]) {
                return false;
            }
            i++;
        }

        return true;
    }

    // Reverse
    int LinkedList_test8() {
        // Expected array
        constexpr size_t n = 1024;
        int expected[n];

        LinkedList<int> ll;

        for (size_t i = 0; i < n; i++) {
            ll.append(i);
            expected[i] = n - i - 1;
        }

        LinkedList_reverse(ll);
        
        size_t i = 0;
        for (LinkedList<int>::ConstIterator it = ll.cbegin(); it != ll.cend(); ++it) {
            if (*it != expected[i]) {
                return false;
            }

            i++;
        }

        return true;
    }

    // Null ptr 
    int LinkedList_test9() {
        // Data 
        LinkedList<int> ll;
        if (ll.size() != 0) {
            return false;
        }

        CS_RANGE_TEST(ll.remove(1), OutOfRange);
        CS_RANGE_TEST( ll[1], OutOfRange);
        CS_RANGE_TEST( ll[1] = 1, OutOfRange);

        return true;
    }

    // Delete the last 
    int LinkedList_test10() {
        LinkedList<int> ll;
        for (int i = 0; i < 10; i++) {
            ll.insert(i, i);
        }

        ll.remove(9);

        CS_RANGE_TEST(ll[9], OutOfRange);
    }
}



typedef int(*testf_t)(void);

int main() {
    using namespace cslib;

    constexpr size_t TEST_SIZE = 10;
    testf_t test[TEST_SIZE] = { 
        LinkedList_test1,
        LinkedList_test2,
        LinkedList_test3,
        LinkedList_test4,
        LinkedList_test5,
        LinkedList_test6,
        LinkedList_test7,
        LinkedList_test8,
        LinkedList_test9,
        LinkedList_test10
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