/*HelpInsPro.cpp��������InsPro�л��õ��ĸ�������*/
//����ϵͳͷ�ļ�
#include<string>
#include<iostream>
#include<vector>
#include<ctype.h>
#include<math.h>
//�Զ���ͷ�ļ�
#include"MyRegister.h"
#include"assistFun.h"
#include"Struct_self.h"

//��������������movָ���мĴ���֮��ĸ�ֵ
//*chΪ������ַ������飬a��Ϊ��Ҫʶ������ͣ�
//1:�Ĵ�����λ��λ֮�丳ֵ��2:�Ĵ���֮�丳ֵ��3:�μĴ��������Ĵ���
unsigned char TwoRegBin(std::string *ch, int n)
{
	using namespace std;
	int i, j;
	int num1=16, num2=16;//���������С
	int a, b;
	const string *m1,*m2;
	string ch0 = ch[0];
	string ch1 = ch[1];
	if (n == 1 ){
		m1 = reg_1;
		m2 = reg_1;
	}
	else if (n == 2){
		m1 = reg2;
		m2 = reg2;
	}
	else if (n == 3){
		num2 = 8;
		m1 = reg2;
		m2 = reg3;
	}
	else if (n == 4){
		ch0 = ch[1];
		ch1 = ch[0];
		num2 = 8;
		m1 = reg2;
		m2 = reg3;
	}
	else{
		std::cout << "TwoRegBin������������error-002��\n";
		return 0;
	}
	a = num1 / 2 - 1;
	b = num2 / 2 - 1;
	for (i = 0; i<num1; i++)
	for (j = 0; j<num2; j++){
		if (ch0 == m1[i] && ch1 == m2[j]){
			if (i>a && j>b)return 0xc0 + i - a - 1 + (j - b - 1) * 8;
			if (i > a)return 0xc0 + (i - a - 1) + j * 8;
			if (j > b)return 0xc0 + i + (j - b - 1) * 8;
			return 0xc0 + i+j*8;
		}
	}
	return 0;
}

unsigned char RegACDB(const std::string& str, short num)
{
	if (num == 2){
		if (str == "AX")return AX_HEX;
		if (str == "CX")return CX_HEX;
		if (str == "DX")return DX_HEX;
		if (str == "BX")return BX_HEX;
		if (str == "SP")return SP_HEX;
		if (str == "BP")return BP_HEX;
		if (str == "SI")return SI_HEX;
		if (str == "DI")return DI_HEX;
		if (str == "ax")return AX_HEX;
		if (str == "cx")return CX_HEX;
		if (str == "dx")return DX_HEX;
		if (str == "bx")return BX_HEX;
		if (str == "sp")return SP_HEX;
		if (str == "bp")return BP_HEX;
		if (str == "si")return SI_HEX;
		if (str == "di")return DI_HEX;
	}
	else if (num == 1){
		if (str == "AH")return AH_HEX;
		if (str == "AL")return AL_HEX;
		if (str == "CH")return CL_HEX;
		if (str == "CL")return CH_HEX;
		if (str == "DH")return DH_HEX;
		if (str == "DL")return DL_HEX;
		if (str == "BH")return BH_HEX;
		if (str == "BL")return BL_HEX;
		if (str == "ah")return AH_HEX;
		if (str == "al")return AL_HEX;
		if (str == "ch")return CL_HEX;
		if (str == "cl")return CH_HEX;
		if (str == "dh")return DH_HEX;
		if (str == "dl")return DL_HEX;
		if (str == "bh")return BH_HEX;
		if (str == "bl")return BL_HEX;
	}
	return 0;
}

//HexOct����һ��ʮ�������ַ������ض�Ӧ������
short HexOct(char ch)
{
	using namespace std;
	switch (ch){
	case '0':return 0;
	case '1':return 1;
	case '2':return 2;
	case '3':return 3;
	case '4':return 4;
	case '5':return 5;
	case '6':return 6;
	case '7':return 7;
	case '8':return 8;
	case '9':return 9;
	case 'a':return 10;
	case 'b':return 11;
	case 'c':return 12;
	case 'd':return 13;
	case 'e':return 14;
	case 'f':return 15;
	case 'A':return 10;
	case 'B':return 11;
	case 'C':return 12;
	case 'D':return 13;
	case 'E':return 14;
	case 'F':return 15;
	}
	std::cout << "HexOct��������error-003��\n" ;
	return -1;
}
//IsHexNum����һ���ַ���ȷ���Ƿ�����16�����ַ�
bool IsHexNum(const std::string& str)
{
	for (int i = 0; i < (int)str.size(); i++){
		if (!isxdigit(str[i]))return false;
	}
	return true;
}

