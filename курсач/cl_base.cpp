#include "cl_base.h"

cl_base::cl_base(cl_base* pparent, string n)//���������� ������������
{
	this->parent = pparent; //������������� ���� parent
	this->name = n; //������������� ���� name
	if (pparent != nullptr)//���� �������� �������� ��������
	{
		pparent->children.push_back(this);// �� � ������ ����� ������������� ������� �������� ��������� �� ������� ������
	}
	this->ready_pointer = 0; //��������� ���������� ���������� �� ����(�� ��������� ������� �� ������)
}
cl_base::~cl_base()//���������� �����������
{
	// �������� ���� ����������� �������� �� ������
	for (int i = 0; i < this->children.size(); i++) {
		delete this->children[i];
	}
}
string cl_base::get_name()//���������� ������ ��������� ����� 
{
	return name;
}
void cl_base::set_name(string n)//���������� ������ ��������� ����� ��� �������� �������
{
	this->name = n;
}
cl_base* cl_base::get_parent()//���������� ��������� �������� ��� �������� �������
{
	return parent;
}
void cl_base::set_parent(cl_base* pparent)//���������� ������ ��������� ��������
{
	if (this->parent == nullptr)//��� ������� ��������� ��������� ��������� ������� � ������ �������� ��������
	{
		return; //���������� ������ �������
	}
	if (pparent == nullptr)//��� ������� ��������� ������ ��������� �������
	{
		return;
	}
	//���� ������� ����������� �������� �� �����������
	for (int i = 0; i < this->parent->children.size(); i++)//����� �� ���� ����������� ���������������� �������� �������
	{
		if (this->parent->children[i] == this)//���� ������� ������� ������
		{
			this->parent->children.erase(children.begin() + i); // �������� ��������� �� ������� ������ �� ���� children ��� �������-��������
			break;
		}
	}
	this->parent = pparent; //������������ ������ ��������
	this->parent->children.push_back(this); //���������� ��������� �� ������� ������ ������ ��������
}
void cl_base::get_tree()//���������� ������ ���������� ������ ��������
{
	if (this->parent != nullptr)//���� ������ �� ��������
	{
		this->tab_control = this->parent->tab_control + 1; //�� ����������� �������� ���� tab_control �������� ������� �������� ���� tab_control ��������� �������, ������������ �� ������� (����������� ���������� �������� ��� ������)
	}
	else//����� ������������� ���� ��� ��������� �������
	{
		this->tab_control = 0;
	}
	for (int i = 0; i < this->tab_control; i++)//����� � ���������
	{
		cout << "    ";
	}
	cout << this->get_name(); //����� ����� �������� �������
	for (int i = 0; i < children.size(); i++)//���� �� �������� �� ��� ����������� �������
	{
		cout << endl;
		this->children[i]->get_tree(); //����� � ������� ������������ ����� ������ ������ ��������
	}
}
int cl_base::get_children_size()//����� ��������� ���������� �����
{
	return this->children.size();
}
int cl_base::get_ready_pointer()//����� ��������� ���������� ���������� �������
{
	return this->ready_pointer;
}
void cl_base::set_ready_pointer(int pointer)//����� ��������� ���������� ���������� �������
{
	if (pointer != 0)
	{
		if (this->parent != nullptr)//���� ������� ������ �� �������� (��������� ���������� �� ��� ���������
		{
			if (this->parent->ready_pointer != 0)//���� � ������� ��������� ���������� �� ����� ����
			{
				this->ready_pointer = pointer;
				return;
			}
			else
			{
				return; //����� ���������� ������� ������������ ������
			}
		}
		else//���� ������ ��������
		{
			this->ready_pointer = pointer;
			return;
		}
	}
	else//���� ��������� ���������� ��������������� ���� ��� �������� �������, �� ��������� ��� ����������� �������
	{
		this->ready_pointer = 0;
		for (int i = 0; i < this->children.size(); i++)
		{
			this->children[i]->set_ready_pointer(0);
		}
	}
}
void cl_base::get_tree_with_ready()//���������� ������ ��� ���������� ������ ��������
{
	if (this->parent != nullptr)//���� ������ �� ��������
		this->tab_control = this->parent->tab_control + 1;//����������� ���������� �������� �� 1
	else
		this->tab_control = 0;
	for (int i = 0; i < this->tab_control; i++) {
		cout << "    ";
	}
	cout << this->get_name() << ' '; //����� ����� ������� �������
	//����� ���������� ���������� �������: ���� �� ����, �� ������ �����������, ����� - ���
	if (this->get_ready_pointer() != 0)
	{
		cout << "is ready";
	}
	else
	{
		cout << "is not ready";
	}
	for (int i = 0; i < this->children.size(); i++)//����� ����� �� ������ ��� ���� ����������� ��������
	{
		cout << endl;
		this->children[i]->get_tree_with_ready();
	}
}
cl_base* cl_base::find_obj_by_name(string name)//����� ������ �� ����� �������
{
	if (this->get_name() == name)//���� ��� �������� ������� ����� ����� ��������, �� ���������� ��������� �� ������� ������
	{
		return this;
	}
	else//����� �������� ����� �� ���� ��������, ������� � ����������� ��������� �������
	{
		for (int i = 0; i < this->children.size(); i++)
		{
			if (this->children[i]->get_name() == name)//���� ��� ������������ ������� ��������� ������� ���������, �� ���������� ��������� �� ������� ����������� ������
			{
				return children[i];
			}
			else//����� ���������� �������� ����� ��� ����������� �������� �������� ������������ �������
			{
				if (this->children[i]->children.size() != 0)
				{
					cl_base* cur_child = children[i]->find_obj_by_name(name);
					if (cur_child != nullptr)//���� ������� ����� ������ ����������� ��������, �� ���������� ��������� �� ����
					{
						return cur_child;
					}
				}
			}
		}
		return nullptr; //����� ���������� ������� ���������
	}
}

