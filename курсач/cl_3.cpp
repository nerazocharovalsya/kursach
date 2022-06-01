#include "cl_3.h"
#include "cl_application.h"

cl_3::cl_3(cl_base* pparent, string name) :cl_base(pparent, name)
{
	numb_of_class = 4; //присвоение полю номера текущего класса
}
void cl_3::signal_proc(string& message)//реализация метода сигнала объекта
{
	message = to_string(((cl_application*)this->get_parent())->get_result());
}
void cl_3::handler_proc(string message)//реализация метода обработчика объекта
{
	int prev = ((cl_application*)this->get_parent())->get_result();//результат предыдущих вычислений
	char op = message[0];
	message = message.substr(2);//второй аргумент вычислений
	if (op == '<')
		((cl_application*)this->get_parent())->set_result(prev * pow(2, stoi(message)));
	else if (op == '>')
		((cl_application*)this->get_parent())->set_result(prev / pow(2, stoi(message)));
}