#include <bits/stdc++.h>

using namespace std;

struct Pos
{
    int x, y;
};

bool judge(int width, int height, Pos start, Pos end, std::vector<Pos> & obstacle)
{
    static const int dirx[]  = {2, 1, -1, -2, -2, -1, 1, 2};
    static const int diry[]  = {1, 2, 2, 1, -1, -2, -2, -1};
    static const int dirnx[] = {1, 0, 0, -1, -1, 0, 0, 1};
    static const int dirny[] = {0, 1, 1, 0, 0, -1, -1, 0};

    auto cmp = [] (const Pos & A, const Pos & B)
    {
        return A.x != B.x ? A.x < B.x : A.y < B.y;
    };

    std::sort(obstacle.begin(), obstacle.end(), cmp);

    std::set<Pos, decltype(cmp)> used(cmp);
    std::queue<Pos> que;

    for (que.push(start); !que.empty(); )
    {
        auto now = que.front();
        que.pop();

        used.insert({now.x, now.y});

        if (now.x == end.x && now.y == end.y)
        {
            return true;
        }

        for (int i = 0; i < sizeof(dirx) / sizeof(dirx[0]); ++i)
        {
            Pos next {now.x + dirx[i], now.y + diry[i]};
            Pos stone {now.x + dirnx[i], now.y + dirny[i]};

            if ((next.x >= 0 && next.x < width && next.y >=0 && next.y < height)
                && !std::binary_search(obstacle.begin(), obstacle.end(), next, cmp)
                && !std::binary_search(obstacle.begin(), obstacle.end(), stone, cmp)
                && used.find(next) == used.end())
            {
                que.push(next);
            }
        }
    }
    
    return false;
}

int main()
{
    int width = 3, height = 2;
    Pos start {0, 0}, end {2, 1};
    std::vector<Pos> obstacle { {1, 0} };
    std::cout << std::boolalpha << judge(width, height, start, end, obstacle) << std::endl;
    obstacle.clear();
    std::cout << std::boolalpha << judge(width, height, start, end, obstacle) << std::endl;
    return 0;
}
