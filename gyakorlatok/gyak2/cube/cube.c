#include "myheader.h"
#include <stdio.h>

int main(int argc, char const *argv[]){

    struct Point p1 = {1, 2};
    printf("p1.x = %d, p1.y = %d", p1.x, p1.y);
    p1 = offsetPoint(p1, 3, 4);
    printf("p1.x = %d, p1.y = %d", p1.x, p1.y);
    return 0;
}
