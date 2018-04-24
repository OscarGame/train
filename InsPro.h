/*InsPro.h��������InsPro.cpp�ļ�*/
#pragma once
#include<string>
#include<vector>

#include"Struct_self.h"

//��������

//��������

std::vector<unsigned char>MOVE(const std::string& str, int k, int num);

std::vector<unsigned char>Move1(const std::string& str,int n,int num);

std::vector<unsigned char>Move2(const std::string& str, STRINF *m1, STRINF *m2, int num);

long Organ(const std::string& str, int n, int num);

//Data���������ڴ���DB,DW,DDָ��,str:����ָ���ַ�����num��ָ���ַ�֮���һ�ֽ�λ�ã�fix����ָ��ռ�õ��ֽ���
std::vector<unsigned char>DataBWD(const std::string& str, int n, int fix, int num);

int ReserveByte(const std::string& str, int num, int all);

//�ӷ�ָ��
std::vector<unsigned char>Additive(const std::string& str, int n, int num);
//����ָ��
std::vector<unsigned char>Subtraction(const std::string& str, int n, int num);

//����jmp��䡣
std::vector<unsigned char>Jemp();

std::vector<unsigned char>Push(const std::string& str, int n, int num);

std::vector<unsigned char>Pop(const std::string& str, int n);

//INTָ��Ϊ�Կ�����ָ��
std::vector<unsigned char>Int(std::string& str, int n, int num);

//����je��䡣str:�ַ�����n����ʼ�ַ�����ȡλ�ã�m��main.cpp�е�jp
std::vector<unsigned char>Je();
//cmpָ��Ƚ�ָ��
std::vector<unsigned char>Cmp(const std::string& str, int n, int num);
//��λָ��,cmd_ch���߳�����shr���ƣ�����shl���ƣ��������������Ƿ����ĵڶ��������룬shr��0xe8~0xef��shl:0xe0~0xe7
std::vector<unsigned char>Shl_Shr(const std::string& str, int n, int num, unsigned char cmd_ch);

//����jbe��䡣
std::vector<unsigned char>Jbe();

//����jb��䡣
std::vector<unsigned char>Jb();

//����in��outָ�w�����ж���in����out�����w=i��Ϊin�������w=o����ô��outָ�
std::vector<unsigned char>In_Out(const std::string& str, int n, int num, char w);

std::vector<unsigned char>Logic(const std::string& str, int n, int num, char w);

//notȡ��ָ��
std::vector<unsigned char>Not(const std::string& str, int n);
//mul�˷�ָ��
std::vector<unsigned char>Mul(const std::string& str, int n);