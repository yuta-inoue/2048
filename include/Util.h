#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
#include <cmath>
#include <cstring>

using namespace std;

// define data structures
typedef pair<int,int> P; // first x, second y;

// define consts
#define FIELD_SIZE 4
// function declarations
bool isValid(P pos);
P getVector(int direction);
void printV(P v);

#endif
