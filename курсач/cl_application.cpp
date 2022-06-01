#include "cl_application.h"
#include "cl_1.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"

cl_application::cl_application(cl_base* pparent, string name) :cl_base(pparent, name)
{
	numb_of_class = 1;
}
int cl_application::get_result()//реализация метода получения текущего результата вычислений
{
	return result;
}
void cl_application::set_result(int result)//реализация метода устаноки нового текущего результата вычислений
{
	this->result = result;
}
string cl_application::get_primer()//реализация метода получения текущего выражения
{
	return this->primer;
}
void cl_application::set_primer(string primer)//реализация метода установки текущего выражения
{
	this->primer = primer;
}
void cl_application::signal_proc(string& message)//реализация метода сигнала
{
	message += " ";
}
void cl_application::handler_proc(string& message) {}//реализация метода обработчика
int cl_application::exec_app() //метод вывода дерева иерархии на экран
{
	this->set_ready_for_all_objects(1);//включение всех объектов
	this->set_primer("");
	string primer = "";//текущий пример и команда
	cl_base* cur_obj;//указатель на объект, передающий сигнал
	int k = 0;//контроль перехода на новую строку
	while (this->get_primer() != "Off")
	{
		this->emit_signal(TOSIGNAL(cl_application::signal_proc), primer);//выдача сигнала на чтение команды
		primer = this->get_primer();
		if (primer == "C")
		{
			cur_obj = this->find_obj_by_name("reader");
			cur_obj->emit_signal(TOSIGNAL(cl_1::signal_proc_c), primer);//передача сигнала объекту-обработчику этой команды
		}
		else if (primer == "SHOWTREE")
		{
			cout << "Object tree with their readiness:" << endl;
			this->get_tree_with_ready();
			exit(0);
		}
		else if (primer != "Off")//арифметическая операция или сдвиг
		{
			if (k != 0) {//первая строка без переноса строки
				cout << endl;
			}
			cout << this->get_primer();//вывод текущего примера
			k = 1;
			cur_obj = this->find_obj_by_name("reader");
			//команда побитового сдвига
			if ((primer[primer.find_last_of(' ') - 1] == '<') || (primer[primer.find_last_of(' ') - 1] == '>'))
			{
				cur_obj->emit_signal(TOSIGNAL(cl_1::signal_proc_sdvig), primer);//передача команды объекту, выполняющему побитовый сдвиг
				cur_obj = this->find_obj_by_name("sdvig");
				cur_obj->emit_signal(TOSIGNAL(cl_3::signal_proc), primer);//выдача сигнала объекту для вывода результата на экран
			}
			//арифметическая операция
			else
			{
				cur_obj->emit_signal(TOSIGNAL(cl_1::signal_proc_count), primer);//передача команды объекту, выполняющему арифметическую операцию
				cur_obj = this->find_obj_by_name("count");
				primer = this->get_primer();
				cur_obj->emit_signal(TOSIGNAL(cl_2::signal_proc), primer);//выдача сигнала объекту для вывода результата на экран
			}
		}
		primer = this->get_primer();
	}
	return 0;
}
void cl_application::build_tree_object() //метод построения иерархии объектов
{
	this->set_name("system");//установка имени корневого объекта
	cl_base* reader = new cl_1(this, "reader");//объект, считывающий пользовательские команды
	cl_base* count = new cl_2(this, "count");//объект, производящий арифметическую операцию
	cl_base* sdvig = new cl_3(this, "sdvig");//объект, выполняющий операцию побитового сдвига
	cl_base* c = new cl_4(this, "c");//объект, обрабатывающий сброс калькулятора в исходное состояние
	cl_base* print = new cl_5(this, "print");//объект, выводящий результат вычислений на экран
	//установка связей типа сигнал(объект,подающий сигнал)->обработчик(объект,обрабатывающий сигнал)
	//система->считывать команд
	this->set_connect(TOSIGNAL(cl_application::signal_proc), reader, TOHANDLER(cl_1::handler_proc));
	//считыватель команд->арифметические действия
	reader->set_connect(TOSIGNAL(cl_1::signal_proc_count), count, TOHANDLER(cl_2::handler_proc));
	//считыватель команд->побитовый сдвиг
	reader->set_connect(TOSIGNAL(cl_1::signal_proc_sdvig), sdvig, TOHANDLER(cl_3::handler_proc));
	//считыватель команд->сброс калькулятора в исходное состояние
	reader->set_connect(TOSIGNAL(cl_1::signal_proc_c), c, TOHANDLER(cl_4::handler_proc));
	//арифметичские действия->вывод на экран
	count->set_connect(TOSIGNAL(cl_2::signal_proc), print, TOHANDLER(cl_5::handler_proc));
	//побитовый сдвиг->вывод
	sdvig->set_connect(TOSIGNAL(cl_3::signal_proc), print, TOHANDLER(cl_5::handler_proc));
}