#include "cl_4.h"
#include "cl_application.h"

cl_4::cl_4(cl_base* pparent, string name) :cl_base(pparent, name)
{
	numb_of_class = 5; //���������� ���� ������ �������� ������
}
void cl_4::signal_proc(string& message) {}//���������� ������ ������� �������
void cl_4::handler_proc(string message)//���������� ������ ����������� �������
{
	//����������� � �������� ���������
	((cl_application*)this->get_parent())->set_primer("0");//��������� ����������
	((cl_application*)this->get_parent())->set_result(0);//��������� �������
}