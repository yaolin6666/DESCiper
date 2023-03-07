// DESCiper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <bitset>
using namespace std;
string desKeys[20];//生成的密钥保存
int T1[8][8] = { 58,50,42,34,26,18,10,2,
                 60,52,44,36,28,20,12,4,
                 62,54,46,38,30,22,14,6,
                 64,56,48,40,32,24,16,8,
                 57,49,41,33,25,17,9,1,
                 59,51,43,35,27,19,11,3,
                 61,53,45,37,29,21,13,5,
                 63,55,47,39,31,23,15,7 };//初始置换表、

int T2[8][7] = { 57,49,41,33,25,17,9,
                 1,58,50,42,34,26,18,
                 10,2,59,51,43,35,27,
                 19,11,3,60,52,44,36,
                 3,55,47,39,31,23,15,
                 7,62,54,46,38,30,22,
                 14,6,61,53,45,37,29,
                 21,13,5,28,20,12,4 };//密钥初始置换表PC1

int T3[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };//移位次数表

int T4[8][6] = { 14,17,11,24,1,5,
                 3,28,15,6,21,10,
                 23,19,12,4,26,8,
                 16,7,27,20,13,2,
                 41,52,31,37,47,55,
                 30,40,51,45,33,48,
                 44,49,39,56,34,53,
                 46,42,50,36,29,32 };//密钥置换表PC2

int T5[8][6] = { 32,1,2,3,4,5,
                 4,5,6,7,8,9,
                 8,9,10,11,12,13,
                 12,13,14,15,16,17,
                 16,17,18,19,20,21,
                 20,21,22,23,24,25,
                 24,25,26,27,28,29,
                 28,29,30,31,32,1 };    //数据扩展表


int T6[8][8] = {  40,8,48,16,56,24,64,32,
                  39,7,47,15,55,23,63,31,
                  38,6,46,14,54,22,62,30,
                  37,5,45,13,53,21,61,29,
                  36,4,44,12,52,20,60,28,
                  35,3,43,11,51,19,59,27,
                  34,2,42,10,50,18,58,26,
                  33,1,41,9,49,17,57,25 };//最终置换表

int P[4][8] = { 16,7,20,21,
                29,12,28,17,
                1,15,23,26,
                5,18,31,10,
                2,8,24,14,
                32,27,3,9,
                19,13,30,6,
                22,11,4,25 };//P盒

int S[8][4][16] = { {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
                {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
                {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
                {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
                {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
                {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
                {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
                {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}} };//S盒

string desXOR(string s1, string s2)
{
    string value_Return = "";
    for (int i = 0; i < s1.length() && i < s2.length(); i++)
    {
        value_Return += ((s1[i] - '0') ^ (s2[i] - '0')) + '0';
    }
    return value_Return;
}//异或运算

string initial_replacement (string s)//明文初始置换
{
    string value_Return = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            value_Return += s[T1[i][j] - 1];
        }
    }
    return value_Return;
}

//最终置换
string final_replacement(string s)
{
    string value_Return = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            value_Return += s[T6[i][j] - 1];
        }
    }
    return value_Return;
}

string extended_replacement(string s)
{
    string valueReturn = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            valueReturn += s[T5[i][j] - 1];
        }
    }
    return valueReturn;
}//明文的扩展

string key_initial_replacement(string s)
{

    string valueReturn = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            valueReturn += s[T2[i][j] - 1];
        }
    }

    return valueReturn;
}//密钥置换PC1

string key_move(int k, string s)//密钥循环左移
{
    string s1 = s.substr(0, 28);
    string s2 = s.substr(28, 28);
    string valueReturn = s1.substr(k, 28 - k) + s1.substr(0, k) + s2.substr(k, 28 - k) + s2.substr(0, k);
    return valueReturn;
}

string key_compression_replacement(string s)
{
    string valueReturn = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            valueReturn += s[T4[i][j] - 1];
        }
    }
    return valueReturn;
}//密钥置换PC2

void des_generateKeys(string s)
{

    s = key_initial_replacement(s);

    for (int i = 1; i <= 16; i++)
    {
        s = key_move(T3[i - 1], s);
        desKeys[i] = key_compression_replacement(s);
    }
}

string S_box(string s)
{
    string value_Return = "";
    string s1;
    int k1, k2;//S盒的行号和列号
    int h = 1;//决定使用那个S盒
    for (int i = 0; i < 48; i = i + 6, h++)
    {
        k1 = (s[i] - '0') * 2 + (s[i + 5] - '0') * 1;
        k2 = (s[i + 1] - '0') * 8 + (s[i + 2] - '0') * 4 + (s[i + 3] - '0') * 2 + (s[i + 4] - '0') * 1;
        int x = S[h - 1][k1][k2];
        s1 = "";
        int y = 8;
        for (int j = 1; j <= 4; j++)
        {
            if (x < y)
            {
                s1 += "0";
                y /= 2;
            }
            else
            {
                s1 += "1";
                x = x % y;
                y /= 2;
            }
        }
        value_Return += s1;
    }
    return value_Return;
}//s盒运算

string P_box(string s)
{
    string value_Return = "";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            value_Return += (s[P[i][j] - 1]);
        }
    }
    return value_Return;
}//P盒运算