cl_base* cl_base::find_obj_by_path(string path)//���������� ������ ������ ������� �� ��� ����������
{
	cl_base* cur_obj = this; //���������� ��������� �� ������� ������
	cl_base* head_obj = this; //���������� ��������� �� �������� ������
	cl_base* result_obj; //���������� ��������� �� ������, ������� ��������� �����
	while (head_obj->get_parent() != nullptr)//������� ��������� �� �������� ������
	{
		head_obj = head_obj->get_parent();
	}
	if (path.substr(0, 2) == "//")
	{
		path.erase(0, 2);
		result_obj = head_obj->find_obj_by_name(path); //����� ������� �� �����
	}
	else if (path == ".") {
		result_obj = cur_obj; //�� ��������� - ������� ������
	}
	else if (path[0] == '/')
	{
		//����� � ��������� �������
		result_obj = head_obj;
		while (path != "")
		{
			path.erase(0, 1);
			if (path == "")//��� ������� ���� � ��������� �������
			{
				result_obj = head_obj;
				return result_obj;
			}
			int pos = path.find_first_of('/');
			int k = 0;
			if (pos > 0 && pos < path.size())//���� ��� �� ����� ����
			{
				for (int i = 0; i < result_obj->children.size(); i++)
				{
					if (result_obj->children[i]->get_name() == path.substr(0, pos))//���� ��� ������������ ������� ��������� � ������ � ����
					{
						result_obj = result_obj->children[i];
						k = 1;
						break;
					}
				}
			}
			else//����� ���� �������� ��������� ��� 
			{
				for (int i = 0; i < result_obj->children.size(); i++)
				{
					if (result_obj->children[i]->get_name() == path)//���� ��� ������������ ������� ������� ��������� � ������ � ����������
					{
						result_obj = result_obj->children[i];
						k = 1;
						path = "";
						break;
					}
				}
			}
			if (k == 0)//���� �� ���� ������� �� ��������� � ������ �� �������
			{
				result_obj = nullptr;
				break;
			}
			path.erase(0, pos);
		}
	}
	else//����� ���� ���� ���������� ����� � ����� �������(����� ������������ �������� ��������������)
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
					if (result_obj->children[i]->get_name() == path.substr(0, pos))//���� ��� ������������ ������� ��������� � ������ � ����
					{
						result_obj = result_obj->children[i];
						k = 1;
						break;
					}
				}
			}
			else//����� ���� �������� ��� ������ �������� �������
			{
				for (int i = 0; i < result_obj->children.size(); i++)
				{
					if (result_obj->children[i]->get_name() == path) //���� ��� �������� ������������ ������� ��������� � ������ � ����������
					{
						result_obj = result_obj->children[i];
						k = 1;
						path = "";
						break;
					}
				}
			}
			if (k == 0)//���� �� ���� ������� �� ��������� � ������ �� ��� ������
			{
				result_obj = nullptr;
				break;
			}
			path.erase(0, pos + 1);
		}
	}
	return result_obj;
}
string cl_base::get_path(string path)//���������� ������ ��������� ����������� ���� �������
{
	if (this->parent == nullptr)//���� ������� ������-��������
	{
		return '/' + path;
	}
	else if (this->parent->parent == nullptr)//����� ���� �������� ������ ��������-��������
	{
		return this->parent->get_path(this->name + path);//����������� ����� ������ � ���������� �������� �������� ���������
	}
	else
	{
		return this->parent->get_path('/' + this->name + path);//����������� ����� ������ � ���������� �������� �������� ���������
	}
}
void cl_base::set_ready_for_all_objects(int ready_pointer)//���������� ������ ��������� � ��������� ���������� ���� �������
{
	this->ready_pointer = ready_pointer;//�������� ���� ready_pointer �������� ������� ������������� �������� ���������
	for (int i = 0; i < this->children.size(); i++)//���� �� �������� ��� ���������� �������
	{
		this->children[i]->set_ready_for_all_objects(ready_pointer); //����������� ����� ������
	}
}
void cl_base::set_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler)//���������� ������ ��������� ����� ����� ���� ������-����������
{
	for (int i = 0; i < connections_of_obj.size(); i++)//����� ���� ������ ���� ������ ���������� �������� �������
	{
		//��� ������� ���������� �����, ������� ��� ����������� �����
		if ((connections_of_obj[i]->signal == signal) && (connections_of_obj[i]->h_obj == pobj) && (connections_of_obj[i]->handler == handler))
		{
			return; //����� �� ������
		}
	}
	//����� ������� ����� ����� � ��������� �� �������� �������
	connections* new_connect = new connections;
	new_connect->signal = signal;
	new_connect->h_obj = pobj;
	new_connect->handler = handler;
	this->connections_of_obj.push_back(new_connect);
}
void cl_base::del_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler)//���������� ������ �������� ����� ���� ������-����������
{
	for (int i = 0; i < this->connections_of_obj.size(); i++)//����� ���� ������ ���� ������-���������� �������� �������
	{
		//��� ���������� �����, ������� ���� �������
		if ((connections_of_obj[i]->signal == signal) && (connections_of_obj[i]->h_obj == pobj) && (connections_of_obj[i]->handler == handler))
		{
			this->connections_of_obj.erase(this->connections_of_obj.begin() + i);//�������� ������� �����
			return; //����� �� ������
		}
	}
}
void cl_base::emit_signal(TYPE_SIGNAL signal, string& message)//���������� ������ �������� �������
{
	if (this->ready_pointer == 0)//���� ���������� ���������� �������� ������� ����� 0, �� ������ �� ����������
	{
		return; //����� �� ������
	}
	(this->*signal)(message);//����� ������ ������� ��� �������� �������(��� ��� signal - ��������� �� �����, �� �� ������� ����������������)
	if (this->connections_of_obj.empty()) //���� � �������� ������� ��� ������ ���� ������-����������
	{
		return; //����� �� ������
	}
	for (int i = 0; i < this->connections_of_obj.size(); i++)//����� ���� ������ ���� ������-���������� �������� �������
	{
		//���� ����� ������� ������� ����� ��������� � ������� ������� �������� ������� � ��������� ���������� �������� ������� �� ����� 0
		if ((this->connections_of_obj[i]->signal == signal) && (this->connections_of_obj[i]->h_obj->ready_pointer != 0))
		{
			//����� ������ ����������� �������� �������(hadler - ��������� �� �����, ������� ���� ���������� ���������������)
			((this->connections_of_obj[i]->h_obj)->*(connections_of_obj[i]->handler))(message);
		}
	}
}
int cl_base::get_numb_of_class()//���������� ������ ��������� ������ ������
{
	return numb_of_class;
}