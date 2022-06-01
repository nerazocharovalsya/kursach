#include "cl_1.h"
#include "cl_application.h"

cl_1::cl_1(cl_base* pparent, string name) :cl_base(pparent, name)//�����������
{
	numb_of_class = 2; //���������� ���� ������ �������� ������
}
void cl_1::signal_proc_count(string& message)//���������� ������ ������� �������, ������������� �������������� ��������
{
	int n;
	n = message.find_last_of(' ');
	if (n != 0)
		message = message.substr(n - 1);//��������� ��������� �������� � ������� ���������
}
void cl_1::signal_proc_sdvig(string& message)//���������� ������ ������� �������, ������������� ��������� �����
{
	int n;
	n = message.find_last_of(' ');
	if (n != 0)
		message = message.substr(n - 1);//��������� ��������� �������� � ������� ���������
}
void cl_1::signal_proc_c(string& message)//���������� ������ ������� �������, ������������� ����� ������������
{
	//��������� �� ����������
}
void cl_1::handler_proc(string message)//���������� ������ ����������� �������
{
	string op, command;
	if (message == " ")
	{
		cin >> command;
		((cl_application*)this->get_parent())->set_result(stoi(command));
		((cl_application*)this->get_parent())->set_primer(command + " ");
		message = command + " ";
	}
	cin >> command; //���� �������
	while (command[0] >= '0' && command[0] <= '9')//���� �������� �����, �� ��������
	{
		if ((message.find_first_of(' ')) == (message.find_last_of(' ')))//���� �� ���� �������, �� ������ ������ �������� ����������
		{
			((cl_application*)this->get_parent())->set_result(stoi(command));
			((cl_application*)this->get_parent())->set_primer(command + " ");
			message = command + " ";
		}
		else //����� ������� �������� ������ �������� ���������� ������������
		{
			cin.clear();
			cin.ignore();
		}
		cin >> command;//����, ���� �� ����� ������� ����������� �������
	}
	if (command == "Off")//������� ������� ���������� ������������
		((cl_application*)this->get_parent())->set_primer("Off");
	else if (command == "C")//������� ������ ������������
		((cl_application*)this->get_parent())->set_primer("C");
	else if (command == "SHOWTREE")//������� ������ ������
		((cl_application*)this->get_parent())->set_primer("SHOWTREE");
	else//��������� �������
	{
		cin >> op;
		command += " " + op;
		((cl_application*)this->get_parent())->set_primer(message + command);
	}
}