#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    struct Brick {
        float x;
        float y;
        float z;
    };

    void set_size(struct Brick *brick, float x, float y, float z) {
        if(x>0){
            brick->x = x;
        } else { brick->x = abs(x);}
        if(y>0){
            brick->y = y;
        } else { brick->y = abs(y);}
        if(z>0){
            brick->z = z;
        } else { brick->z = abs(z);}
    }

    float calc_volume(struct Brick brick) {
        return brick.x * brick.y * brick.z;
    }

    float calc_surface(struct Brick brick) {
        return 2 * (brick.x * brick.y + brick.x * brick.z + brick.y * brick.z);
    }

    int one_side_cubic(struct Brick brick){
        if(brick.x == brick.y || brick.x == brick.z || brick.y == brick.z){
            return 1;
        } 
        return 0;
    }

    struct Brick brick = {1, 1, 1};

    set_size(&brick,2, 2, 3);

    printf("%f %f %f\n", brick.x, brick.y, brick.z);
    printf("Brick volume: %f\n", calc_volume(brick));
    printf("Brick surface: %f\n", calc_surface(brick));
    if(one_side_cubic(brick)){
        printf("At lest one side is a square\n");
    }else{printf("Dont have a square side");}
    return 0;
}
