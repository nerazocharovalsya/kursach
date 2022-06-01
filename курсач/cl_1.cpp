#include "cl_1.h"
#include "cl_application.h"

cl_1::cl_1(cl_base* pparent, string name) :cl_base(pparent, name)//конструктор
{
	numb_of_class = 2; //присвоение полю номера текущего класса
}
void cl_1::signal_proc_count(string& message)//реализация метода сигнала объекта, производящего арифметическую операцию
{
	int n;
	n = message.find_last_of(' ');
	if (n != 0)
		message = message.substr(n - 1);//получение последней операции и второго аргумента
}
void cl_1::signal_proc_sdvig(string& message)//реализация метода сигнала объекта, производящего побитовый сдвиг
{
	int n;
	n = message.find_last_of(' ');
	if (n != 0)
		message = message.substr(n - 1);//получение последней операции и второго аргумента
}
void cl_1::signal_proc_c(string& message)//реализация метода сигнала объекта, производящего сброс калькулятора
{
	//изменений не происходит
}
void cl_1::handler_proc(string message)//реализация метода обработчика объекта
{
	string op, command;
	if (message == " ")
	{
		cin >> command;
		((cl_application*)this->get_parent())->set_result(stoi(command));
		((cl_application*)this->get_parent())->set_primer(command + " ");
		message = command + " ";
	}
	cin >> command; //ввод команды
	while (command[0] >= '0' && command[0] <= '9')//если вводится число, не операция
	{
		if ((message.find_first_of(' ')) == (message.find_last_of(' ')))//если не было команды, то меняем первый аргумент вычислений
		{
			((cl_application*)this->get_parent())->set_result(stoi(command));
			((cl_application*)this->get_parent())->set_primer(command + " ");
			message = command + " ";
		}
		else //иначе попытка поменять первый аргумент вычислений игнорируется
		{
			cin.clear();
			cin.ignore();
		}
		cin >> command;//ввод, пока не будет введена полноценная команда
	}
	if (command == "Off")//введена команда отключения калькулятора
		((cl_application*)this->get_parent())->set_primer("Off");
	else if (command == "C")//команда сброса калькулятора
		((cl_application*)this->get_parent())->set_primer("C");
	else if (command == "SHOWTREE")//команда вывода дерева
		((cl_application*)this->get_parent())->set_primer("SHOWTREE");
	else//остальные команды
	{
		cin >> op;
		command += " " + op;
		((cl_application*)this->get_parent())->set_primer(message + command);
	}
}