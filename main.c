#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 256
#define GC_TRESHOLD 8

typedef enum {
    OBJ_INT,
    OBJ_PAIR
} ObjectType;

typedef struct sObject {
    ObjectType type;
    unsigned char marked;   //added marking bit

    struct sObject* next;    //added next pointer for linked list

    union {
        int value;

        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

typedef struct {
    Object* stack[STACK_MAX];
    int stackSize;

    Object* firstObject;   //added pointer to first object in linked list

    int numObjects;        //added number of objects in linked list
    int maxObjects;        //added max number of objects before gc
} VM;

void assert(int condition, const char* message) {
    if(!condition) {
        printf("%s\n", message);
        exit(1);
    }
}


// ## START VM CODE ##
// create and initialize VM

VM* newVM() {
    VM* vm = malloc(sizeof(VM));
    vm->stackSize = 0;

    vm->firstObject = NULL; //initialize first object to null

    vm->numObjects = 0; //initialize number of objects to 0
    vm->maxObjects = GC_TRESHOLD; //initialize max number of objects to defined threshold

    return vm;
}

// manipulate vm stack

void push(VM* vm, Object* value) {
    assert(vm->stackSize < STACK_MAX, "Stack overflow!");
    vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm){
    assert(vm->stackSize > 0, "Stack underflow!");
    return vm->stack[--vm->stackSize];
}

//helper function

Object* newObject(VM* vm, ObjectType type){
    if(vm->numObjects == vm->maxObjects) gc(vm); //if number of objects is equal to max number of objects, run gc

    Object* object = malloc(sizeof(Object));
    object->marked = 0;
    object->type = type;

    object->next = vm->firstObject; //add first object to linked list
    vm->firstObject = object;

    vm->numObjects++; //increment number of objects
    return object;
}

//push function for ints and pairs

void pushInt(VM* vm, int intValue){
    Object* object = newObject(vm, OBJ_INT);
    object->value = intValue;
    push(vm, object);
}

Object* pushPair(VM* vm){
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

// ## END VM CODE

//marking function
void mark(Object* object){
    if (object->marked) return; //if already marked, return

    object->marked = 1;

    if (object->type == OBJ_PAIR){
        mark(object->head);
        mark(object->tail);
    }
}


void markAll(VM* vm){
    for(int i = 0; i < vm->stackSize; i++){
        mark(vm->stack[i]);
    }
}

//delete all the unused object
void sweep(VM* vm){
    Object** object = &vm->firstObject;
    while (*object){
        if(!(*object)->marked){
            //object not marked, remove from list and free
            Object* unreached = *object;

            *object = unreached->next;
            free(unreached);
            vm->numObjects--;
        } else {
            //object marked, move on to next
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void gc(VM* vm){
    int numObjects = vm->numObjects;

    markAll(vm);
    sweep(vm);

    vm->maxObjects = vm->numObjects == 0 ? GC_TRESHOLD : vm->numObjects * 2;

    printf("I've collected %d objects, and now I have %d objects remaining\n", numObjects - vm->numObjects, vm->numObjects);
}

void ObjectPrint(Object* object){
    switch(object->type){
        case OBJ_INT:
            printf("%d", object->value);
            break;
        case OBJ_PAIR:
            printf("(");
            ObjectPrint(object->head);
            printf(", ");
            ObjectPrint(object->tail);
            printf(")");
            break;
    }
}

void freeVM(VM* vm){
    vm->stackSize = 0;
    gc(vm);
    free(vm);
}