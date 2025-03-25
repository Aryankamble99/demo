/*#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data d;

    d.i = 10;
    printf("Integer: %d\n", d.i);

    d.f = 22.5;
    printf("Float: %f\n", d.f);

    
    sprintf(d.str, "Hello");
    printf("String: %s\n", d.str);

    // Printing overwritten values
    printf("After storing string:\n");
    printf("Integer: %d\n", d.i);
    printf("Float: %f\n", d.f);

    return 0;
}
/*
*///------------------------------------------------
//union with pointers
/*
#include <stdio.h>

union Value {
    int *pInt;
    float *pFloat;
};

int main() {
    int a = 10;
    float b = 20.5;

    union Value val;

    val.pInt = &a;
    printf("Integer Pointer Value: %d\n", *val.pInt);

    val.pFloat = &b;
    printf("Float Pointer Value: %.2f\n", *val.pFloat);

    return 0;
}

*/
//---------------------------------------------------

// Checking Endianness 
/*
#include <stdio.h>

union Endian 
{
    unsigned int num;
    char byte;
};

int main() {
    union Endian e;
    e.num = 0x10000001; // 0x00000001
    printf("%x\n",e.num);

    if (e.byte == 1)
        printf("Little Endian\n");
    else
        printf("Big Endian\n");

    return 0;
}*/

//------------------------------------------
/*
#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() 
{
    union Data d, *ptr;

    ptr = &d; // Pointer to union

    ptr->i = 10;
    printf("Integer: %d\n", ptr->i);

    ptr->f = 5.5; // Overwrites previous value
    printf("Float: %.2f\n", ptr->f);

    sprintf(ptr->str, "Hello"); // Overwrites previous value
    printf("String: %s\n", ptr->str);

    return 0;
}
*/
//-------------------------------------
//Array of Union

/*
#include <stdio.h>

union Data {
    int i;
    float f;
};

int main() {
    union Data arr[2];

    arr[0].i = 100;
    arr[1].f = 3.14;

    printf("First Element (int): %d\n", arr[0].i);
    printf("Second Element (float): %.2f\n", arr[1].f);

    return 0;
}
*/
