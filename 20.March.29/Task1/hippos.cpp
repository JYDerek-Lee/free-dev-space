#include <string>
#include <map>
#include <sstream>

int make_point(std::map<int, int> const &input)
{
    // 5장의 카드 모두 같은 숫자가 나온 조합
    // 예) (1, 1, 1, 1, 1), (2, 2, 2, 2, 2)
    if (input.size() == 1)
    {
        return 6;
    }
    // 5장의 카드가 연속된 숫자로 나오는 조합
    // 예) (3, 2, 1, 4, 5), (2, 5, 4, 3, 6)
    // 위 모든 경우에 포함되지 않는 조합
    else if (input.size() == 5)
    {
        int previous = 0;
        for (auto iter : input)
        {
            if (!previous)
            {
                previous = iter.first;
            }
            else
            {
                if (previous + 1 != iter.first)
                {
                    return 1;
                }
            }
        }
        return 5;
    }
    // 4개의 카드가 같은 숫자가 나오는 조합. 4
    // 예) (4, 4, 1, 4, 4)
    // 2개의 카드의 숫자가 같고, 나머지 3개의 카드의 숫자가 또 같은 조합. 3
    // 예) (2, 5, 5, 2, 5)
    else if (input.size() == 2)
    {
        for (auto iter : input)
        {
            if (iter.second == 4)
            {
                return 4;
            }
        }

        return 3;
    }
    // 2개의 카드의 숫자가 같고, 그 두 카드를 제외한 나머지 3개 중 2개의 카드의 숫자가 같은 조합. 2
    // 예) (2, 1, 3, 3, 2)
    else
    {
        return 2;
    }
}

std::string solution(std::string &&input)
{
    auto pos = input.find_first_of(",");
    auto str1 = input.substr(0, pos);
    auto str2 = input.substr(pos + 1);

    std::stringstream strm(str1);
    int value = 0;
    std::map<int, int> first{};
    while (strm >> value)
    {
        first[value]++;
    }

    std::stringstream strm2(str2);
    value = 0;
    std::map<int, int> second{};
    while (strm2 >> value)
    {
        second[value]++;
    }

    int point1 = make_point(first);
    int point2 = make_point(second);

    if (point1 == point2)
    {
        return "Draw";
    }

    return point1 > point2 ? "First" : "Second";
}

#include <iostream>
int main()
{
    std::cout << solution("3 2 3 2 3,6 1 1 2 3") << " / A: First" << std::endl;
    std::cout << solution("5 5 5 5 5,1 1 1 1 1") << " / A : Draw" << std::endl;
}