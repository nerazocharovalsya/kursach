#ifndef _CL_5_H_
#define _CL_5_H_

#include "cl_base.h"

class cl_5 : public cl_base
{
public:
	cl_5(cl_base* pparent, string name = ""); //������������������� �����������
	void signal_proc(string& message); //����� ������� �������
	void handler_proc(string message); //����� ����������� �������
};

#endif