//��һ������ת��Ϊ unsigned char ���飬n:������num���������Ԫ������
std::vector<unsigned char>NumToUc(long n,int num)
{
	std::vector<unsigned char>data;
	for (int i = 0; i<num; i++){
		data.push_back((unsigned char)(n >> (8 * i)));
	}
	return data;
}
//�����ַ������Ƿ����
char FoundMathChar(const std::string& str)
{
	for (int i = 0; i < (int)str.size(); ++i){
		switch (str[i]){
		case '+':return '+';
		case '-':return '-';
		case '*':return '*';
		case '/':return '/';
		}
	}
	return 0;
}

//��16���ƻ�10�����ַ���ת��Ϊ������str:�ַ���;num:���ļ��е�number
long IntNum(const std::string& str,int num)
{
	using namespace std;
	int i, sum = 0, n = str.size();
	//�鿴�Ƿ���BYTE WORD�ȱ�ʶ��
	char c = FoundMathChar(str);//�����������
	if (c>0){
		string ch[2];
		long k[2] = {0};
		ch[0] = str.substr(0,str.find(c));
		ch[1] = str.substr(str.find(c)+1,n - str.find(c)-1);
		//��ʱ��ch�ֱ𴢴�����������ߵ������ַ���������IntNum����ת��Ϊ����
		k[0] = IntNum(ch[0], num);
		k[1] = IntNum(ch[1], num);
		switch (c){
		case '+':return k[0] + k[1];
		case '-':return k[0] - k[1];
		case '*':return k[0] * k[1];
		case '/':return k[0] / k[1];
		case '$':return num;
		}
	}
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')){
		for (i = 2; i<n; ++i){
			sum += (int)pow(16.0, (double)(n - 1 - i))*HexOct(str[i]);
		}
		return sum;
	}
	else if (IsHexNum(str)){
		//�������ַ���ת��Ϊ�ɹ�����ĸ�ʽ
		for (i = 0; i < n; ++i){
			sum += (int)pow(10.0, (double)(n - i - 1))*HexOct(str[i]);
		}
		return sum;
	}
	else if (str == "$")return num;
	//�����Ǳ���ַ���
	return -1;
}
//��16���ƻ�10�����ַ���ת��Ϊ����д���ļ���ֵ��str:�ַ�����num:�������Ԫ������;a��main.cpp�е�Number����ָ���е�$������������ַ����޷�ת��Ϊ���飬������������СΪ0��
std::vector<unsigned char>Num(const std::string& str, int num, int a)
{
	using namespace std;
	vector<unsigned char>data;
	int i, sum = 0, n = str.size();
	int w = IntNum(str, a);
	if (!(w < 0)){ return NumToUc(w, num); }
	else if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')){
		for (i = 2; i < n; ++i){
			sum += (int)pow(16.0, (double)(n - 1 - i))*HexOct(str[i]);
		}
		return NumToUc(sum, num);
	}
	else if (IsHexNum(str)){
		//�������ַ���ת��Ϊ�ɹ�����ĸ�ʽ
		for (i = 0; i < n; ++i){
			sum += (int)pow(10.0, (double)(n - i - 1))*HexOct(str[i]);
		}
		return NumToUc(sum, num);
		//cout << "Numת��������ȷ��Ϊ�Ĵ����ĸ�ֵ��ȷ��error-004!" << endl;
		//�����Ǳ���ַ���,����data�Ĵ�СΪ0
	}
	return data;
}

unsigned char regadd(const std::string& str,int num)
{
	if (num == 2){
		if (str == "CX")return CX_ADD;
		if (str == "DX")return DX_ADD;
		if (str == "BX")return BX_ADD;
		if (str == "SP")return SP_ADD;
		if (str == "BP")return BP_ADD;
		if (str == "SI")return SI_ADD;
		if (str == "DI")return DI_ADD;

		if (str == "cx")return CX_ADD;
		if (str == "dx")return DX_ADD;
		if (str == "bx")return BX_ADD;
		if (str == "sp")return SP_ADD;
		if (str == "bp")return BP_ADD;
		if (str == "si")return SI_ADD;
		if (str == "di")return DI_ADD;
	}
	else if (num == 1){
		if (str == "cl")return CL_ADD;
		if (str == "dl")return DL_ADD;
		if (str == "bl")return BL_ADD;
		if (str == "ah")return AH_ADD;
		if (str == "ch")return CH_ADD;
		if (str == "dh")return DH_ADD;
		if (str == "bh")return BH_ADD;

		if (str == "CL")return CL_ADD;
		if (str == "DL")return DL_ADD;
		if (str == "BL")return BL_ADD;
		if (str == "AH")return AH_ADD;
		if (str == "CH")return CH_ADD;
		if (str == "DH")return DH_ADD;
		if (str == "BH")return BH_ADD;
	}
	return 0;
}

