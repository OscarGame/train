#include<string>

#ifndef RET_H
#define RET_H
typedef struct ReT{
	std::string str;
	int num;//����д���ֵnumber
	int s;//����λ��AllNum
}ReTitle;
#endif

#ifndef STRUCT_H
#define STRUCT_H 
typedef struct STRINF{
	std::string explain;//��˵�����������byte��word�ȣ�
	std::string str;//���ַ����������ڵ��ַ�����������
	bool w;//�ַ������Ƿ���������
	int lk;//���w=true���ַ������������ŵ�λ��
	int rk;//���w=true���ַ������������ŵ�λ��
}STRINF;
#endif