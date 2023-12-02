#ifndef __UTILITY_X_H__
#define __UTILITY_X_H__
namespace X {
/**
 * @brief Returns the sign of a number
 *
 * @tparam T
 * @param a number to find the sign of
 * @return constexpr T
 */
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
int abs(const int a);
int min(const int a, const int b);
int max(const int a, const int b);
int clamp(int value, int low, int high);
} // namespace X
#endif /* __UTILITY_X_H__ */
