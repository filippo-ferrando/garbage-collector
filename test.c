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

void test5() {
    printf("Test 5: Handle large number of objects.\n");
    printf("Insert number of objects: ");
    int nOb = 0;
    scanf("%d", &nOb);
    VM* vm = newVM();
    for (int i = 0; i < nOb; i++) {
        pushInt(vm, i);
    }
    for (int i = 0; i < nOb; i++) {
        pop(vm);
    }

    gc(vm);
    assert(vm->numObjects == 0, "Should have collected objects.\n");
    freeVM(vm);
}

void test6(){
    printf("Print objects in the list (int).\n");
    VM* vm = newVM();

    Object* object_int_1 = newObject(vm, OBJ_INT);
    object_int_1->value = 1;
    push(vm, object_int_1);

    Object* object_int_2 = newObject(vm, OBJ_INT);
    object_int_2->value = 2;
    push(vm, object_int_2);

    ObjectPrint(object_int_1);
    ObjectPrint(object_int_2);

    gc(vm);
    assert(vm->numObjects == 2, "Should have preserved objects.\n");
    freeVM(vm);
}

void test7(){
    printf("Print objects in the list (pair).\n");
    VM* vm = newVM();

    //first int
    Object* object_int_1 = newObject(vm, OBJ_INT);
    object_int_1->value = 1;
    push(vm, object_int_1);

    //second int
    Object* object_int_2 = newObject(vm, OBJ_INT);
    object_int_2->value = 2;
    push(vm, object_int_2);

    //first pair
    Object* object_pair_1 = newObject(vm, OBJ_PAIR);
    object_pair_1->head = pop(vm);
    object_pair_1->tail = pop(vm);
    push(vm, object_pair_1);

    ObjectPrint(object_pair_1);

    gc(vm);
    assert(vm->numObjects == 3, "Should have preserved objects.\n");
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
            test5();
            break;
        case 6:
            test6();
            break;
        case 7:
            test7();
            break;
        case 8:
            perfTest();
            break;
        default:
            printf("Invalid test number");
            break;
    }
    return 0;
}