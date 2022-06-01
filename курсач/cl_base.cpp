#include "cl_base.h"

cl_base::cl_base(cl_base* pparent, string n)//реализация конструктора
{
	this->parent = pparent; //инициализация поля parent
	this->name = n; //инициализация поля name
	if (pparent != nullptr)//если объектне является корневым
	{
		pparent->children.push_back(this);// то в массив детей родительского объекта добавить указатель на текущий объект
	}
	this->ready_pointer = 0; //установка индикатора готовности на ноль(по умолчанию объекты не готовы)
}
cl_base::~cl_base()//реализация деструктора
{
	// удаление всех подчиненных объектов по одному
	for (int i = 0; i < this->children.size(); i++) {
		delete this->children[i];
	}
}
string cl_base::get_name()//реализация метода получения имени 
{
	return name;
}
void cl_base::set_name(string n)//реализация метода изменения имени для текущего объекта
{
	this->name = n;
}
cl_base* cl_base::get_parent()//реализация получения родителя для текущего объекта
{
	return parent;
}
void cl_base::set_parent(cl_base* pparent)//реализация метода установки родителя
{
	if (this->parent == nullptr)//при попытке изменения положения корневого объекта в дереве иерархии объектов
	{
		return; //завершение работы функции
	}
	if (pparent == nullptr)//при попытке установки нового корневого объекта
	{
		return;
	}
	//если никаких запрещенных действий не выполняется
	for (int i = 0; i < this->parent->children.size(); i++)//обход по всем подчиненным объектамродителя текущего объекта
	{
		if (this->parent->children[i] == this)//если текущий элемент найден
		{
			this->parent->children.erase(children.begin() + i); // удаление указателя на текущий объект из поля children для объекта-родителя
			break;
		}
	}
	this->parent = pparent; //установление нового родителя
	this->parent->children.push_back(this); //добавление указателя на текущий объект новому родителю
}
void cl_base::get_tree()//реализация метода построения дерева иерархии
{
	if (this->parent != nullptr)//если объект не корневой
	{
		this->tab_control = this->parent->tab_control + 1; //то присваиваем значению поля tab_control текущего объекта значение поля tab_control головного объекта, увеличенного на единицу (увеличиваем количество отступов при выводе)
	}
	else//иначе устанавливаем ноль для корневого объекта
	{
		this->tab_control = 0;
	}
	for (int i = 0; i < this->tab_control; i++)//вывод с отступами
	{
		cout << "    ";
	}
	cout << this->get_name(); //вывод имени текущего объекта
	for (int i = 0; i < children.size(); i++)//пока не выведены не все подчиненные объекты
	{
		cout << endl;
		this->children[i]->get_tree(); //вызов к каждому подчиненному метод вывода дерева иерархии
	}
}
int cl_base::get_children_size()//метод получения количества детей
{
	return this->children.size();
}
int cl_base::get_ready_pointer()//метод получения индикатора готовности объекта
{
	return this->ready_pointer;
}
void cl_base::set_ready_pointer(int pointer)//метод установка индикатора готовности объекта
{
	if (pointer != 0)
	{
		if (this->parent != nullptr)//если текущий объект не корневой (установка индикатора не для корневого
		{
			if (this->parent->ready_pointer != 0)//если у объекта индикатор готовности не равен нулю
			{
				this->ready_pointer = pointer;
				return;
			}
			else
			{
				return; //иначе игнорируем попытку активировать объект
			}
		}
		else//если объект корневой
		{
			this->ready_pointer = pointer;
			return;
		}
	}
	else//если индикатор готовности устанавливается ноль для текущего объекта, то отключаем все подчиненные объекты
	{
		this->ready_pointer = 0;
		for (int i = 0; i < this->children.size(); i++)
		{
			this->children[i]->set_ready_pointer(0);
		}
	}
}
void cl_base::get_tree_with_ready()//реализация метода для построения дерева иерархии
{
	if (this->parent != nullptr)//если объект не корневой
		this->tab_control = this->parent->tab_control + 1;//увеличиваем количество отступов на 1
	else
		this->tab_control = 0;
	for (int i = 0; i < this->tab_control; i++) {
		cout << "    ";
	}
	cout << this->get_name() << ' '; //вывод имени теущего объекта
	//вывод индикатора готовности объекта: если не ноль, то объект активирован, иначе - нет
	if (this->get_ready_pointer() != 0)
	{
		cout << "is ready";
	}
	else
	{
		cout << "is not ready";
	}
	for (int i = 0; i < this->children.size(); i++)//вызов этого же метода для всех подчиненных объектов
	{
		cout << endl;
		this->children[i]->get_tree_with_ready();
	}
}
cl_base* cl_base::find_obj_by_name(string name)//метод поиска по имени объекта
{
	if (this->get_name() == name)//если имя текущего объекта равно имени искомого, то возвращаем указатель на текущий объект
	{
		return this;
	}
	else//иначе начинаем поиск по всем объектам, начиная с подчиненных головному объекту
	{
		for (int i = 0; i < this->children.size(); i++)
		{
			if (this->children[i]->get_name() == name)//если имя подчиненного объекта головного объекта совпадает, то возвращаем указатель на текущий подчиненный объект
			{
				return children[i];
			}
			else//иначе рекурсивно вызываем метод для подчиненных объектов текущему подчиненному объекту
			{
				if (this->children[i]->children.size() != 0)
				{
					cl_base* cur_child = children[i]->find_obj_by_name(name);
					if (cur_child != nullptr)//если находим среди других подчиненных объектов, то возвращаем указатель на него
					{
						return cur_child;
					}
				}
			}
		}
		return nullptr; //иначе возвращаем нулевой указатель
	}
}

