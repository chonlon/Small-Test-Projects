#include <regex>
#include <iostream>
#include <string>
#include "../../../header/base.h"
#include <any>

using namespace std::string_literals;
using namespace std;

int main() {
    cout << boolalpha;

    {
        // 判断是否匹配.
        CaseMarker c("match"s);

        cout << regex_match("123"s, regex("\\d"))
            << " "
            << regex_match("12345"s, regex("//d+"))
            << '\n';

        cout << "match with sub:\n";


       
        string str = "Hello_2018";
        smatch result;
        regex pattern("(.{5})_(\\d{4})");	//匹配5个任意单字符 + 下划线 + 4个数字

        if (regex_match(str, result, pattern))
        {
            // smatch的op[]或者at返回一个sub_match, 这个类继承了pair, first是成功匹配序列的开始位置, second是成功匹配的序列的结尾的下一个位置.
            // 这里的第一个形式其实是对<<做了重载, 其中调用了str()函数.
            cout<< '\t' << result[0] << endl;		//完整匹配结果，Hello_2018
            cout<< '\t' << result[1] << endl;		//第一组匹配的数据，Hello
            cout<< '\t' << result[2] << endl;		//第二组匹配的数据，2018
            cout<< '\t' << "结果显示形式2" << endl;
            cout<< '\t' << result.str() << endl;	//完整结果，Hello_2018
            cout<< '\t' << result.str(1) << endl;	//第一组匹配的数据，Hello
            cout<< '\t' << result.str(2) << endl;	//第二组匹配的数据，2018
        }

        // another match.
        cout << "another match:\n";
        string fname(
            "/usr/local/include/boost/any.hpp");

        smatch results;
        cout << '\t'
            << regex_match(
                fname,
                results,
                regex(".*/(.+)\\..*$")) << '\n';
        // 小括号是正则里面的group, submatch就是对应这个.
        for (const auto& i : results) {
            std::cout << '\t' << i << '\n';
        }
    }

    {
        CaseMarker c("search"s);
        //search 仅仅查找给定范围内的第一个匹配的结果.
        {
            string nums = "123";
            smatch s1;
            if (regex_search(nums, s1, regex("\\d+"))) {
                cout << s1[0];
            }
            cout << '\n';
        }
        

        string str = "Hello 2018, Bye 2017";
        smatch result;
        regex pattern("\\d{4}");	//匹配四个数字

        //迭代器声明
        string::const_iterator iterStart = str.begin();
        string::const_iterator iterEnd = str.end();
        string temp;
        while (regex_search(iterStart, iterEnd, result, pattern))
        {
            temp = result[0];
            cout << temp << " " << result[0].second - result[0].first << ' ';
            iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
        }
        cout << '\n';
    }


    {
        CaseMarker c("replace"s);
        // basic rule can see here : https://www.boost.org/doc/libs/1_74_0/libs/regex/doc/html/boost_regex/captures.html
        // 完全文档 http://ecma-international.org/ecma-262/5.1/#sec-15.5.4.11 (完全文档看的头疼)...
        string fname(
            "@abc def--");
        // replace 部分是$&.
        cout << regex_replace(fname, regex("(\\w+)\\W+(\\w+)"), "|||$`/regex/replace/$'|||") << '\n';
    }
}
