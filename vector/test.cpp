#include <iostream>
#include "vector.hpp"
#include <vector>
#include <algorithm>


class Print{
    public:
    void    operator()(int a){
        std::cout << a << std::endl;
    }
};

int main(void)
{
    ft::vector<int> test1;

    std::vector<int>    std_v;
    std::vector<int>    sw;

    test1.push_back(5);
    test1.push_back(4);
    test1.push_back(3);
    test1.push_back(2);
    test1.push_back(1);

    std_v.push_back(5);
    std_v.push_back(4);
    std_v.push_back(3);
    std_v.push_back(2);
    std_v.push_back(1);   
    // std_v.push_back(6);   

    sw.push_back(5);
    sw.push_back(4);
    sw.push_back(3);
    sw.push_back(2);
    sw.push_back(1);   
    sw.push_back(6);

    // sw.push_back(111);
    // sw.push_back(111);
    // sw.push_back(111);

    std::cout << ft::equal(std_v.begin(), std_v.end(), sw.begin()) << std::endl;
    std::cout << (std_v == sw) << std::endl;
   


}