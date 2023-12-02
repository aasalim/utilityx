#include "UtilityX.h"

int sign(const int a)
{
    return (a < 0) ? -1 : +1;
}
int min(const int a, const int b)
{
    return (a < b) ? a : b;
}
int max(const int a, const int b)
{
    return (a > b) ? a : b;
}
int clamp(const int value, const int low, const int high)
{
    return min(max(value, low), high);
}
