#include "xTemplate.h"

int constrain(int value, int low, int high)
{
    if (value < low) {
        return low;
    } else {
        return (value > high ? high : value);
    }
}
