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
     *  sign(int): 19 cycles
     *      ; start of prologue
     *      PUSHM.W #1, R4
     *      MOV.W   R1, R4
     *      SUB.W   #2, R1
     *      ; end of prologue
     *      MOV.W   R12, -2(R4)
     *      CMP.W   #0, -2(R4) { JGE      .L2
     *      MOV.W   #-1, R12
     *      BR      #.L4
     *  .L2:
     *      MOV.B   #1, R12
     *  .L4:
     *      ; start of epilogue
     *      ADD.W   #2, R1
     *      POPM.W  #1, r4
     *      RET
     *
     */
}
template <typename T>
constexpr T abs(const T a)
{
    return (a < 0) ? -a : a;
    /**
     *  abs(int): 19 cycles
     *      ; start of prologue
     *      PUSHM.W #1, R4
     *      MOV.W   R1, R4
     *      SUB.W   #2, R1
     *      ; end of prologue
     *      MOV.W   R12, -2(R4)
     *      MOV.W   -2(R4), R12
     *      CMP.W   #0, R12 { JGE .L2
     *      MOV.B   #0, R13
     *      SUB.W   R12, R13
     *      MOV.W   R13, R12
     *  .L2:
     *      ; start of epilogue
     *      ADD.W   #2, R1
     *      POPM.W  #1, r4
     *      RET
     *
     */
}

template <typename T>
constexpr T min(const T a, const T b)
{
    return (a < b) ? a : b;
    /**
     *  min(int, int): 20 cycles
     *      ; start of prologue
     *      PUSHM.W #1, R4
     *      MOV.W   R1, R4
     *      SUB.W   #4, R1
     *      ; end of prologue
     *      MOV.W   R12, -2(R4)
     *      MOV.W   R13, -4(R4)
     *      CMP.W   -2(R4), -4(R4) { JGE  .L2
     *      MOV.W   -2(R4), R12
     *      BR      #.L3
     *  .L2:
     *      MOV.W   -4(R4), R12
     *  .L3:
     *      ; start of epilogue
     *      ADD.W   #4, R1
     *      POPM.W  #1, r4
     *      RET
     *
     */
}
template <typename T>
constexpr T max(const T a, const T b)
{
    return (a > b) ? a : b;
    /**
     *  max(int, int): 20 cycles
     *      ; start of prologue
     *      PUSHM.W #1, R4
     *      MOV.W   R1, R4
     *      SUB.W   #4, R1
     *      ; end of prologue
     *      MOV.W   R12, -2(R4)
     *      MOV.W   R13, -4(R4)
     *      CMP.W   -2(R4), -4(R4) { JGE  .L2
     *      MOV.W   -2(R4), R12
     *      BR      #.L4
     *  .L2:
     *      MOV.W   -4(R4), R12
     *  .L4:
     *      ; start of epilogue
     *      ADD.W   #4, R1
     *      POPM.W  #1, r4
     *      RET
     *
     */
}

template <typename T>
constexpr T clamp(T value, T low, T high)
{
    return min(max(value, low), high);
    /**
     *  clampMine(int, int, int): 27 cylces
     *      ; start of prologue
     *      PUSHM.W #1, R4
     *      MOV.W   R1, R4
     *      SUB.W   #6, R1
     *      ; end of prologue
     *      MOV.W   R12, -2(R4)
     *      MOV.W   R13, -4(R4)
     *      MOV.W   R14, -6(R4)
     *      CMP.W   -4(R4), -2(R4) { JL   .L2
     *      CMP.W   -2(R4), -6(R4) { JGE  .L3
     *      MOV.W   -6(R4), R12
     *      BR      #.L6
     *  .L3:
     *      MOV.W   -2(R4), R12
     *      BR      #.L6
     *  .L2:
     *      MOV.W   -4(R4), R12
     *  .L6:
     *      ; start of epilogue
     *      ADD.W   #6, R1
     *      POPM.W  #1, r4
     *      RET
     *
     */
}

} // namespace X
#endif /* __UTILITY_X_H__ */
