#include <iostream>
#include <set>

bool palindrome(int n)
{
    int temp = n;
    int rev = 0;
    int digit = 1;
    while (temp != 0)
    {
        digit = temp % 10;
        rev = (rev * 10) + digit;
        temp = temp / 10;
        // std::cout << temp << "\n";
    }
    return (rev == n);
}

int main()
{
    std::set<int> s;
    for (int i = 100; i < 1000; i++)
    {
        for (int j = 100; j < 1000; j++)
        {
            if (palindrome(i * j) == 1)
            {
                s.insert(i * j);
            }
        }
    }
    std::cout << *s.rbegin();
    return 0;
}