#include "UtilityX.h"
namespace X {

template <typename T>
constexpr T sign(const T a)
{
    return (a < 0) ? -1 : +1;
    /**
     *  sign(int):
     *      ; start of prologue
     *      PUSHM.W #1, R4
     *      MOV.W   R1, R4
     *      ; end of prologue
     *
     *      CMP.W   #0, R12 { JL  .L3
     *      MOV.B   #1, R12
     *  .L1:
     *      ; start of epilogue
     *      POPM.W  #1, r4
     *      RET
     *  .L3:
     *      MOV.W   #-1, R12
     *      BR      #.L1
     *
     */
}
int abs(const int a)
{
    return (a > 0) ? a : -a;
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
} // namespace X