#ifndef _CL_2_H_
#define _CL_2_H_

#include "cl_base.h"

class cl_2 : public cl_base
{
public:
	cl_2(cl_base* pparent, string name = ""); //������������������� �����������
	void signal_proc(string& message); //����� ������� �������
	void handler_proc(string message); //����� ����������� �������
};

#endif