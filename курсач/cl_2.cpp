#include "cl_2.h"
#include "cl_application.h"

cl_2::cl_2(cl_base* pparent, string name) :cl_base(pparent, name)
{
	numb_of_class = 3; //присвоение полю номера текущего класса
}
void cl_2::signal_proc(string& message)//реализация метода сигнала объекта
{
	if ((message != "Overflow") && (message != "Division by zero"))//если не было ошибки
		message = to_string(((cl_application*)this->get_parent())->get_result());//передаем результат последних вычислений
	//иначе передаем сигнал с ошибкой
}
void cl_2::handler_proc(string message)//реализация метода обработчика объекта
{
	int last = ((cl_application*)this->get_parent())->get_result();//последнее значение вычислений
	char op = message[0];//арифметическая операция
	message = message.substr(2);//второй аргумент
	switch (op)
	{
	case '+'://сложение
		((cl_application*)this->get_parent())->set_result(last + stoi(message));
	case '-'://вычитание
		((cl_application*)this->get_parent())->set_result(last + stoi(message));
	case '*'://умножение
		((cl_application*)this->get_parent())->set_result(last * stoi(message));
	case '/'://деление
		if (message == "0")//деление на ноль
			((cl_application*)this->get_parent())->set_primer("Division by zero");
		else
			((cl_application*)this->get_parent())->set_result(last / stoi(message));
	case '%'://остаток от деления
		if (message == "0")//деление на ноль
			((cl_application*)this->get_parent())->set_primer("Division by zero");
		else
			((cl_application*)this->get_parent())->set_result(last % stoi(message));
	}
	if (((cl_application*)this->get_parent())->get_result() < -32768 || ((cl_application*)this->get_parent())->get_result() > 32767)//переполнение
		((cl_application*)this->get_parent())->set_primer("Overflow");
}