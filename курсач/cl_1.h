#ifndef _CL_1_H_
#define _CL_1_H_

#include "cl_base.h"

class cl_1 : public cl_base
{
public:
	cl_1(cl_base* pparent, string name = ""); //������������������� �����������
	void signal_proc_count(string& message); //����� ������� �������
	void signal_proc_sdvig(string& message); //����� ������� �������
	void signal_proc_c(string& message); //����� ������� �������
	void handler_proc(string message); //����� ����������� �������
};

#endif