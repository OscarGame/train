/*InsPro.cpp��������ָ����뺯��*/
#include<string>
#include<iostream>
#include<vector>
#include<ctype.h>
//*�Զ���ͷ�ļ�
//#include"MyRegister.h"
#include"assistFun.h"
#include"HelpInsPro.h"
#include"MyRegister.h"
#include"Struct_self.h"

//str���ַ�����n����ʼλ�ã�num�����ļ���main.cpp����Number
std::vector<unsigned char>Move1( STRINF *m1, STRINF *m2,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>w;
	unsigned char a,b,c,c_s,d,f;
	string ch[2];
	ch[0] = m1->str;
	ch[1] = m2->str;
	//ch[0] = CutStr(str,n);
	//ch[1] = CutStr(str, str.find(',')+1);
	//cout << ch[0] << '\t' << ch[1] << endl;
	a=TwoRegBin(ch,1);
	b=TwoRegBin(ch,2);
	c=TwoRegBin(ch,3);
	c_s = TwoRegBin(ch, 4);
	//����Ƿ�Ϊ�Ĵ���֮�丳ֵ
	if (a){
		data.push_back(0x88);
		data.push_back(a);
		return data;
	}
	else if (b){
		data.push_back(0x89);
		data.push_back(b);
		//cout << "**************" << endl;
		return data;
	}
	else if (c){
		data.push_back(0x8c);
		data.push_back(c);
		return data;
	}
	else if (c_s){
		data.push_back(0x8e);
		data.push_back(c_s);
		return data;
	}
	else{
		d = RegACDB(ch[0], 1);//�ж�8λ�Ĵ���
		f = RegACDB(ch[0], 2);//�ж�16λ�Ĵ���
		if(d){//��d���棬˵�����ϸߵ�λ�Ĵ���
			data.push_back(d);
			//�����ж��Ƿ�Ϊ�ַ���$��������ǣ�д��3����Ԫ�أ���data�Ĵ�С���ڵ���4,���򷵻ؽ��Ĵ��������ֵת����Ľ��
			if (ch[1] != "$"){
				//д��Ĵ���������������ֵ����������16���ƻ�ʮ�����ַ���
				w = Num(ch[1], 1,num);
				if (w.size() > 0){
					data.insert(data.end(), w.begin(), w.end());
					return data;
				}
				else{
					//��ʱdata�Ĵ�СΪ4�����ȷ����Ϊ���
					data.insert(data.end(), 2, 0x00);
					data.push_back(2);
					return data;
				}
			}
			else {
				w = NumToUc(num, 1);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
		else if(f){
			data.push_back(f);//д��Ĵ���
			//ͬ��
			if (ch[1] != "$"){
				//д��Ĵ���������������ֵ����������16���ƻ�ʮ�����ַ���
				w = Num(ch[1], 2,num);
				//�ж��Ƿ��Ǳ���ַ���
				if (w.size() > 0){
					data.insert(data.end(), w.begin(), w.end());
					return data;
				}
				else{
					//��ʱdata�Ĵ�СΪ4�����ȷ����Ϊ���
					data.insert(data.end(), 2, 0x00);
					data.push_back(1);
					return data;
				}
			}
			else {
				w = NumToUc(num, 2);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
		else{
			cout << "����MOVָ�����error-005!" << endl;
			return data;
		}
		cout << "����MOVָ�����error-019!" << endl;
		return data;
	}
	//���䣬֮ǰû�з��ֶμĴ����ĸ�ֵ
	
	return data;
}

std::vector<unsigned char>Move2(const std::string& str,STRINF *m1, STRINF *m2, int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	//�ж�˵����Ϊbyteʱ
	if (m1->explain == "byte" || m1->explain == "BYTE"){
		//���ж��Ƿ���������
		if (m1->w){
			//�����ŵĻ���
			if (m1->str == "bx" || m1->str == "BX"){
				return mov_push(str, 0xc6, 0x07, num, m1, m2);
			}
			//�����ŵĻ���
			if (m1->str == "si" || m1->str == "SI"){
				return mov_push(str, 0xc6, 0x04, num, m1, m2);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return mov_push(str, 0xc6, 0x05, num, m1, m2);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return mov_push(str, 0xc6, 0x00, num, m1, m2);
			}//��������ֵ�ַ��������
			d = Num(m1->str, 2, num);
			if ((int)d.size() > 0){
				data = mov_push(str, 0xc6, 0x06, num, m1, m2);
				data.insert(data.end() - 1, d.begin(), d.end());
				return data;
			}
			//˵��[]�ڼȲ���sp��bp��si��di��Ҳ������ֵ�ַ���,����������������
			cout << "���鱾���룺" << str << endl;
			return data;
		}
		//��m1û�����ţ�Ȼ���ж�m2�Ƿ�������
		if (m2->w){//m2������ʱ
			if (m2->explain == "word"){ cout << "����-001������ָ��Ϊword��" << str << endl; }
			if (m1->str == "ax" || m1->str == "AX"){
				return BX_BP_SI_DI('b', 0,m2->explain, m2->str,num);
			}
			if (m1->str == "cx" || m1->str == "CX"){
				return BX_BP_SI_DI('b', 1, m2->explain, m2->str, num);
			}
			if (m1->str == "dx" || m1->str == "DX"){
				return BX_BP_SI_DI('b', 2, m2->explain, m2->str, num);
			}
			if (m1->str == "bx" || m1->str == "BX"){
				return BX_BP_SI_DI('b', 3, m2->explain, m2->str, num);
			}
			if (m1->str == "sp" || m1->str == "SP"){
				return BX_BP_SI_DI('b', 4, m2->explain, m2->str, num);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return BX_BP_SI_DI('b', 5, m2->explain, m2->str, num);
			}
			if (m1->str == "si" || m1->str == "SI"){
				return BX_BP_SI_DI('b', 6, m2->explain, m2->str, num);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return BX_BP_SI_DI('b', 7, m2->explain, m2->str, num);
			}
			//64465465456****8λ�Ĵ���***********************
			if (m1->str == "al" || m1->str == "AL"){
				return BX_BP_SI_DI('b', 8, m2->explain, m2->str, num);
			}
			if (m1->str == "cl" || m1->str == "CL"){
				return BX_BP_SI_DI('b', 9, m2->explain, m2->str, num);
			}
			if (m1->str == "dl" || m1->str == "DL"){
				return BX_BP_SI_DI('b', 10, m2->explain, m2->str, num);
			}
			if (m1->str == "bl" || m1->str == "BL"){
				return BX_BP_SI_DI('b', 11, m2->explain, m2->str, num);
			}
			if (m1->str == "ah" || m1->str == "AH"){
				return BX_BP_SI_DI('b', 12, m2->explain, m2->str, num);
			}
			if (m1->str == "ch" || m1->str == "CH"){
				return BX_BP_SI_DI('b', 13, m2->explain, m2->str, num);
			}
			if (m1->str == "dh" || m1->str == "DH"){
				return BX_BP_SI_DI('b', 14, m2->explain, m2->str, num);
			}
			if (m1->str == "bh" || m1->str == "BH"){
				return BX_BP_SI_DI('b', 15, m2->explain, m2->str, num);
			}
			cout << "����-011,������룺" << str << endl;
			return data;
		}
	}
	//******************************************************************
	if (m1->explain == "word" || m1->explain == "WORD"){
		//���ж�M1�Ƿ���������
		if (m1->w){
			//�����ŵĻ���
			if (m1->str == "bx" || m1->str == "BX"){
				return mov_push(str, 0xc7, 0x07, num, m1, m2);
			}
			//�����ŵĻ���
			if (m1->str == "si" || m1->str == "SI"){
				return mov_push(str, 0xc7, 0x04, num, m1, m2);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return mov_push(str, 0xc7, 0x05, num, m1, m2);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return mov_push(str, 0xc7, 0x00, num, m1, m2);
			}//��������ֵ�ַ��������
			d = Num(m1->str, 2, num);
			if ((int)d.size() > 0){
				data = mov_push(str, 0xc7, 0x06, num, m1, m2);
				data.insert(data.end() - 1, d.begin(), d.end());
				return data;
			}
			//˵��[]�ڼȲ���sp��bp��si��di��Ҳ������ֵ�ַ���,����������������
			cout << "���鱾���룺" << str << endl;
			return data;
		}
		//��m1û�����ţ�Ȼ���ж�m2�Ƿ�������
		if (m2->w){//m2������ʱ
			if (m2->explain == "word"){ cout << "����-001������ָ��Ϊword��" << str << endl; }
			if (m1->str == "ax" || m1->str == "AX"){
				return BX_BP_SI_DI('w', 0, m2->explain, m2->str, num);
			}
			if (m1->str == "cx" || m1->str == "CX"){
				return BX_BP_SI_DI('w', 1, m2->explain, m2->str, num);
			}
			if (m1->str == "dx" || m1->str == "DX"){
				return BX_BP_SI_DI('w', 2, m2->explain, m2->str, num);
			}
			if (m1->str == "bx" || m1->str == "BX"){
				return BX_BP_SI_DI('w', 3, m2->explain, m2->str, num);
			}
			if (m1->str == "sp" || m1->str == "SP"){
				return BX_BP_SI_DI('w', 4, m2->explain, m2->str, num);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return BX_BP_SI_DI('w', 5, m2->explain, m2->str, num);
			}
			if (m1->str == "si" || m1->str == "SI"){
				return BX_BP_SI_DI('w', 6, m2->explain, m2->str, num);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return BX_BP_SI_DI('w', 7, m2->explain, m2->str, num);
			}
			//64465465456****8λ�Ĵ���***********************
			if (m1->str == "al" || m1->str == "AL"){
				return BX_BP_SI_DI('w', 8, m2->explain, m2->str, num);
			}
			if (m1->str == "cl" || m1->str == "CL"){
				return BX_BP_SI_DI('w', 9, m2->explain, m2->str, num);
			}
			if (m1->str == "dl" || m1->str == "DL"){
				return BX_BP_SI_DI('w', 10, m2->explain, m2->str, num);
			}
			if (m1->str == "bl" || m1->str == "BL"){
				return BX_BP_SI_DI('w', 11, m2->explain, m2->str, num);
			}
			if (m1->str == "ah" || m1->str == "AH"){
				return BX_BP_SI_DI('w', 12, m2->explain, m2->str, num);
			}
			if (m1->str == "ch" || m1->str == "CH"){
				return BX_BP_SI_DI('w', 13, m2->explain, m2->str, num);
			}
			if (m1->str == "dh" || m1->str == "DH"){
				return BX_BP_SI_DI('w', 14, m2->explain, m2->str, num);
			}
			if (m1->str == "bh" || m1->str == "BH"){
				return BX_BP_SI_DI('w', 15, m2->explain, m2->str, num);
			}
			cout << "����-011,������룺" << str << endl;
			return data;
		}
		cout << "����--016��������룺" << str << endl;
		return data;
	}
	//******************�ָ���****���m1��������***********************
	if (m1->w){
		if (m1->str == "bx" || m1->str == "BX"){
			return acdb(0x89, 0x88, 0, m2->str);
		}
		if (m1->str == "bp" || m1->str == "BP"){
			return acdb(0x89, 0x88, 1, m2->str);
		}
		if (m1->str == "si" || m1->str == "SI"){
			return acdb(0x89, 0x88, 2, m2->str);
		}
		if (m1->str == "di" || m1->str == "DI"){
			return acdb(0x89, 0x88, 3, m2->str);
		}
		//��Ϊ��ֵ�ַ���ʱ
		num = IntNum(m1->str, num);
		if (num > -1){
			return acdb_m1_num(1,m2->str, m1->str, num);
		}
		cout << "����--018��������룺" << str << endl;
		return data;
	}
	//******************�ָ���****���m2��������***********************
	if (m2->w){
		if (m2->str == "bx" || m2->str == "BX"){
			return acdb(0x8b,0x8a,0, m1->str);
		}
		if (m2->str == "bp" || m2->str == "BP"){
			return acdb(0x8b, 0x8a, 1, m1->str);
		}
		if (m2->str == "si" || m2->str == "SI"){
			return acdb(0x8b, 0x8a, 2, m1->str);
		}
		if (m2->str == "di" || m2->str == "DI"){
			return acdb(0x8b, 0x8a, 3, m1->str);
		}
		//��Ϊ��ֵ�ַ���ʱ
		num = IntNum(m2->str, num);
		if (num > -1){
			return acdb_m1_num(2,m1->str, m2->str, num);
		}
		cout << "����--019��������룺" << str << endl;
		return data;
	}
	return data;
}

std::vector<unsigned char>MOVE(const std::string& str, int k, int num)
{
	using namespace std;
	int str_size = str.size();
	//vector<unsigned char>data;
	//vector<unsigned char>d;
	string *ch;//ch1��ch2�ֱ��������涺��ǰ����ַ�����DEST �� SRC��
	//�����ո�
	while (k < str_size && (str[k] == 0x20 || str[k] == '\t'))k++;
	ch = CS(str, k);//���涺��ǰ�������ַ���
	STRINF *m1 = hep(ch[0]);
	STRINF *m2 = hep(ch[1]);
	
	if (!m1->w && !m2->w){
		//û������ʱ����Move1����Ҫ��һЩ�����������
		if ((m1->explain == "byte" || m1->explain == "BYTE") && (m2->explain == "word" || m2->explain == "WORD"))cout << "���棬����ʹ��word�����򽫶����������,������룺" << str << endl;
		return Move1(m1, m2, num);
	}//������ʱ����Move2
	//cout << "����move2" << endl;
	return Move2(str, m1, m2, num);
}
//Data���������ڴ���DB,DW,DDָ��,str:����ָ���ַ�����num��ָ���ַ�֮���һ�ֽ�λ�ã�fix����ָ��ռ�õ��ֽ���
std::vector<unsigned char>DataBWD(const std::string& str, int k, int fix,int num)
{
	using namespace std;
	string ch;
	vector<unsigned char>data;
	vector<unsigned char>d;
	bool w = false;
	while (k < (int)str.size() && (str[k] == 0x20 || str[k] == '\t'))k++;
	while (k<(int)str.size() && str[k] != '\n' && str[k] != '\0'){
		if (!w&&str[k] == '"'){ w = true; k++; }
		if (w){
			if (str[k] == '"')break;
			data.push_back(str[k]);
			k++;
		}
		else{
			ch = CutStrDBWD(str, k);
			if ((int)ch.size() > 0)k = ch.size() + k + 1;
			else k++;
			d = Num(ch, fix, num);
			data.insert(data.end(), d.begin(), d.end());
		}
	}
	return data;
}

long Organ(const std::string& str, int n,int num)
{
	std::string m = CutStr(str, n);
	return IntNum(m,num);
}

int ReserveByte(const std::string& str, int n, int num)
{
	using namespace std;
	string ch = CutStr(str, n);
	return IntNum(ch,num);
}

std::vector<unsigned char>Additive(const std::string& str,int n,int num)
{
	using namespace std;

	vector<unsigned char>data;
	vector<unsigned char>w;
	unsigned char a, b, c, d, f;
	string ch[2];
	ch[0] = CutStr(str, n);
	ch[1] = CutStr(str, str.find(',') + 1);
	//cout << ch[0] << '\t' << ch[1] << endl;
	a = TwoRegBin(ch, 1);
	b = TwoRegBin(ch, 2);
	c = TwoRegBin(ch, 3);
	//����Ƿ�Ϊ�Ĵ���֮�丳ֵ
	if (a){
		//cout << "aaaaaaaaaaaaaaaa"<<endl;
		data.push_back(0x00);
		data.push_back(a);
		return data;
	}
	else if (b){
		//cout << "bbbbbbbbbbbbbbbbb" << endl;
		data.push_back(0x01);
		data.push_back(b);
		//cout << "**************" << endl;
		return data;
	}
	else if (c){
		cout << "�μĴ�������ֱ�Ӳ������!-error-007!" << endl;
	}
	//˵��ch[1]��һ�������ַ�������
	//����Ƿ���ax�Ĵ���
	else if (ch[0] == "ax" || ch[0] == "AX"){
		data.push_back(0x05);
		w = Num(ch[1], 2, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else if (ch[0] == "al" || ch[0] == "AL"){
		data.push_back(0x04);
		w = Num(ch[1], 1, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else{
		//�жϼĴ���λ��
		d = regadd(ch[0], 1);//������ֵ��Ϊ0����˵��ch[0]��8λ�Ĵ�������
		f = regadd(ch[0], 2);//������ֵ��Ϊ0����˵��ch[1]��16λ�Ĵ�������
		if (d){
			//�ж�Ϊ8λ�Ĵ���
			data.push_back(0x80);
			data.push_back(d);
			w = Num(ch[1], 1, num);
			data.insert(data.end(), w.begin(), w.end());
			return data;
		}
		else if (f){
			//�ж�Ϊ16λ�Ĵ���
			if (IntNum(ch[1], num) > 0x7f){
				//��ֵӦת��Ϊ2�ֽ�
				w = Num(ch[1], 2, num);
				data.push_back(0x81);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
			else{
				w = Num(ch[1], 1, num);
				data.push_back(0x83);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
	}
	return data;
}

std::vector<unsigned char>Subtraction(const std::string& str, int n, int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>w;
	unsigned char a, b, c, d, f;
	string ch[2];
	ch[0] = CutStr(str, n);
	ch[1] = CutStr(str, str.find(',') + 1);
	//cout << ch[0] << '\t' << ch[1] << endl;
	a = TwoRegBin(ch, 1);
	b = TwoRegBin(ch, 2);
	c = TwoRegBin(ch, 3);
	//����Ƿ�Ϊ�Ĵ���֮�丳ֵ
	if (a){
		//cout << "aaaaaaaaaaaaaaaa"<<endl;
		data.push_back(0x28);
		data.push_back(a);
		return data;
	}
	else if (b){
		//cout << "bbbbbbbbbbbbbbbbb" << endl;
		data.push_back(0x29);
		data.push_back(b);
		//cout << "**************" << endl;
		return data;
	}
	else if (c){
		cout << "�μĴ�������ֱ�Ӳ������!-error-007!" << endl;
	}
	//˵��ch[1]��һ�������ַ�������
	//����Ƿ���ax�Ĵ���
	else if (ch[0] == "ax" || ch[0] == "AX"){
		data.push_back(0x2d);
		w = Num(ch[1], 2, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else if (ch[0] == "al" || ch[0] == "AL"){
		data.push_back(0x2c);
		w = Num(ch[1], 1, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else{
		//�жϼĴ���λ��
		d = regsub(ch[0], 1);//������ֵ��Ϊ0����˵��ch[0]��8λ�Ĵ�������
		f = regsub(ch[0], 2);//������ֵ��Ϊ0����˵��ch[1]��16λ�Ĵ�������
		if (d){
			//�ж�Ϊ8λ�Ĵ���
			data.push_back(0x80);
			data.push_back(d);
			w = Num(ch[1], 1, num);
			data.insert(data.end(), w.begin(), w.end());
			return data;
		}
		else if (f){
			//�ж�Ϊ16λ�Ĵ���
			if (IntNum(ch[1], num) > 0x7f){
				//��ֵӦת��Ϊ2�ֽ�
				w = Num(ch[1], 2, num);
				data.push_back(0x81);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
			else{
				w = Num(ch[1], 1, num);
				data.push_back(0x83);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
	}
	return data;
}
//����jmp��䡣str:�ַ�����n����ʼ�ַ�����ȡλ�ã�m��main.cpp�е�jp
std::vector<unsigned char>Jemp()
{
	//ֱ�ӷ���0xeb��0x00
	std::vector<unsigned char>data{ 0xeb, 0x00 };
	return data;
}

//����je��䡣
std::vector<unsigned char>Je()
{
	//ֱ�ӷ���0x74��0x00
	std::vector<unsigned char>data{ 0x74, 0x00 };
	return data;
}

//����jbe��䡣
std::vector<unsigned char>Jbe()
{
	//ֱ�ӷ���0x76��0x00
	std::vector<unsigned char>data{ 0x76, 0x00 };
	return data;
}

//����jbe��䡣
std::vector<unsigned char>Jb()
{
	//ֱ�ӷ���0x72��0x00
	std::vector<unsigned char>data{ 0x72, 0x00 };
	return data;
}

std::vector<unsigned char>Push(const std::string& str, int n,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	string ch;
	ch = CutStr(str,n);
	if (ch == "AX" || ch == "ax"){
		data.push_back(0x50);
		return data;
	}
	else if (ch == "CX" || ch == "cx"){
		data.push_back(0x51);
		return data;
	}
	else if (ch == "DX" || ch == "dx"){
		data.push_back(0x52);
		return data;
	}
	else if (ch == "BX" || ch == "bx"){
		data.push_back(0x53);
		return data;
	}
	else if (ch == "SP" || ch == "sp"){
		data.push_back(0x54);
		return data;
	}
	else if (ch == "BP" || ch == "bp"){
		data.push_back(0x55);
		return data;
	}
	else if (ch == "SI" || ch == "si"){
		data.push_back(0x56);
		return data;
	}
	else if (ch == "DI" || ch == "di"){
		data.push_back(0x57);
		return data;
	}
	else if (ch == "ES" || ch == "es"){
		data.push_back(0x6);
		return data;
	}
	else if (ch == "CS" || ch == "cs"){
		data.push_back(0xe);
		return data;
	}
	else if (ch == "SS" || ch == "ss"){
		data.push_back(0x16);
		return data;
	}
	else if (ch == "DS" || ch == "ds"){
		data.push_back(0x1e);
		return data;
	}
	else {
		int k = IntNum(ch, num);
		if (k > 0x7f){
			data.push_back(0x68);
			d = Num(ch, 2, num);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		else if(k>=0&&k<0x80){
			data.push_back(0x6a);
			d = Num(ch, 1, num);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		else{
			return data;
			//�������data��СΪ0��˵��Ϊ���
		}
	}
}

std::vector<unsigned char>Pop(const std::string& str, int n)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	string ch;
	ch = CutStr(str, n);
	if (ch == "AX" || ch == "ax"){
		data.push_back(0x58);
		return data;
	}
	else if (ch == "CX" || ch == "cx"){
		data.push_back(0x59);
		return data;
	}
	else if (ch == "DX" || ch == "dx"){
		data.push_back(0x5a);
		return data;
	}
	else if (ch == "BX" || ch == "bx"){
		data.push_back(0x5b);
		return data;
	}
	else if (ch == "SP" || ch == "sp"){
		data.push_back(0x5c);
		return data;
	}
	else if (ch == "BP" || ch == "bp"){
		data.push_back(0x5d);
		return data;
	}
	else if (ch == "SI" || ch == "si"){
		data.push_back(0x5e);
		return data;
	}
	else if (ch == "DI" || ch == "di"){
		data.push_back(0x5f);
		return data;
	}
	else if (ch == "ES" || ch == "es"){
		data.push_back(0x7);
		return data;
	}
	else if (ch == "CS" || ch == "cs"){
		data.push_back(0xf);
		return data;
	}
	else if (ch == "SS" || ch == "ss"){
		data.push_back(0x17);
		return data;
	}
	else if (ch == "DS" || ch == "ds"){
		data.push_back(0x1f);
		return data;
	}
	else {
		cout << "����popָ��:" << str << endl;
	}
	return data;
}
//INTָ��Ϊ�Կ�����ָ��,��һ���ж�ָ��
std::vector<unsigned char>Int(std::string& str,int n,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	data.push_back(0xcd);
	str = CutStr(str, n);
	d = Num(str, 1, num);
	data.push_back(d[0]);
	return data;
}

//cmpָ��Ƚ�ָ��
std::vector<unsigned char>Cmp(const std::string& str,int n,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	long str_size = str.size();
	short a;//��������˵���ַ������ͣ�byteΪ1��wordΪ2
	string *ch;
	unsigned char w[] = {0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff};
	unsigned char a1, a2;
	while (n<str_size && (str[n] == 0x20 || str[n] == '\t'))n++;
	ch = CS(str,n);
	STRINF *cm0 = hep(ch[0]);
	STRINF *cm1 = hep(ch[1]);
	ch[0] = cm0->str;
	ch[1] = cm1->str;
	a1 = TwoRegBin(ch, 1);//8λ�Ĵ���֮��
	a2 = TwoRegBin(ch, 2);//16λ�Ĵ���֮��
	if (a1){
		data.push_back(0x38);
		data.push_back(a1);
		return data;
	}
	if (a2){
		data.push_back(0x39);
		data.push_back(a2);
		return data;
	}
	if (cm1->explain == "byte" || cm1->explain == "BYTE")a = 1;
	if (cm1->explain == "word" || cm1->explain == "WORD")a = 2;
	for (int i = 0; i < 16; ++i){
		if (reg2[i] == cm0->str){
			if (i==0 ||i==8){
				data.push_back(0x3d);
				d = Num(cm1->str, 2, num);
				data.insert(data.end(), d.begin(), d.end());
				return data;
			}
			str_size = IntNum(cm1->str,num);
			if (str_size>0x7f)a = 2;
			else a = 1;
			d = NumToUc(str_size, a);
			data.push_back(0x85 - 2 * a);
			if (i>8)data.push_back(w[i-8]);
			else data.push_back(w[i]);
			data.insert(data.end(), d.begin(), d.end());
			return data;

		}
		if (reg_1[i] == cm0->str){
			if (i == 0 || i == 8){
				data.push_back(0x3c);
				d = Num(cm1->str, 1, num);
				data.push_back(d[0]);
				return data;
			}
			data.push_back(0x80);
			if (i>8)data.push_back(w[i - 8]);
			else data.push_back(w[i]);
			d = Num(cm1->str, 1, num);
			data.push_back(d[0]);
			return data;

		}
	}
	cout << "����������룺" << str << endl;
	return data;
}

//��λָ��,cmd_ch���߳�����shr���ƣ�����shl���ƣ��������������Ƿ����ĵڶ��������룬shr��0xe8~0xef��shl:0xe0~0xe7
std::vector<unsigned char>Shl_Shr(const std::string& str, int n, int num,unsigned char cmd_ch)
{
	using namespace std;
	string *ch;
	ch = CS(str, n);//CS����������ȡ���������ߵ�Ŀ��Ĵ�������Դ���������Զ�ȥ���ո�
	unsigned char m[2] = {0};
	vector<unsigned char>data;
	vector<unsigned char>d;
	for (int i = 0; i < 16; ++i){
		if (ch[0] == reg_1[i]){
			m[0] = 0xc0;
			if (i>7)m[1] = cmd_ch + i - 8;
			else m[1] = cmd_ch + i;

		}
		if (ch[0] == reg2[i]){
			m[0] = 0xc1;
			if (i>7)m[1] = cmd_ch + i - 8;
			else m[1] = cmd_ch + i;
		}
	}
	d = Num(ch[1], 1, num);
	if ((int)d.size() > 0 && m[0] != 0 && m[1] != 0){
		data.push_back(m[0]);
		data.push_back(m[1]);
		data.push_back(d[0]);
		return data;
	}
	cout << "����-021������ָ�" << str << endl;
	return data;
}
//����in��outָ�w�����ж���in����out�����w=i��Ϊin�������w=o����ô��outָ�
std::vector<unsigned char>In_Out(const std::string& str, int n, int num,char w)
{
	using namespace std;
	string *ch = CS(str, n);
	vector<unsigned char>d=Num(ch[1],1,num);
	vector<unsigned char>data;
	unsigned char ax_ch=0xe5, al_ch=0xe4,ax_dx=0xed,al_dx=0xec;
	if (w = 'o'){
		ax_ch = 0xe7; al_ch = 0xe6; ax_dx = 0xef; al_dx = 0xee;
	}
	else if (w != 'i'){
		cout << "�����ж�" << endl; return data;
	}
	if ((ch[0] == "ax" || ch[0] == "AX") && (int)d.size() > 0){
		data.push_back(ax_ch);
		data.push_back(d[0]);
		return data;
	}
	if ((ch[0] == "al" || ch[0] == "AL") && (int)d.size() > 0){
		data.push_back(al_ch);
		data.push_back(d[0]);
		return data;
	}
	if ((ch[0] == "ax" || ch[0] == "AX") && (ch[0] == "dx" || ch[0] == "DX")){
		data.push_back(ax_dx);
		return data;
	}
	if ((ch[0] == "al" || ch[0] == "AL") && (ch[0] == "dx" || ch[0] == "DX")){
		data.push_back(al_dx);
		return data;
	}
	cout << "����-022��������룺" << str << endl;
	return data;
}
//����and��or��xorָ�wȡֵΪ��a����o����x��,�ֱ��Ӧ
std::vector<unsigned char>Logic(const std::string& str, int n, int num, char w_n)
{
	using namespace std;
	vector<unsigned char>data;
	string *ch = CS(str, n);
	unsigned char dt8 = 0, dt16 = 0, dt_ax = 0, dt_al = 0, dt8_num = 0, dt16_num[2] = {0};

	unsigned char a, b;
	const unsigned char *mm;
	if (w_n == 'a'){
		//�Ĵ���֮��
		dt8 = 0x20;
		dt16 = 0x21;
		//�Ĵ�������ֵ
		dt_al = 0x24;
		dt_ax = 0x25;
		dt8_num = 0x80;
		dt16_num[0] = 0x81;//������������0x80ʱ
		dt16_num[1] = 0x83;//��������С��0x80ʱ
		mm = logic_and;
	}
	else if (w_n == 'o'){
		//�Ĵ���֮��
		dt8 = 0x08;
		dt16 = 0x09;
		//�Ĵ�������ֵ
		dt_al = 0x0c;
		dt_ax = 0x0d;
		dt8_num = 0x80;
		dt16_num[0] = 0x81;//������������0x80ʱ
		dt16_num[1] = 0x83;//��������С��0x80ʱ
		mm = logic_or;
	}
	else if (w_n == 'x'){
		//�Ĵ���֮��
		dt8 = 0x30;
		dt16 = 0x31;
		//�Ĵ�������ֵ
		dt_al = 0x34;
		dt_ax = 0x35;
		dt8_num = 0x80;
		dt16_num[0] = 0x81;//������������0x80ʱ
		dt16_num[1] = 0x83;//��������С��0x80ʱ
		mm = logic_xor;
	}
	else{
		cout << "����-025������login����������" << w_n << endl;
		return data;
	}
	a = TwoRegBin(ch, 1);//����Ƿ���8λ�Ĵ���
	b = TwoRegBin(ch, 2);//����Ƿ���16λ�Ĵ���
	if (a){
		data.push_back(dt8);
		data.push_back(a);
		return data;
	}
	if (b){
		data.push_back(dt16);
		data.push_back(b);
		return data;
	}
	vector<unsigned char>d;
	int k = IntNum(ch[1], num);
	cout << "k=" << k << endl;
	d = NumToUc(k, 2);
	cout << "d=" << hex<< (int)d[0] << endl;
	if (d.size() <= 0){
		cout << "����-023������ָ��:" << str << endl;
		return data;
	}
	for (int i = 0; i < 16; ++i){
		if (ch[0] == reg_1[i]){
			if (i == 0 || i == 8){//�ж�Ϊal�Ĵ���
				data.push_back(dt_al);
				data.push_back(d[0]);
				return data;
			}
			data.push_back(dt8_num);
			if (i>7)data.push_back(mm[i - 8]);
			else data.push_back(mm[i]);
			data.push_back(d[0]);
			return data;
		}
		if (ch[0] == reg2[i]){
			if (i == 0 || i == 8){
				data.push_back(dt_ax);
				data.push_back(d[0]);
				data.push_back(d[1]);
				return data;
			}
			if (k > 0x7f) data.push_back(dt16_num[0]);
			else data.push_back(dt16_num[1]);
			if (i > 7)data.push_back(mm[i - 8]);
			else data.push_back(mm[i]);
			data.push_back(d[0]);
			if (k >0x7b)data.push_back(d[1]);
			return data;
		}
	}
	cout << "����-024������ָ��:" << str << endl;
	return data;
}
//notȡ��ָ��
std::vector<unsigned char>Not(const std::string& str, int n)
{
	using namespace std;
	string ch = CutStr(str, n);
	vector<unsigned char>data;
	for (int i = 0; i < 16; ++i){
		if (ch == reg_1[i]){
			data.push_back(0xf6);
			if (i>7)data.push_back(logic_not[i - 8]);
			else data.push_back(logic_not[8]);
			return data;
		}
		if (ch == reg2[i]){
			data.push_back(0xf7);
			if (i>7)data.push_back(logic_not[i - 8]);
			else data.push_back(logic_not[8]);
			return data;
		}
	}
	cout << "����-026���������:" << str << endl;
	return data;
}

//mul�˷�ָ��
std::vector<unsigned char>Mul(const std::string& str, int n)
{
	using namespace std;
	string ch = CutStr(str, n);
	vector<unsigned char>data;
	for (int i = 0; i < 16; ++i){
		if (ch == reg_1[i]){
			data.push_back(0xf6);
			if (i>7)data.push_back(logic_and[i - 8]);
			else data.push_back(logic_and[8]);
			return data;
		}
		if (ch == reg2[i]){
			data.push_back(0xf7);
			if (i>7)data.push_back(logic_and[i - 8]);
			else data.push_back(logic_and[8]);
			return data;
		}
	}
	//�ж��Ƿ�������
	int lk, rk, str_size = str.size();
	lk=str.find('[');
	rk = str.find(']');
	if (lk < str_size && rk < str_size && !(rk < 0) && !(lk < 0)){
		ch.clear();
		while (n <str_size && (str[n] == 0x20 || str[n] == '\t'))n++;
		while (n < str_size && (str[n] != '\n' || str[n] == '\0')){
			if (str[n] == 0x20 || str[n] == '\t')break;
			if (isalnum(str[n]))ch.push_back(str[n]);
			n++;
		}
		if (ch == "word" || ch == "WORD")data.push_back(0xf7);
		else if (ch == "byte" || ch == "BYTE")data.push_back(0xf6);
		else {
			cout << "����-027���������:" << str << endl; return data;
		}
		ch.clear(); ch = str.substr(lk+1, rk - lk-1);
		cout << "**************" << ch << endl;
		if (ch == "bx" || ch == "BX"){
			data.push_back(0x27); return data;
		}
		else if (ch == "bp" || ch == "BP"){
			data.push_back(0x66); data.push_back(0x00);
			return data;
		}
		else if (ch == "si" || ch == "SI"){
			data.push_back(0x24); return data;
		}
		else if (ch == "di" || ch == "DI"){
			data.push_back(0x25); return data;
		}
		else {
			data.clear();
			cout << "����-028���������:" << str << endl; return data;
		}
	}
	cout << "����-029���������:" << str << endl; return data;
	return data;
}