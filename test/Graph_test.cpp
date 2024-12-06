#include "Graph.h"
#include "Test.h"

#include <stdio.h>
#include <string.h>
#include <string>


namespace cslib {
    // Koningsberg Bridges
    int Graph_test1() {
        // Data isn't important here.

        //      o-
        //     / \ \
        //     \ /  \
        //      o----o
        //     / \  /
        //     \ / /
        //      o-

        constexpr size_t n = 4;
        Graph<int> graph;

        size_t north = graph.insert(0);
        size_t center = graph.insert(1);
        size_t south = graph.insert(2);
        size_t east = graph.insert(3);

        graph.connect(center, north);
        graph.connect(center, north);

        graph.connect(center, south);
        graph.connect(center, south);

        graph.connect(east, north);
        graph.connect(east, center);
        graph.connect(east, south);

        // If not good size...
        if (graph.size() != n) {
            return false;
        }

        // If the values don't match up to what they should be
        size_t nodes[n] = { north, center, south, east };
        for (size_t i = 0; i < n; i++) {
            if (graph[i] != nodes[i]) {
                return false;
            }
        }

        return true;
    }

    // Disconnecting Test
    int Graph_test2() {
        constexpr size_t n = 9;
        Graph<size_t> g;

        //
        // 0 - 1 - 2
        // |   |   |
        // 3 - 4 - 5
        // |   |   |
        // 6 - 7 - 8
        //

        for (size_t i = 0; i < n; i++) {
            g.insert(i);
        }

        // Add connnections 
        g.connect(0, 1);
        g.connect(1, 2);

        g.connect(0, 3);
        g.connect(1, 4);
        g.connect(2, 5);

        g.connect(3, 4);
        g.connect(4, 5);

        g.connect(3, 6);
        g.connect(4, 7);
        g.connect(5, 8);

        g.connect(6, 7);
        g.connect(7, 8);

        // If not amount of sizes
        if (g.size() != n) {
            return false;
        }

        // This is the one we remove
        const size_t a = 4;

        // Remove 4
        g.remove(a);

        // Search for 4
        bool success = true;
        auto search = [&](size_t b) {  
            if (b == a) {
                success = false;
            }
        };

        for (size_t i = 0; i < n; i++) {
            if (i != a) {
                success = true;
                g.breadthFirst(i, search);
                if (!success) {
                    return false;
                }

                success = true;
                g.depthFirst(i, search);
                if (!success) {
                    return false;
                }
            }
        }

        return true;
    }

    // Depth/Breadth First testing
    int Graph_test3() {
        //         0 
        //       /   \
        //      2     5
        //     / \   / \
        //    1   3 4   6
        //     \  | |  /
        //      \ | | /
        //       \| |/
        //         7
        Graph<int> g;

        constexpr size_t n = 8;
        constexpr bool directed = true;

        const int depthfirst[n] = { 0, 5, 6, 7, 4, 2, 3, 1 };
        const int breadthfirst[n] = { 0, 2, 5, 1, 3, 4, 6, 7 };

        for (size_t i = 0; i < n; i++) {
            g.insert(i);
        }

        g.connect(0, 2, directed);
        g.connect(0, 5, directed);

        g.connect(2, 1, directed);
        g.connect(2, 3, directed);

        g.connect(5, 4, directed);
        g.connect(5, 6, directed);

        g.connect(1, 7, directed);
        g.connect(3, 7, directed);
        g.connect(4, 7, directed);
        g.connect(6, 7, directed);

        // Lambdas
        bool correct = true;

        auto ldepth = [&](int a) {
            static size_t i = 0;
            if (a != depthfirst[i]) {
                correct = false;
            }
            i++;
        };
        auto lbreadth = [&](int a) {
            static size_t i = 0;
            if (a != breadthfirst[i]) {
                correct = false;
            }
            i++;
        };

        g.depthFirst(0, ldepth);
        g.breadthFirst(0, lbreadth);

        return correct;
    }

    // Disconnected Graph Testing
    int Graph_test4() {
        // 
        // 0 - 1
        // | /
        // 3   2
        //

        Graph<int> g;
        g.insert(0);
        g.insert(1);
        g.insert(2);
        g.insert(3);

        g.connect(0, 1);
        g.connect(0, 3);
        g.connect(1, 3);

        // Disconnect 2
        g.connect(1, 2);
        g.connect(3, 2);
        g.disconnect(1, 2);
        g.disconnect(3, 2);

        // Invalid check 
        bool correct = true;
        auto isMissing = [&](int a) {
            if (a == 2) {
                correct = false;
            }
        };

        auto isOnlyConnected = [&](int a) {
            if (a != 2) {
                correct = true;
            }
        };

        g.breadthFirst(0, isMissing);
        g.depthFirst(0, isMissing);

        if (!correct) { return false; }

        g.depthFirst(2, isOnlyConnected);
        if (!correct) { return false; }

        g.depthFirst(2, isOnlyConnected);

        return correct;
    }

