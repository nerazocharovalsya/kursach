#ifndef _CL_3_H_
#define _CL_3_H_

#include "cl_base.h"

class cl_3 : public cl_base
{
public:
	cl_3(cl_base* pparent, string name = ""); //параметризированный конструктор
	void signal_proc(string& message); //метод сигнала объекта
	void handler_proc(string message); //метод обработчика объекта
};

#endif