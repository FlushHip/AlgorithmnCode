#include <bits/stdc++.h>

std::uint32_t InetAddr(const std::string & address)
{
    static const int NUM = 4;
    int digit[NUM];
    char skip[1 << 10];
    
    int num = std::sscanf(address.c_str(), "%d.%d.%d.%d%s", &digit[0], &digit[1], &digit[2], &digit[3], skip);
    if (NUM == num)
    {
        if (std::all_of(digit, digit + NUM, [] (int x) { return x >= 0 && x < 256; }))
        {
            uint32_t ret = 0;
            for (int i = 0; i < NUM; ret |= digit[i] << (8 * i), ++i) {}
            return ret;
        }
        else
        {
            throw std::invalid_argument("out of range");
        }
    }
    else
    {
        throw std::invalid_argument("paste error");
    }
}

int main()
{
    std::vector<std::string> arr
    {
        "1.2.3.4",
        "255.255.255.255",
        "3 3 3 3",
        "256.255.255.255",
        "x.x.x.x",
        "0.-2.2.2",
        "0.0x3.2.2",
        "0.02.2.2",
        "0.02.2.2.2",
        "0.02.2.2a",
        "ab.0.0.0.0",
        "0.123..0"
    };   

    for (auto & ele : arr)
    {
        std::cout << ele << std::endl;
        try
        {
            printf("%x\n", InetAddr(ele));
        }
        catch (const std::invalid_argument & e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
