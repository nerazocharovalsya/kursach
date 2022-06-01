#ifndef _CL_APPLICATION_H_
#define _CL_APPLICATION_H_

#include "cl_base.h"

class cl_application : public cl_base
{
private:
	string primer;
	int result;

public:
	cl_application(cl_base* pparent, string name = ""); //������������������� �����������
	void build_tree_object(); //����� ��� ���������� ������ ��������
	int exec_app(); //����� ��� ������ ������ �������� �� �����
	void signal_proc(string& message); //����� ������� �������� �������
	void handler_proc(string& message);//����� ����������� �������� �������
	int get_result();//����� ��������� �������� ���������� ����������
	void set_result(int result);//����� ��������� �������� ���������� ����������
	string get_primer();//����� ��������� �������� ���������
	void set_primer(string primer);//����� ��������� �������� ���������
};

#endif