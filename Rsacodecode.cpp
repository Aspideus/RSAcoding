//RSA ����
#include <NTL/ZZ.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <fstream>
NTL_CLIENT

#pragma comment( lib, "NTL.lib" )
using namespace NTL;

unsigned long long Perevert (unsigned long long a)
{
    unsigned long long y = 0;
    while (a)
    {
        y = y * 10 + a % 10;
        a /= 10;
    }
    return y;
}

unsigned long long Encode (unsigned long long inpblock, long vib, long dlin)
{
   unsigned long long inpblock1 = inpblock;

   for (long j = 0; j < vib; j++)
   {
       inpblock1 *= inpblock;
   }
   inpblock = inpblock1 % dlin;
   return inpblock;
}


int main()
{
    unsigned long long x = 0;
    int i = 1;
    //
    int chalen = 15; //������ ������ ������������� 15
    char input[chalen + 1] //= "aBitzabecdeadts" //������� ������ ������ ������ �� ���
    ; //�������� ������� ������ �� �����������
    //
    ifstream inputimf("inputRSA.txt");
    inputimf >> input;
    inputimf.close();
    cout << input << endl; //��������, ��� ������� ���������

    if (input[0] >= 97)
        x = input[0] - 96;
        else
        x = input[0] - 38;
    while (i < chalen) //��������� �������� ����� � �����, ������ a - �� 97, � 1, A - �� 65, � 27 � ����� �� �������
    {
        if ((input[i] > 105) || (input[i] < 97))
                x *= 100;
        else
                x *= 10;
        if ((input[i] >= 65) && (input[i] <= 90))
            x += input[i] - 38;
        else
            x += input[i] - 96;
        i++;
    }

    //��� �������
    //x = 19; //��� ���������� ���� 10
    //x = 10; //��� ������������� ���� 19
    //����� �������

    std::cout << "Ishod chislo: " << x << endl; //����� �������� �� ������ ��������������� �����
    int xorig = x;
    x = Perevert(x); //������� ��������������� ��������� �����, ����� �� ����� � ��� ������ ��������
    //std::cout << "Obernutoe chislo: " << x << endl; //����� �������� �� ������ ������������ �����


    //�������� ������
   long p = 3; //clo 3
   long q = 7; //clo 7
   long e = 5; //open 5
   long d = 17; //clo 17
   unsigned long n = p * q; //open
   cout << "Lets input the keys: " << endl;
   cout << "p: ";
   cin >> p;
   cout << "q: ";
   cin >> q;
   cout << "e: ";
   cin >> e;
   cout << "d: ";
   cin >> d;
   cout << "Your open key is: " << endl;
   n = p * q;
   cout << "e: " << e << endl << "n: " << n << endl;
   cout << "Your closed key is: " << endl;
   cout << "p: " << p << endl << "q: " << q << endl << "d: " << d << endl;
    //
   long method;
   int inp;
   cout << "Print 2 to encode, smth else to decode: " << endl; //�������� ����� ����� ����������� � �������������
   cin >> inp;
   if (inp == 2)
        method = e - 1;
    else
        method = d - 1;
   cout << "In Process..." << endl << endl;

   //������ ����
    ostringstream ost;
    ost << xorig;
    int xlen = ost.str().size();
    ostringstream ost1;
    ost1 << x;
    int xolen = ost1.str().size();
    int raz, xs = 1;

    if (xlen > xolen) //����� �� ����������� ����� �� ����� �������� ���� � �����, ��� �������� �������� ����� ��������
    {
        raz = xlen - xolen;
        for (i = 0; i < raz; i++)
        {
            xs *= 10;
        }
    }
    unsigned long long block = 0;
    string str = "";
    stringstream ss;

    while (x > 0) //�������� ����� �� ���������� mod������� ���� ��� �� ����� ������������ n
    {
        block += x % 10;
        x /= 10;
        if (block < n)
            block *= 10;
        else
        {
            x = x * 10 + (block % 10);
            block /= 10;

            //cout << block << endl;
            block = Encode(block, method, n); //� � ���� ������ �� ��� ��������� � �������/���������
            // block -> shifr
            ss << block;
            block = 0;
        }
    }
    block /= 10;
    //
    if (block * xs < n) //����������� ����������� ����
        block *= xs;

    cout << block << endl;
    block = Encode(block, method, n); //��� ���������� ����� ������� ��������
    //block -> shifr last word
    ss << block;
    cout << "Fin coded string is: ";
    str = ss.str();
    cout << str << endl;
    return 0;
}
//19 - 10 ��� p3 q7 e5 d17
