#include "main.c"

void test1() {
    printf("Test 1: Objects on stack are preserved.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);

    gc(vm);
    assert(vm->numObjects == 2, "Should have preserved objects.\n");
    freeVM(vm);
}

void test2() {
    printf("Test 2: Unreached objects are collected.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pop(vm);
    pop(vm);

    gc(vm);
    assert(vm->numObjects == 0, "Should have collected objects.\n");
    freeVM(vm);
}

void test3() {
    printf("Test 3: Reach nested objects.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pushPair(vm);
    pushInt(vm, 3);
    pushInt(vm, 4);
    pushPair(vm);
    pushPair(vm);

    gc(vm);
    assert(vm->numObjects == 7, "Should have collected objects.\n");
    freeVM(vm);
}

void test4() {
    printf("Test 4: Handle cycles.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    Object* a = pushPair(vm);
    pushInt(vm, 3);
    pushInt(vm, 4);
    Object* b = pushPair(vm);

    a->tail = b;
    b->tail = a;

    gc(vm);
    assert(vm->numObjects == 4, "Should have collected objects.\n");
    freeVM(vm);
}

void perfTest() {
    printf("Performance Test: Create lots of objects.\n");
    VM* vm = newVM();
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 20; j++) {
            pushInt(vm, i);
        }
        for (int j = 0; j < 20; j++) {
            pop(vm);
        }
    }
    freeVM(vm);
}

int main(int argc, const char * argv[]) {
    int test = 0;
    
    printf("Insert test here: \n");
    scanf("%d", &test);
    switch(test){
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3();
            break;
        case 4:
            test4();
            break;
        case 5:
            perfTest();
            break;
        default:
            printf("Invalid test number");
            break;
    }
    return 0;
}