    // Directed Graph Testing
    int Graph_test5() {

        // 0
        //  \
        //   1 -> 2 -> 3 -> 4 -> 5 -> 6
        //  /
        // 0
        
        constexpr size_t n = 7;
        int arr[n] = { 0, 1, 2, 3, 4, 5, 6 };

        Graph<int> g;

        g.insert(0);
        g.insert(0);
        for (size_t i = 1; i < n; i++) {
            g.insert(i);
        }

        g.connect(0, 2, true);
        g.connect(1, 2, true);

        for (size_t i = 3; i < n + 1; i++) {
            g.connect(i - 1, i, true);
        }

        size_t start = 0;
        bool correct = true;
        auto lambda = [&](int a) {
            size_t i = start;
            if (arr[i] != a) {
                correct = false;
            }
            start++;
        };

        start = 0;
        g.depthFirst(0, lambda);
        for (size_t i = 0; i < n; i++) {
            start = i;
            g.depthFirst(i + 1, lambda);
        }

        return correct;
    }

    // Border checking
    int Graph_test6() {
        constexpr size_t n = 7;
        enum Countries {
            POL = 0,
            LIT,
            LAT,
            EST,
            BEL,
            RUS,
            UKR
        };
        std::string names[n] = {
            "Poland",
            "Lithuania",
            "Latvia",
            "Estonia",
            "Belarus",
            "Russia",
            "Ukraine"
        };

        //       EST ----------
        //        |            \
        //       LAT --------- RUS
        //        |   \        //
        // RUS - LIT  - BEL ---/
        //  |  /       / |    /
        // POL  ------   |   /
        //  |            |  /
        //  \            | /
        //   ---------- UKR

        Graph<Countries> easteur;
        for (size_t i = 0; i < n; i++) {
            easteur.insert((Countries)i);
        }

        // Border Matrix
        bool border_matrix[n][n] = {
                      /* POL LIT LAT EST BEL RUS UKR */
            /* POL */ {   0,  1,  0,  0,  1,  1,  1 },
            /* LIT */ {   1,  0,  1,  0,  1,  1,  0 },
            /* LAT */ {   0,  1,  0,  0,  1,  1,  0 },
            /* EST */ {   0,  0,  1,  0,  0,  1,  0 },
            /* BEL */ {   1,  1,  1,  0,  0,  1,  1 },
            /* RUS */ {   1,  1,  1,  1,  1,  1,  1 },
            /* UKR */ {   1,  0,  0,  0,  1,  1,  0 }
        };

        // Create a new border matrix 
        bool matrix[n][n];

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (border_matrix[i][j]) {
                    easteur.connect(i, j, true);
                }

                matrix[i][j] = false;
            }
        }

        // Exists
        auto exists = [](const LinkedList<size_t>& v, size_t a) {
            for (auto it = v.cbegin(); it != v.cend(); ++it) {
                if (*it == a) {
                    return true;
                }
            }

            return false;
        };

        // For all possible combinations, find if it fits the matrix
        for (size_t i = 0; i < n; i++) {
            // Get neighbours
            LinkedList<size_t>& neighbors = easteur.neighbours(i);

            for (size_t j = 0; j < n; j++) {
                // If (j) country is in the neighbours of (i) it is a bordering country
                if (exists(neighbors, j)) {
                    //printf("%s borders %s\n", names[i].c_str(), names[j].c_str());
                    matrix[i][j] = true;
                }
            }
        }

        // Check if they're all correct
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (border_matrix[i][j] != matrix[i][j]) {
                    return false;
                }
            }
        }

        return true;

    }

    // Spacing
    int Graph_test7() {
        // Coordinates
        struct Coordinate { 
            int x; 
            int y;
        };

        // Create a box, 5x5

        //  o--o--o--o--o
        //  |  |  |  |  |
        //  o--o--o--o--o
        //  |  |  |  |  |
        //  o--o--o--o--o
        //  |  |  |  |  |
        //  o--o--o--o--o
        //  |  |  |  |  |
        //  o--o--o--o--o

        constexpr size_t w = 5;
        constexpr size_t h = 5;

        Graph<Coordinate> g;

        for (size_t i = 0; i < w; i++) {
            for (size_t j = 0; j < h; j++) {
                // Create coordinates
                Coordinate c;
                c.x = i + 1;
                c.y = j + 1;
                
                g.insert(c);
            }
        }

        // Check if it is valid
        for (size_t i = 0; i < w; i++) {
            for (size_t j = 0; j < h; j++) {
                Coordinate& c = g[ w*i + j ];

                if (c.x != i + 1 || c.y != j + 1) {
                    return false;
                }
            }
        }

        return true;
    }

    // Complex removal test
    int Graph_test8() {
        //  0 - - - 1
        //  | \   / |
        //  |   4   |
        //  | /   \ |
        //  2 - - - 3

        constexpr size_t n = 5;
        const size_t a = n - 1;
        bool correct = true;

        Graph<int> g;
        for (size_t i = 0; i < n; i++) {
            g.insert(i);
        }

        g.connect(0, 1);
        g.connect(0, 2);

        g.connect(1, 3);
        g.connect(2, 3);

        for (size_t i = 0; i < a; i++) {
            g.connect(i, a);
            g.connect(i, a, true);
        }

        // Remove it 
        g.remove(a);

        // Ensure it is deleted
        for (size_t i = 0; i < a; i++) {
            correct = true;
            LinkedList<size_t> ll = g.neighbours(i);
            for (auto it = ll.begin(); it != ll.end(); ++it) {
                if (*it == a) {
                    correct = true;
                }
            }
            
            if (!correct) {
                return false;
            }
        }

        // Add it in
        g.insert(a);

        // Connect it
        for (size_t i = 0; i < a; i++) {
            g.connect(i, a);
        }

        // Ensure it is now connected.
        for (size_t i = 0; i < a; i++) {
            correct = false;
            
            LinkedList<size_t>& ll = g.neighbours(i);
            for (auto it = ll.begin(); it != ll.end(); ++it) {
                if (*it == a) {
                    correct = true;
                }
            }

            if (!correct) {
                return false;
            }
        }

        return correct;
    }

    // Ensure everything was connected correctly
    int Graph_test9() {
        
        // (0)->(3)-
        //  |    ^   \
        //  |    |    \
        //  |    |     \
        //  |    |      \
        //  |    |       \
        // (1)->(2)----->(4)

        // Matrix
        constexpr size_t n = 5;
        bool correct = true;
        bool matrix[n][n] = {
            /*       0  1  2  3  4  */
            /* 0 */{ 0, 1, 0, 1, 0 },
            /* 1 */{ 1, 0, 1, 0, 0 },
            /* 2 */{ 0, 0, 0, 1, 1 },
            /* 3 */{ 0, 0, 0, 0, 1 },
            /* 4 */{ 0, 0, 0, 1, 0 }
        };

        // Connect
        Graph<int> g;
        for (size_t i = 0; i < n; i++) {
            g.insert(i);
        }
        
        g.connect(0, 1);
        g.connect(0, 3, true);
        g.connect(1, 2, true);
        g.connect(2, 3, true);
        g.connect(2, 4, true);
        g.connect(3, 4);
        
        for (size_t i = 0; i < n; i++) {
            LinkedList<size_t>& ll = g.neighbours(i);
            for (size_t j = 0; j < ll.size(); j++) {
                // If the value is in the matrix.
                if (matrix[i][j] && !LinkedList_contains(ll, j)) {
                    correct = false;
                }
                j++;
            }
        }
    
        return correct;
    }

    // Loops!
    int Graph_test10() {
    
        //      ___         ___
        //     /   \       /   \
        //    |     |     |     |
        //     \___(0)---(2)___/
        //          |     |
        //          |     |
        //          |     |
        //       --(1)---(3)---
        //     /    |     |    \
        //    |     |     |     |
        //     \___/       \___/
        //

        constexpr size_t n = 4;
        bool matrix[n][n] = {
            /*       0  1  2  3 */
            /* 0 */{ 1, 1, 1, 0 },
            /* 1 */{ 1, 1, 0, 1 },
            /* 2 */{ 1, 0, 1, 1 },
            /* 3 */{ 0, 1, 1, 1 }
        };

        Graph<int> g;
        bool correct = true;

        for (size_t i = 0; i < n; i++) {
            g.insert(i);
        }

        g.connect(0, 0);
        g.connect(0, 1);
        g.connect(0, 2);

        g.connect(1, 1);
        g.connect(1, 3);

        g.connect(2, 2);
        g.connect(2, 3);
        
        g.connect(3, 3);

        for (size_t i = 0; i < n; i++) {
            LinkedList<size_t>& ll = g.neighbours(i);

            for (auto it = ll.begin(); it != ll.end(); ++it) {
                printf("%llu ", *it);
            }
            printf("\n");

            for (size_t j = 0; j < ll.size(); j++) {
                // If the value is in the matrix.
                if (matrix[i][j] && !LinkedList_contains(ll, j)) {
                    correct = false;
                }
                j++;
            }
        }
    
        return correct;
    }
}



typedef int(*testf_t)(void);

int main() {
    using namespace cslib;

    constexpr size_t TEST_SIZE = 10;
    testf_t test[TEST_SIZE] = {
        Graph_test1,
        Graph_test2,
        Graph_test3,
        Graph_test4,
        Graph_test5,
        Graph_test6,
        Graph_test7,
        Graph_test8,
        Graph_test9,
        Graph_test10
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