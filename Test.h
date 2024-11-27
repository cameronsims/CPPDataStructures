#ifndef CSTEST_H
#define CSTEST_H

#define CS_RANGE_TEST(x, e) try { x; return false; } catch (e& err) {  };

namespace cslib {
    void Datastructure_test(int no, int result);
    
    typedef int(*testf_t)(void);
}



#endif