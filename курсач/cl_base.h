#ifndef _CL_BASE_H_
#define _CL_BASE_H_

#define TOSIGNAL(signal_f) (TYPE_SIGNAL) (&signal_f) //получение указателя на метод сигнала класса
#define TOHANDLER(handler_f) (TYPE_HANDLER) (&handler_f) //получение указателя на метод обработчика сигнала класса

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class cl_base {
public:
	typedef void (cl_base::* TYPE_SIGNAL) (string&); //указатель на метод сигнала объекта
	typedef void (cl_base::* TYPE_HANDLER) (string); //указатель на метод обработчика объекта
	cl_base(cl_base* pparent, string name = ""); //параметризированный конструктор
	string get_name(); //метод получения имени объекта
	void set_name(string n); //метод изменения имени объекта
	cl_base* get_parent(); //метод получения указателя на объект родитель
	void set_parent(cl_base* pparent); //метод установки нового объекта-родителя
	void get_tree(); //метод построения дерева иерархии
	int get_children_size(); //метод получения количества подчиненных объектов для данного объекта
	~cl_base(); //деструктор
	cl_base* find_obj_by_name(string name); //метод поиска объекта по имени
	void get_tree_with_ready(); //метод для вывода дерева иерархии объектов с их индикаторами готовности
	int get_ready_pointer(); //метод получения значения индикатора готовности
	void set_ready_pointer(int pointer); //метод установки нового значения индикатора готовности
	cl_base* find_obj_by_path(string path); //метод нахождения объекта по его пути
	string get_path(string path = "");//метод получения абсолютного пути объекта
	void set_ready_for_all_objects(int ready_pointer);//метод установки в состояние готовности всех объекта
	void set_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler);//метод установки новой связи типа сигнал-обработчик
	void del_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler);//метод удаления связи типа сигнал-обработчик
	void emit_signal(TYPE_SIGNAL signal, string& message);//метод передачи сигнала
	int get_numb_of_class();//метод получения номера класса
private:
	string name; //поле, отвечающее за имя объекта
	cl_base* parent; //поле, отвечающее за указатель на объект родитель
	vector <cl_base*> children; //поле, отвечающее за массив детей
	int ready_pointer;//поле, отвечающее за индикатор готовности
	int tab_control;//поле, отвечающее за контроль табуляции при выводе дерева объектов
	struct connections//структура одной связи типа сигнал-обработчик
	{
		TYPE_SIGNAL signal; //ссылка на метод сигнала объекта
		cl_base* h_obj; //указатель на целевой объект, обрабатывающий сигнал
		TYPE_HANDLER handler; //метод обработчика сигнала целевого объекта
	};
	vector <connections*> connections_of_obj; //вектор, хранящий множество связей типа сигнал-обработчик
protected:
	int numb_of_class; //номер класса текущего объекта
};

#endif