unsigned char regsub(const std::string& str, int num)
{
	if (num == 2){
		if (str == "CX")return CX_SUB;
		if (str == "DX")return DX_SUB;
		if (str == "BX")return BX_SUB;
		if (str == "SP")return SP_SUB;
		if (str == "BP")return BP_SUB;
		if (str == "SI")return SI_SUB;
		if (str == "DI")return DI_SUB;

		if (str == "cx")return CX_SUB;
		if (str == "dx")return DX_SUB;
		if (str == "bx")return BX_SUB;
		if (str == "sp")return SP_SUB;
		if (str == "bp")return BP_SUB;
		if (str == "si")return SI_SUB;
		if (str == "di")return DI_SUB;
	}
	else if (num == 1){
		if (str == "cl")return CL_SUB;
		if (str == "dl")return DL_SUB;
		if (str == "bl")return BL_SUB;
		if (str == "ah")return AH_SUB;
		if (str == "ch")return CH_SUB;
		if (str == "dh")return DH_SUB;
		if (str == "bh")return BH_SUB;

		if (str == "CL")return CL_SUB;
		if (str == "DL")return DL_SUB;
		if (str == "BL")return BL_SUB;
		if (str == "AH")return AH_SUB;
		if (str == "CH")return CH_SUB;
		if (str == "DH")return DH_SUB;
		if (str == "BH")return BH_SUB;
	}
	return 0;
}

//ר����movָ��ĸ�������
std::vector<unsigned char>mov_push(const std::string& str, unsigned char b, unsigned char a, int num, STRINF *m1, STRINF *m2)
{
	using namespace std;
	int ch_num;
	vector<unsigned char>d;
	vector<unsigned char>data;
	//��Ƕ���ڵĴ����Ƕ�ch[1]�δ���Ĵ���
	if (m2->explain == "byte" || m2->explain == "BYTE"){
		//������ch[1]�ڲ����������ţ�ֻ��Ϊ��ֵ�ַ�����
		if (!m2->w){
			d = Num(m2->str, 1, num);
			if (d.size() == 0){
				cout << "����-008��,���鱾�ַ�����" << str << endl;
				return data;
			}
			else{
				data.push_back(b);
				if (a != 0x00)data.push_back(a);
				else{
					data.push_back(0x46);
					data.push_back(0x00);
				}
				data.push_back(d[0]);
				return data;
			}
		}
		else{
			cout << "����-009,���鱾�ַ�����" << str << endl;
			return data;
		}
	}
	if (m2->explain == "word" || m2->explain == "WORD"){
		//��m1->explain == "byte"��m2->explain����Ϊ"word"
		cout << "����-010,���鱾�ַ���������Ϊword����" << str << endl;
		return data;
	}
	//��ch[1]��û���ֳ�˵����ʱ,Ҳ������������
	if (!m2->w){//û������ʱ
		//�ж��Ƿ�Ϊ�����ַ���
		ch_num = IntNum(m2->str, num);
		//if (ch_num<0){//С��0��˵��Ϊ���
		//cout << "*******" << m2->str << endl;
		if (ch_num>0xff)cout << "����,���ܴ���0xff(������򽫻ᶪ���������):" << str << endl;
		//����ת��Ϊ1�ֽڣ�
		d = NumToUc(ch_num, 1);
		data.push_back(b);
		if (a != 0x00)data.push_back(a);
		else{
			data.push_back(0x46);
			data.push_back(0x00);
		}
		data.push_back(d[0]);
		return data;
	}
	cout << "���鱾�д��룺" << str << endl;
	return data;
}

