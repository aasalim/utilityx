#ifndef __UTILITY_X_H__
#define __UTILITY_X_H__
namespace X {
/**
 * @brief Returns the sign of a number
 * 
 * @tparam T 
 * @param a value to find the sign of
 * @return constexpr T 
 */
template <typename T>
constexpr T sign(const T a);
int abs(const int a);
int min(const int a, const int b);
int max(const int a, const int b);
int clamp(int value, int low, int high);
} // namespace X
#endif /* __UTILITY_X_H__ */
