/*HelpInsPro.hͷ�ļ���������HelpInsPro.cpp*/
#pragma once
#include<string>
#include<vector>

#include"Struct_self.h"

//���帨������

unsigned char RegACDB(const std::string& str, short num);

//���������Ĵ�����ֵ��Ӧ�Ĳ����룬1:8λ�Ĵ�����2:16λ�Ĵ�����3:��16λ���μĴ�������4�����μĴ�����16λ��
unsigned char TwoRegBin(std::string *ch, int n);

//��16���ƻ�10�����ַ���ת��Ϊ����д���ļ���ֵ��str:�ַ�����num:�������Ԫ������;a:number
std::vector<unsigned char>Num(const std::string& str, int num,int a);

//��һ������ת��Ϊ unsigned char ���飬n:������num���������Ԫ������
std::vector<unsigned char>NumToUc(long n, int num);

//��16���ƻ�10�����ַ���ת��Ϊ������str:�ַ���
long IntNum(const std::string& str,int num);

unsigned char regadd(const std::string& str, int num);

unsigned char regsub(const std::string& str, int num);
//�����пո��tab���ַ���
std::vector<unsigned char>Num_cut(const std::string& str, int num);


//ר����movָ��ĸ�������
std::vector<unsigned char>mov_push(const std::string& str, unsigned char b, unsigned char a, int num, STRINF *m1, STRINF *m2);

//cmd1:��cmd1=��b��ʱ��˵��m1->explain=="byte",��cmd1=��w��ʱ��˵��m1->explain=="word";
//cmd2:ȡֵ��0~15,�ֱ��Ӧ AX~DI,AL~BH��
//cmd1���������Ƿ�Ҫ��0x3e��cmd2����Ŀ��Ĵ�������
//explain��str��Ӧm2��ֵ
std::vector<unsigned char>BX_BP_SI_DI(char cmd1, char cmd2, std::string explain, std::string str, int num);

//str���Ĵ�������,a:0~3;n1/n2���ֱ���16λ��8λ�Ĵ����Ļ�����
std::vector<unsigned char>acdb(unsigned char n1, unsigned char n2, short a, std::string str);

std::vector<unsigned char>acdb_m1_num(short cmd, std::string str, std::string m1_str, int num);

STRINF *hep(const std::string& str);