//cmd1:��cmd1=��b��ʱ��˵��m1->explain=="byte",��cmd1=��w��ʱ��˵��m1->explain=="word";
//cmd2:ȡֵ��0~15,�ֱ��Ӧ AX~DI,AL~BH��
//cmd1���������Ƿ�Ҫ��0x3e��cmd2����Ŀ��Ĵ�������
//explain��str��Ӧm2��ֵ
std::vector<unsigned char>BX_BP_SI_DI(char cmd1, char cmd2, std::string explain,std::string str,int num)
{
	using namespace std;
	bool n=false;
	short a=0, b=0;
	//��������
	

	vector<unsigned char>data;
	vector<unsigned char>d;
	if (cmd1 == 'b' && (cmd2 >= 0 && cmd2 < 8))n = true;//0<=cmd2<8˵��Ϊ16λ�Ĵ�����ֻ��16λ�Ĵ���ǰ��ָ����byte����Ҫ����0x3e
	if (cmd2 == 0){ a = 1; b = 0; }
	if (cmd2 == 1){ a = 1; b = 1; }
	if (cmd2 == 2){ a = 1; b = 2; }
	if (cmd2 == 3){ a = 1; b = 3; }
	if (cmd2 == 4){ a = 1; b = 4; }
	if (cmd2 == 5){ a = 1; b = 5; }
	if (cmd2 == 6){ a = 1; b = 6; }
	if (cmd2 == 7){ a = 1; b = 7; }
	if (cmd2 == 8){ a = 0; b = 0; }
	if (cmd2 == 9){ a = 0; b = 1; }
	if (cmd2 == 10){ a = 0; b = 2; }
	if (cmd2 == 11){ a = 0; b = 3; }
	if (cmd2 == 12){ a = 0; b = 4; }
	if (cmd2 == 13){ a = 0; b = 5; }
	if (cmd2 == 14){ a = 0; b = 6; }
	if (cmd2 == 15){ a = 0; b = 7; }
//*************************************************************
	if (str == "bx" || str == "BX"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][0]);
		return data;
	}
	if (str == "bp" || str == "BP"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][1]);
		data.push_back(0x00);
		return data;
	}
	if (str == "si" || str == "SI"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][2]);
		
		return data;
	}
	if (str == "di" || str == "DI"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][3]);
		return data;
	}
	//�ж�һ���Ƿ�Ϊ�����ַ���
	int number = IntNum(str, num);
	if (number>-1){//˵��number��һ��������ȡֵ��Ч
		if ((explain == "word" || explain == "WORD" || explain == "n") && cmd1 == 'b'&& cmd2<8){//��Ӧ��ָ���ʽ��mov byte 16λ�Ĵ�����[0x00]
			data.push_back(0x3e);
			data.push_back(0x8b);
			data.push_back(m_unch[cmd2]);
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		if (explain == "n" && cmd1 == 'b'&& cmd2 > 7){//��Ӧ��ָ���ʽ��mov byte 8λ�Ĵ�����[0x00]<==>mov 8λ�Ĵ�����[0x00]
			data.push_back(0x8a);
			data.push_back(m_unch[cmd2 - 8]);
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		if ((explain == "word" || explain == "WORD" || explain == "n") && cmd1 == 'w'&& cmd2<8){//��Ӧ��ָ���ʽ��mov word 16λ�Ĵ�����[0x00]<==>mov 16λ�Ĵ�����[0x00]
			if (cmd2 == 0)data.push_back(0xa1);
			else{
				data.push_back(0x8b);
				data.push_back(m_unch[cmd2]);
			}
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		if (explain == "n" && cmd1 == 'w'&& cmd2 > 7){//��Ӧ��ָ���ʽ��mov word 8λ�Ĵ�����[0x00];���ָ�ʽ�Ǵ����
			cout << "����-012��������룺" << str << endl;
			return data;
		}
		if ((explain == "byte" || explain == "BYTE") && cmd1 == 'b'&& cmd2<8){//��Ӧָ���ʽ mov	byte 16λ�Ĵ��� ,byte [0x23]������Ŀ��Ĵ���ֻ����8λ�Ĵ���
			cout << "����-013��Ŀ��Ĵ���ֻ����8λ�Ĵ���:" <<str<< endl;
			return data;
		}
		if ((explain == "byte" || explain == "BYTE") && cmd1 == 'b'&& cmd2>7){//��Ӧָ���ʽ mov	byte 8λ�Ĵ��� ,byte [0x23]��
			if (cmd2 == 8)data.push_back(0xa0);
			else{
				data.push_back(0x8a);
				data.push_back(m_unch[cmd2 - 8]);
			}
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}//************************************************
		if ((explain == "byte" || explain == "BYTE") && cmd1 == 'w'){//��Ӧָ���ʽ mov	byte 16λ�Ĵ��� ,byte [0x23]������Ŀ��Ĵ���ֻ����8λ�Ĵ���
			cout << "����-014��Ŀ��Ĵ���ֻ����16λ�Ĵ���:" << str << endl;
			return data;
		}
		if ((explain == "word" || explain == "WORD") && cmd1 == 'b'){//����
			cout << "����-015��Ŀ��Ĵ���Ӧָ��Ϊword:" << str << endl;
		}
	}
	cout << "[]�ڽ�����bx��bp��si��di,������룺" << str << endl;
	return data;
}
//str���Ĵ�������,a:0~3
std::vector<unsigned char>acdb(unsigned char n1,unsigned char n2,short a,std::string str)
{
	using namespace std;
	vector<unsigned char>data;
	for (int i = 0; i < 16; ++i){
		//�ж��Ƿ�Ϊ16λ�Ĵ���
		if (str == reg2[i]){
			data.push_back(n1);
			if (i>7)data.push_back(b1[i-8][a]);
			else data.push_back(b1[i][a]);
			if (a == 1)data.push_back(0x00);
			return data;
		}
		if (str == reg_1[i]){
			data.push_back(n2);
			if (i>7)data.push_back(b1[i - 8][a]);
			else data.push_back(b1[i][a]);
			if (a == 1)data.push_back(0x00);
			return data;
		}
	}
	cout << "������룺" << str << endl;
	return data;
}
//cmdΪ�������֣���cmd=1ʱ��ָ���ʽ��mov [0x00],ax ����cmd=2ʱ��mov ax��[0x00]
std::vector<unsigned char>acdb_m1_num(short cmd,std::string str,std::string m1_str,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d = Num(m1_str, 2, num);
	unsigned char n_ax=0xa3,n_al=0xa2, n_16=0x89,n_8=0x88,n_s=0x8c;
	//����cmd
	if (cmd == 2){
		n_ax = 0xa1;
		n_al = 0xa0;
		n_16 = 0x8b;
		n_8 = 0x8a;
		n_s = 0x8e;
	}
	for (int i = 0; i < 16; ++i){
		//�ж��Ƿ�Ϊ16λ�Ĵ���
		if (str == reg2[i]){
			if (i == 0 || i == 8)//reg[0]��reg[8]��Ӧ���ַ���ʱax���������
				data.push_back(n_ax);
			else{
				data.push_back(n_16);
				if (i>7)data.push_back(m_unch[i - 8]);
				else data.push_back(m_unch[i]);
			}
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		//�ж��Ƿ�Ϊ8λ�Ĵ���
		if (str == reg2[i]){
			if (i == 0 || i == 8)//reg[0]��reg[8]��Ӧ���ַ���ʱax���������
				data.push_back(n_al);
			else{
				data.push_back(n_8);
				if (i>7)data.push_back(m_unch[i - 8]);
				else data.push_back(m_unch[i]);
			}
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
	}
	if (str == "es" || str == "ES"){
		data.push_back(n_s);
		data.push_back(0x06);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	if (str == "cs" || str == "CS"){
		data.push_back(n_s);
		data.push_back(0x0e);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	if (str == "ss" || str == "SS"){
		data.push_back(n_s);
		data.push_back(0x16);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	if (str == "ds" || str == "DS"){
		data.push_back(n_s);
		data.push_back(0x1e);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	cout << "����--017,���飺" << str<<endl;
	return data;
}
//ר����movָ��ĸ�������
STRINF *hep(const std::string& str)
{
	using namespace std;
	int str_size = str.size();
	int lk, rk, k;
	STRINF *m = new STRINF;
	//ȥ��β���Ŀո�
	while (str_size>0 && (str[str_size - 1] == 0x20 || str[str_size - 1] == '\t'))str_size--;
	k = str.find(0x20);
	if (k >= str_size)k = str.find('\t');
	//k�����˿ո��λ�ã�����еĻ�������k����һ��Զ�����ַ������ȵ�ֵ,��С��0��ֵ
	if (k < str_size && k >= 0){
		m->explain = str.substr(0, k);
		lk = str.find('[');
		rk = str.find(']');
	
		if (lk < str_size && rk < str_size && lk >= 0 && rk >= 0){//�ж�������
			m->str = str.substr(lk + 1, rk - lk - 1);
			m->lk = lk;
			m->rk = rk;
			m->w = true;
			return m;
		}
		else{
			//�����ո��������
			while (k < str_size && (str[k] == 0x20 || str[k] == '\t'))k++;
			m->str = str.substr(k, str_size - k);
			m->lk = 0;
			m->rk = 0;
			m->w = false;
			return m;
		}
	}
	else{//û�пո�
		m->explain = "n";//˵������Ϊn
		//����������
		lk = str.find('[');
		rk = str.find(']');
		
		if (lk < str_size && rk < str_size && lk >= 0 && rk >= 0){
			m->str = str.substr(lk + 1, rk - lk - 1);
			m->lk = lk;
			m->rk = rk;
			m->w = true;
			return m;
		}
		else{
			m->str = str.substr(0,str_size);
			m->lk = 0; m->rk = 0;
			m->w = false;
			return m;
		}
	}
	return m;
}