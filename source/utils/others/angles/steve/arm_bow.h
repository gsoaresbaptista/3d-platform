#ifndef SOURCE_UTILS_OTHERS_ANGLES_STEVE_ARM_BOW_H_
#define SOURCE_UTILS_OTHERS_ANGLES_STEVE_ARM_BOW_H_
#include <GL/gl.h>

GLfloat arm_bow[50][22] = {
{ -60,-5,30,0,-65,15,-10,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{ -60,-4.9,30,0,-65,15,-10,32.5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{ -60,-4.8,30,0,-65,15,-10,33,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
{ -60,-4.7,30,0,-65,15,-10,33.5,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
{ -60,-4.6,30,0,-65,15,-10,34,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
{ -60,-4.5,30,0,-65,15,-10,34.5,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
{ -60,-4.4,30,0,-65,15,-10,35,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
{ -60,-4.3,30,0,-65,15,-10,35.5,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{ -60,-4.2,30,0,-65,15,-10,36,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
{ -60,-4.1,30,0,-65,15,-10,36.5,0,0,0,0,0,0,0,0,0,0,0,0,0,9},
{ -60,-4,30,0,-65,15,-10,37,0,0,0,0,0,0,0,0,0,0,0,0,0,10},
{ -60,-3.9,30,0,-65,15,-10,37.5,0,0,0,0,0,0,0,0,0,0,0,0,0,11},
{ -60,-3.8,30,0,-65,15,-10,38,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
{ -60,-3.7,30,0,-65,15,-10,38.5,0,0,0,0,0,0,0,0,0,0,0,0,0,13},
{ -60,-3.6,30,0,-65,15,-10,39,0,0,0,0,0,0,0,0,0,0,0,0,0,14},
{ -60,-3.5,30,0,-65,15,-10,39.5,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
{ -60,-3.4,30,0,-65,15,-10,40,0,0,0,0,0,0,0,0,0,0,0,0,0,16},
{ -60,-3.3,30,0,-65,15,-10,40.5,0,0,0,0,0,0,0,0,0,0,0,0,0,17},
{ -60,-3.2,30,0,-65,15,-10,41,0,0,0,0,0,0,0,0,0,0,0,0,0,18},
{ -60,-3.1,30,0,-65,15,-10,41.5,0,0,0,0,0,0,0,0,0,0,0,0,0,19},
{ -60,-3,30,0,-65,15,-10,42,0,0,0,0,0,0,0,0,0,0,0,0,0,20},
{ -60,-2.9,30,0,-65,15,-10,42.5,0,0,0,0,0,0,0,0,0,0,0,0,0,21},
{ -60,-2.8,30,0,-65,15,-10,43,0,0,0,0,0,0,0,0,0,0,0,0,0,22},
{ -60,-2.7,30,0,-65,15,-10,43.5,0,0,0,0,0,0,0,0,0,0,0,0,0,23},
{ -60,-2.6,30,0,-65,15,-10,44,0,0,0,0,0,0,0,0,0,0,0,0,0,24},
{ -60,-2.5,30,0,-65,15,-10,44.5,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
{ -60,-2.4,30,0,-65,15,-10,45.1,0,0,0,0,0,0,0,0,0,0,0,0,0,26},
{ -60,-2.3,30,0,-65,15,-10,45.7,0,0,0,0,0,0,0,0,0,0,0,0,0,27},
{ -60,-2.2,30,0,-65,15,-10,46.3,0,0,0,0,0,0,0,0,0,0,0,0,0,28},
{ -60,-2.1,30,0,-65,15,-10,46.9,0,0,0,0,0,0,0,0,0,0,0,0,0,29},
{ -60,-2,30,0,-65,15,-10,47.5,0,0,0,0,0,0,0,0,0,0,0,0,0,30},
{ -60,-1.9,30,0,-65,15,-10,48.1,0,0,0,0,0,0,0,0,0,0,0,0,0,31},
{ -60,-1.8,30,0,-65,15,-10,48.7,0,0,0,0,0,0,0,0,0,0,0,0,0,32},
{ -60,-1.7,30,0,-65,15,-10,49.3,0,0,0,0,0,0,0,0,0,0,0,0,0,33},
{ -60,-1.6,30,0,-65,15,-10,49.9,0,0,0,0,0,0,0,0,0,0,0,0,0,34},
{ -60,-1.5,30,0,-65,15,-10,50.5,0,0,0,0,0,0,0,0,0,0,0,0,0,35},
{ -60,-1.4,30,0,-65,15,-10,51.3,0,0,0,0,0,0,0,0,0,0,0,0,0,36},
{ -60,-1.3,30,0,-65,15,-10,52.1,0,0,0,0,0,0,0,0,0,0,0,0,0,37},
{ -60,-1.2,30,0,-65,15,-10,52.9,0,0,0,0,0,0,0,0,0,0,0,0,0,38},
{ -60,-1.1,30,0,-65,15,-10,54.1,0,0,0,0,0,0,0,0,0,0,0,0,0,39},
{ -60,-1,30,0,-65,15,-10,55.3,0,0,0,0,0,0,0,0,0,0,0,0,0,40},
{ -60,-0.900003,30,0,-65,15,-10,56.5,0,0,0,0,0,0,0,0,0,0,0,0,0,41},
{ -60,-0.800003,30,0,-65,15,-10,58.3,0,0,0,0,0,0,0,0,0,0,0,0,0,42},
{ -60,-0.700003,30,0,-65,15,-10,60.1,0,0,0,0,0,0,0,0,0,0,0,0,0,43},
{ -60,-0.600003,30,0,-65,15,-10,62.9,0,0,0,0,0,0,0,0,0,0,0,0,0,44},
{ -60,-0.500003,30,0,-65,15,-10,65.7,0,0,0,0,0,0,0,0,0,0,0,0,0,45},
{ -60,-0.400003,30,0,-65,15,-10,68.5,0,0,0,0,0,0,0,0,0,0,0,0,0,46},
{ -60,-0.300003,30,0,-65,15,-10,71.3,0,0,0,0,0,0,0,0,0,0,0,0,0,47},
{ -60,-0.200003,30,0,-65,15,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,48},
{ -60,-0.100003,30,0,-65,15,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49}
};

GLfloat holding_bow[21][22] = {
{-60,-0.1,30,0,-67.45,15,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-0.35,30,0,-67.45,14.75,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-0.6,30,0,-67.45,14.5,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-0.85,30,0,-67.45,14.25,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.1,30,0,-67.45,14,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.35,30,0,-67.45,13.75,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.6,30,0,-67.45,13.5,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.85,30,0,-67.45,13.25,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-2.1,30,0,-67.45,13,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-2.35,30,0,-67.45,12.75,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-2.6,30,0,-67.45,12.5,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-2.35,30,0,-67.45,12.75,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-2.1,30,0,-67.45,13,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.85,30,0,-67.45,13.25,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.6,30,0,-67.45,13.5,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.35,30,0,-67.45,13.75,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-1.1,30,0,-67.45,14,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-0.85,30,0,-67.45,14.25,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-0.6,30,0,-67.45,14.5,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-0.35,30,0,-67.45,14.75,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49},
{-60,-0.0999999,30,0,-67.45,15,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,49}
};

GLfloat returning_bow[20][22] = {
{-60,-0.1,30,0,-67.45,15,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,60},
{-60,-0.1,30,0,-67.45,15,-10,74.1,0,0,0,0,0,0,0,0,0,0,0,0,0,61},
{-60,-0.1,30,0,-67.45,15,-10,70.6,0,0,0,0,0,0,0,0,0,0,0,0,0,62},
{-60,-0.6,30,0,-67.45,15,-10,69.6,0,0,0,0,0,0,0,0,0,0,0,0,0,63},
{-60,-1.1,30,0,-67.45,15,-10,68.6,0,0,0,0,0,0,0,0,0,0,0,0,0,64},
{-60,-1.6,30,0,-67.45,15,-10,67.6,0,0,0,0,0,0,0,0,0,0,0,0,0,65},
{-60,-2.1,30,0,-67.45,15,-10,66.6,0,0,0,0,0,0,0,0,0,0,0,0,0,66},
{-60,-2.6,30,0,-67.45,15,-10,65.6,0,0,0,0,0,0,0,0,0,0,0,0,0,67},
{-60,-3.1,30,0,-67.45,15,-10,62.6,0,0,0,0,0,0,0,0,0,0,0,0,0,68},
{-60,-3.6,30,0,-67.45,15,-10,59.6,0,0,0,0,0,0,0,0,0,0,0,0,0,69},
{-60,-4.1,30,0,-67.45,15,-10,56.6,0,0,0,0,0,0,0,0,0,0,0,0,0,70},
{-60,-4.6,30,0,-67.45,15,-10,53.6,0,0,0,0,0,0,0,0,0,0,0,0,0,71},
{-60,-5,30,0,-67.45,15,-10,50.6,0,0,0,0,0,0,0,0,0,0,0,0,0,72},
{-60,-5,30,0,-67.45,15,-10,47.6,0,0,0,0,0,0,0,0,0,0,0,0,0,73},
{-60,-5,30,0,-67.45,15,-10,44.6,0,0,0,0,0,0,0,0,0,0,0,0,0,74},
{-60,-5,30,0,-67.45,15,-10,41.6,0,0,0,0,0,0,0,0,0,0,0,0,0,75},
{-60,-5,30,0,-66.45,15,-10,38.6,0,0,0,0,0,0,0,0,0,0,0,0,0,76},
{-60,-5,30,0,-65.45,15,-10,35.2,0,0,0,0,0,0,0,0,0,0,0,0,0,77},
{-60,-5,30,0,-65.00,15,-10,32.0,0,0,0,0,0,0,0,0,0,0,0,0,0,78},
{-60,-5,30,0,-65.00,15,-10,32,0,0,0,0,0,0,0,0,0,0,0,0,0,79}
};

#endif  // SOURCE_UTILS_OTHERS_ANGLES_STEVE_ARM_BOW_H_
