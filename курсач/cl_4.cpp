#include "cl_4.h"
#include "cl_application.h"

cl_4::cl_4(cl_base* pparent, string name) :cl_base(pparent, name)
{
	numb_of_class = 5; //присвоение полю номера текущего класса
}
void cl_4::signal_proc(string& message) {}//реализация метода сигнала объекта
void cl_4::handler_proc(string message)//реализация метода обработчика объекта
{
	//возвращение в исходное состояние
	((cl_application*)this->get_parent())->set_primer("0");//обнуление вычислений
	((cl_application*)this->get_parent())->set_result(0);//обнуление примера
}