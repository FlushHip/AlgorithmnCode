#include <bits/stdc++.h>

using namespace std;

void FindPhoneNumber(const std::string & str, const std::string & prefix)
{
    static const int LEN = 11;

    assert(prefix.size() <= LEN);

    vector<std::string> res;
    int start = 0;
    for (auto it = str.find(prefix, start); it != std::string::npos; it = str.find(prefix, start))
    {
        if (str.size() - it >= LEN && std::all_of(str.begin() + it, str.begin() + it + LEN, ::isdigit))
        {
            res.push_back(str.substr(it, LEN));
            start = it + LEN;
        }
        else
        {
            start = str.size() - it >= LEN ? it + LEN : str.size();
        }
    }

    for (auto & ele : res)
    {
        std::cout << ele << std::endl;
    }
}

int main()
{
    FindPhoneNumber("134136abc13512345679abc", "135");
    FindPhoneNumber("1a1c13613612345678136123123123abc", "136");
    return 0;
}