cl_base* cl_base::find_obj_by_path(string path)//реализация метода поиска объекта по его координате
{
	cl_base* cur_obj = this; //переменная указатель на текущий объект
	cl_base* head_obj = this; //переменная указатель на корневой объект
	cl_base* result_obj; //переменная указатель на объект, который требуется найти
	while (head_obj->get_parent() != nullptr)//находим указатель на корневой объект
	{
		head_obj = head_obj->get_parent();
	}
	if (path.substr(0, 2) == "//")
	{
		path.erase(0, 2);
		result_obj = head_obj->find_obj_by_name(path); //поиск объекта по имени
	}
	else if (path == ".") {
		result_obj = cur_obj; //то результат - текущий объект
	}
	else if (path[0] == '/')
	{
		//поиск с корневого объекта
		result_obj = head_obj;
		while (path != "")
		{
			path.erase(0, 1);
			if (path == "")//был передан путь к корневому объекту
			{
				result_obj = head_obj;
				return result_obj;
			}
			int pos = path.find_first_of('/');
			int k = 0;
			if (pos > 0 && pos < path.size())//если еще не конец пути
			{
				for (int i = 0; i < result_obj->children.size(); i++)
				{
					if (result_obj->children[i]->get_name() == path.substr(0, pos))//если имя подчиненного объекта совпадает с именем в пути
					{
						result_obj = result_obj->children[i];
						k = 1;
						break;
					}
				}
			}
			else//иначе если осталось последнее имя 
			{
				for (int i = 0; i < result_obj->children.size(); i++)
				{
					if (result_obj->children[i]->get_name() == path)//если имя подчиненного объекта объекта совпадает с именем в координате
					{
						result_obj = result_obj->children[i];
						k = 1;
						path = "";
						break;
					}
				}
			}
			if (k == 0)//если ни одно условие не сработало и ничего не найдено
			{
				result_obj = nullptr;
				break;
			}
			path.erase(0, pos);
		}
	}
	else//иначе если путь начинается сразу с имени объекта(поиск относительно текущего установленного)
	{
		result_obj = cur_obj;
		while (path != "")
		{
			int pos = path.find_first_of('/');
			int k = 0;
			if (pos > 0 && pos < path.size())
			{
				for (int i = 0; i < result_obj->children.size(); i++)
				{
					if (result_obj->children[i]->get_name() == path.substr(0, pos))//если имя подчиненного объекта совпадает с именем в пути
					{
						result_obj = result_obj->children[i];
						k = 1;
						break;
					}
				}
			}
			else//иначе если осталось имя самого искомого объекта
			{
				for (int i = 0; i < result_obj->children.size(); i++)
				{
					if (result_obj->children[i]->get_name() == path) //если имя текущего подчиненного объекта совпадает с именем в координате
					{
						result_obj = result_obj->children[i];
						k = 1;
						path = "";
						break;
					}
				}
			}
			if (k == 0)//если ни одно условие не сработало и объект не был найден
			{
				result_obj = nullptr;
				break;
			}
			path.erase(0, pos + 1);
		}
	}
	return result_obj;
}
string cl_base::get_path(string path)//реализация метода получения абсолютного пути объекта
{
	if (this->parent == nullptr)//если текущий объект-корневой
	{
		return '/' + path;
	}
	else if (this->parent->parent == nullptr)//иначе если головной объект текущего-корневой
	{
		return this->parent->get_path(this->name + path);//рекурсивный вызов метода с изменением текущего значения параметра
	}
	else
	{
		return this->parent->get_path('/' + this->name + path);//рекурсивный вызов метода с изменением текущего значения параметра
	}
}
void cl_base::set_ready_for_all_objects(int ready_pointer)//реализация метода установки в состояние готовности всех объекта
{
	this->ready_pointer = ready_pointer;//значение полю ready_pointer текущего объекта устанавливаем значение параметра
	for (int i = 0; i < this->children.size(); i++)//пока не пройдены все подиченные объекты
	{
		this->children[i]->set_ready_for_all_objects(ready_pointer); //рекурсивный вызов метода
	}
}
void cl_base::set_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler)//реализация метода установки новой связи типа сигнал-обработчик
{
	for (int i = 0; i < connections_of_obj.size(); i++)//обход всех связей типа сигнал обработчик текущего объекта
	{
		//при попытке установить связь, которая уже установлена ранее
		if ((connections_of_obj[i]->signal == signal) && (connections_of_obj[i]->h_obj == pobj) && (connections_of_obj[i]->handler == handler))
		{
			return; //выход из метода
		}
	}
	//иначе создаем новую связь и добавляем ее текущему объекту
	connections* new_connect = new connections;
	new_connect->signal = signal;
	new_connect->h_obj = pobj;
	new_connect->handler = handler;
	this->connections_of_obj.push_back(new_connect);
}
void cl_base::del_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler)//реализация метода удаления связи типа сигнал-обработчик
{
	for (int i = 0; i < this->connections_of_obj.size(); i++)//обход всех связей типа сигнал-обработчик текущего объекта
	{
		//при нахождении связи, которую надо удалить
		if ((connections_of_obj[i]->signal == signal) && (connections_of_obj[i]->h_obj == pobj) && (connections_of_obj[i]->handler == handler))
		{
			this->connections_of_obj.erase(this->connections_of_obj.begin() + i);//удаление искомой связи
			return; //выход из метода
		}
	}
}
void cl_base::emit_signal(TYPE_SIGNAL signal, string& message)//реализация метода передачи сигнала
{
	if (this->ready_pointer == 0)//если индикатора готовности текущего объекта равен 0, то сигнал не передается
	{
		return; //выход из метода
	}
	(this->*signal)(message);//вызов метода сигнала для текущего объекта(так как signal - указатель на метод, то он сначала разыменовывается)
	if (this->connections_of_obj.empty()) //если у текущего объекта нет связей типа сигнал-обработчик
	{
		return; //выход из метода
	}
	for (int i = 0; i < this->connections_of_obj.size(); i++)//обход всех связей типа сигнал-обработчик текущего объекта
	{
		//если метод сигнала текущей связи совпадает с методом сигнала текущего объекта и индикатор готовности целевого объекта не равен 0
		if ((this->connections_of_obj[i]->signal == signal) && (this->connections_of_obj[i]->h_obj->ready_pointer != 0))
		{
			//вызов метода обработчика целевого объекта(hadler - указатель на метод, поэтому тоже необходимо разыменовывание)
			((this->connections_of_obj[i]->h_obj)->*(connections_of_obj[i]->handler))(message);
		}
	}
}
int cl_base::get_numb_of_class()//реализация метода получения номера класса
{
	return numb_of_class;
}