//F运算
string des_f(string str1, string str2)
{
    string expendR = extended_replacement(str1);
    string valueReturn = desXOR(expendR, str2);
    valueReturn = S_box(valueReturn);
    valueReturn = P_box(valueReturn);
    return valueReturn;
}
string des_H(string s)
{
    string s1;
    string value_Return = "";
    for (int i = 0; i < s.length(); i++)
    {
        int x;
        if (s[i] >= '0' && s[i] <= '9')
        {
            x = s[i] - '0';
        }
        else
        {
            x = s[i] - 'A' + 10;
        }
        s1 = "";
        int y = 8;
        for (int j = 1; j <= 4; j++)
        {
            if (x < y)
            {
                y /= 2;
                s1 += "0";
            }
            else
            {
                s1 += "1";
                x = x % y;
                y = y / 2;
            }
        }
        value_Return += s1;
    }
    return value_Return;
}//输入key为16位十六进制字符 key的二进制化为64位字符串
string des_StrToBitStr(string str)
{
    bitset<64> bstr;
    for (int i = 0; i < 8; i++)
    {
        bitset<8> bits = bitset<8>(str[i]);
        for (int j = 0; j < 8; j++)
        {
            //bstr[i * 8 + j] = bits[7 - j];
            bstr[(7-i)*8+j] = bits[j];
        }
    }
    string s = bstr.to_string();
    //reverse(begin(s), end(s));
    return s;
}
//高低位与正常相反


// 反向转换 将二进制字符串转换为字符
string des_BitStrToStr(string bstr)
{
    string value_Return = "";
    //每八位转化成十进制，然后将数字结果转化成字符
    int sum;
    for (int i = 0; i < bstr.size(); i += 8)
    {
        sum = 0;
        for (int j = 0; j < 8; j++)
            if (bstr[i + j] == '1')
                sum = sum * 2 + 1;
            else
                sum = sum * 2;
        value_Return = value_Return + char(sum);
    }
    return value_Return;
}
string chardeel(string str1) {
    string temp_str = "";
    int divi_times = (str1.size() % 8 ? str1.size() / 8 + 1 : str1.size() / 8);		//计算分组个数 三目运算符计算分组次数
    for (int i = 0; i < divi_times; ++i) {										//每个分组单独转换成二进制串 
        string str1_temp = str1.substr(8 * i, 8);  //substr(start,len) 

        bool jude = false;
        int addchar = 0;
        if (str1_temp.size() % 8) {
            jude = true;
            addchar = 8 - str1_temp.size() % 8;
        }
        int sub = str1_temp.size() * 8;
        if (jude) {
            for (int i = 0; i < addchar; i++) {
                str1_temp += 'a';
            }
        }
        str1_temp = des_StrToBitStr(str1_temp);
        if (jude) {
            for (int i = 0; i < addchar * 8; i++) {
                str1_temp[sub + i] = '0';
            }
        }                                               //多余位补0
        temp_str = temp_str + str1_temp;

    }
    return temp_str;
}

string des_encrypt(string str1, string str2)
{
    str1=chardeel(str1);
    str2 = des_H(str2);
    des_generateKeys(str2);  //生成16个子密钥
    int divi_times = str1.size() / 64;
    string value_Return = "";

    for (int i = 0; i < divi_times; ++i) {
        string str1_temp = str1.substr(i * 64, 64);
        //初始置换
        str1_temp = initial_replacement(str1_temp);
        string left = str1_temp.substr(0, 32);
        string right = str1_temp.substr(32, 32);
        string newleft;
        for (int i = 1; i <= 16; i++)
        {
            newleft = right;
            right = desXOR(left, des_f(right, desKeys[i]));
            left = newleft;
        }
        string temp = right + left;//最后一轮不交换 这里使用right+left在交换回来
        //最终置换
        temp = final_replacement(temp);
        value_Return = value_Return + temp;
    }
    return value_Return;

}
string des_decrypt(string str1,string str2)
{
    int divi_times = str1.size() / 64;
    string value_Return = "";
    str2 = des_H(str2);
    des_generateKeys(str2);
    for (int i = 0; i < divi_times; ++i) {
        string str_temp = str1.substr(i * 64, 64);
        str_temp = initial_replacement(str_temp);
        string left = str_temp.substr(0, 32);
        string right = str_temp.substr(32, 32);
        string newleft;
        for (int i = 16; i >= 1; i--)
        {
            newleft = right;
            right = desXOR(left, des_f(right, desKeys[i]));
            left = newleft;
        }
        string temp = right + left;
        temp = final_replacement(temp);
        value_Return = value_Return + temp;
    }
    value_Return = des_BitStrToStr(value_Return);
    return value_Return;
}

int main()
{   
    string str1 = "目前使用设备:\n\t1.罗技G502\n\t2.AE75(组合轴) + 原厂高度极简白键帽\n\t3.Wacom PTH - 660";
    string str2 = "U2FsdGVkXWmqR1yx7";
    string ciper_text=des_encrypt(str1, str2);
    cout << ciper_text<<endl;
    string plain_text = des_decrypt(ciper_text, str2);
    cout << plain_text << endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
