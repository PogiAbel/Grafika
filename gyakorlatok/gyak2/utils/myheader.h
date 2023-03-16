// example headder file

#ifndef __MYHEADER_H__
#define __MYHEADER_H__

#include <stdio.h>

    void printHelloWorld(){

        printf("Hello World!\n");
    }
    
struct Point
{
    int x;
    int y;
};

struct Line
{
    struct Point p1;
    struct Point p2;
};

struct Circle
{
    struct Point p;
    int r;
};

struct Hpoint
{
    int x;
    int y;
    int w;
};

struct Hline
{
    struct Hpoint p1;
    struct Hpoint p2;
};

struct Point offsetPoint(struct Point p, int dx, int dy){
    p.x += dx;
    p.y += dy;
    return p;
}

#endif