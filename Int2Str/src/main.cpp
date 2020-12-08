/******************* Problem *********************
Convert integer to string
**************************************************/
#include <iostream>

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, int> = 0>
std::string Int2Str(T value)
{
	constexpr T MinValue = T(-1) < 0 ? T(1) << (sizeof(T) * 8 - 1) : 0;
	bool neg = value < 0;
	std::string ret = value == 0 ? "0" : "";
	if (neg && value == MinValue)
	{
		ret += -1 * (value % 10) + '0';
		value /= 10;
	}
	if (neg) value *= -1;
	while (value)
	{
		ret += value % 10 + '0';
		value /= 10;
	}
	std::reverse(ret.begin(), ret.end());
	ret = neg ? "-" + ret : ret;
	return ret;
}

template<typename T, typename std::enable_if_t<!std::is_integral<T>::value, int> = 0>
std::string Int2Str(T value)
{
	static_assert(false, "Type of value is not integer!");
}

int main()
{
	std::cout << Int2Str<unsigned int>(0) << std::endl;
	std::cout << Int2Str(-2147483648) << std::endl;
	std::cout << Int2Str(2147483648999999) << std::endl;
	//std::cout << IntegerToString(12.5) << std::endl;
 	return 0;
}