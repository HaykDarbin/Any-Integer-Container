#include "Any_Integer.hpp"
#include <iostream>

int main ()
{
    Any_Integer num ("11111111333333333311111111111122222222222222222223333333333333333333444444444444444444445555555555555555555566666666666666666667777777777777777777788888000003210000000000099999999999999991110000000000000000000000");
    Any_Integer num2 ("-1111222233334");
    Any_Integer num3 (num2);
    std::cout << "num1 " << num << std::endl;
    std::cout << "num2 " << num2 << std::endl;
    std::cout << "num3 " << num3 << std::endl;
    Any_Integer num4 (num);
    std::cout << "num4 " << num4 << std::endl;
    Any_Integer num5;
    std::cout << "num5 " << num5 << std::endl;
    num5 = "3333333333111111111111222222222222222222233";
    num4 = num5;
    std::cout << "num5 - num = "<< num5 - num << std::endl;
    std::cout << "num - num5 = "<< num - num5 << std::endl;
    std::cout << "num5 " << num5 << std::endl;
    num5 = 1110000111222333344;
    std::cout << "num5 " << num5 << std::endl;
    num3 = num5;
    std::cout << "num3 " << num3 << std::endl;
    num4 = num2 + num5; 
    std::cout << "num4 " << num4 << std::endl;
    Any_Integer num6 ("2222222233");
    Any_Integer num7 ("-9111111111");
    Any_Integer num8 = (num6 + num7);
    std::cout << num8 << std::endl;
    std::cout << "num8 - num8 = "<< num8 - num8 << std::endl;
    std::cout << "num3 - num2 = "<< num3 - num2 << std::endl;
    std::cout << "num3 + num4 = "<< num3 + num4 << std::endl;
    std::cout << "num3 + liter_int = "<< num3 + 12345 << std::endl;
    Any_Integer num9(num8);
    std::cout << ((num6 > num7) ? "AYO" : "VOCH") << std::endl;
    std::cout << ((num6 < num7) ? "AYO" : "VOCH") << std::endl;
    std::cout << ((num8 == (num6 + num7)) ? "AYO" : "VOCH") << std::endl;
    std::cout << ((num8 == (num6)) ? "AYO" : "VOCH") << std::endl;
    std::cout << ((num8 > (num6)) ? "AYO" : "VOCH") << std::endl;
    std::cout << ((num8 < (num6)) ? "AYO" : "VOCH") << std::endl;
    std::cout << ((num8 < (num9)) ? "AYO" : "VOCH") << std::endl;
    std::cout << ((num8 > (num9)) ? "AYO" : "VOCH") << std::endl;
    
}

