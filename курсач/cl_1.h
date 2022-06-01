#ifndef _CL_1_H_
#define _CL_1_H_

#include "cl_base.h"

class cl_1 : public cl_base
{
public:
	cl_1(cl_base* pparent, string name = ""); //параметризированный конструктор
	void signal_proc_count(string& message); //метод сигнала объекта
	void signal_proc_sdvig(string& message); //метод сигнала объекта
	void signal_proc_c(string& message); //метод сигнала объекта
	void handler_proc(string message); //метод обработчика объекта
};

#endif