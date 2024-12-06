#include "Test.h"

#include <stdio.h>

void cslib::Datastructure_test(int no, int result) {
    printf("Test #%d: ", no);
    if (result) {
        printf("Success\n");
    } else {
        printf("Failure\n");
    }
}