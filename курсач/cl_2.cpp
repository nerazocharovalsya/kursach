#include "cl_2.h"
#include "cl_application.h"

cl_2::cl_2(cl_base* pparent, string name) :cl_base(pparent, name)
{
	numb_of_class = 3; //���������� ���� ������ �������� ������
}
void cl_2::signal_proc(string& message)//���������� ������ ������� �������
{
	if ((message != "Overflow") && (message != "Division by zero"))//���� �� ���� ������
		message = to_string(((cl_application*)this->get_parent())->get_result());//�������� ��������� ��������� ����������
	//����� �������� ������ � �������
}
void cl_2::handler_proc(string message)//���������� ������ ����������� �������
{
	int last = ((cl_application*)this->get_parent())->get_result();//��������� �������� ����������
	char op = message[0];//�������������� ��������
	message = message.substr(2);//������ ��������
	switch (op)
	{
	case '+'://��������
		((cl_application*)this->get_parent())->set_result(last + stoi(message));
	case '-'://���������
		((cl_application*)this->get_parent())->set_result(last + stoi(message));
	case '*'://���������
		((cl_application*)this->get_parent())->set_result(last * stoi(message));
	case '/'://�������
		if (message == "0")//������� �� ����
			((cl_application*)this->get_parent())->set_primer("Division by zero");
		else
			((cl_application*)this->get_parent())->set_result(last / stoi(message));
	case '%'://������� �� �������
		if (message == "0")//������� �� ����
			((cl_application*)this->get_parent())->set_primer("Division by zero");
		else
			((cl_application*)this->get_parent())->set_result(last % stoi(message));
	}
	if (((cl_application*)this->get_parent())->get_result() < -32768 || ((cl_application*)this->get_parent())->get_result() > 32767)//������������
		((cl_application*)this->get_parent())->set_primer("Overflow");
}