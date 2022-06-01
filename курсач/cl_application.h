#ifndef _CL_APPLICATION_H_
#define _CL_APPLICATION_H_

#include "cl_base.h"

class cl_application : public cl_base
{
private:
	string primer;
	int result;

public:
	cl_application(cl_base* pparent, string name = ""); //параметризированный конструктор
	void build_tree_object(); //метод дл€ построени€ дерева иерархии
	int exec_app(); //метод дл€ вывода дерева иерархии на экран
	void signal_proc(string& message); //метод сигнала текущего объекта
	void handler_proc(string& message);//метод обработчика текущего объекта
	int get_result();//метод получени€ текущего результата вычислений
	void set_result(int result);//метод установки текущего результата вычислений
	string get_primer();//метод получени€ текущего выражени€
	void set_primer(string primer);//метод установки текущего выражени€
};

#endif