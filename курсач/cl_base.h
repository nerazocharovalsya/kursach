#ifndef _CL_BASE_H_
#define _CL_BASE_H_

#define TOSIGNAL(signal_f) (TYPE_SIGNAL) (&signal_f) //��������� ��������� �� ����� ������� ������
#define TOHANDLER(handler_f) (TYPE_HANDLER) (&handler_f) //��������� ��������� �� ����� ����������� ������� ������

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class cl_base {
public:
	typedef void (cl_base::* TYPE_SIGNAL) (string&); //��������� �� ����� ������� �������
	typedef void (cl_base::* TYPE_HANDLER) (string); //��������� �� ����� ����������� �������
	cl_base(cl_base* pparent, string name = ""); //������������������� �����������
	string get_name(); //����� ��������� ����� �������
	void set_name(string n); //����� ��������� ����� �������
	cl_base* get_parent(); //����� ��������� ��������� �� ������ ��������
	void set_parent(cl_base* pparent); //����� ��������� ������ �������-��������
	void get_tree(); //����� ���������� ������ ��������
	int get_children_size(); //����� ��������� ���������� ����������� �������� ��� ������� �������
	~cl_base(); //����������
	cl_base* find_obj_by_name(string name); //����� ������ ������� �� �����
	void get_tree_with_ready(); //����� ��� ������ ������ �������� �������� � �� ������������ ����������
	int get_ready_pointer(); //����� ��������� �������� ���������� ����������
	void set_ready_pointer(int pointer); //����� ��������� ������ �������� ���������� ����������
	cl_base* find_obj_by_path(string path); //����� ���������� ������� �� ��� ����
	string get_path(string path = "");//����� ��������� ����������� ���� �������
	void set_ready_for_all_objects(int ready_pointer);//����� ��������� � ��������� ���������� ���� �������
	void set_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler);//����� ��������� ����� ����� ���� ������-����������
	void del_connect(TYPE_SIGNAL signal, cl_base* pobj, TYPE_HANDLER handler);//����� �������� ����� ���� ������-����������
	void emit_signal(TYPE_SIGNAL signal, string& message);//����� �������� �������
	int get_numb_of_class();//����� ��������� ������ ������
private:
	string name; //����, ���������� �� ��� �������
	cl_base* parent; //����, ���������� �� ��������� �� ������ ��������
	vector <cl_base*> children; //����, ���������� �� ������ �����
	int ready_pointer;//����, ���������� �� ��������� ����������
	int tab_control;//����, ���������� �� �������� ��������� ��� ������ ������ ��������
	struct connections//��������� ����� ����� ���� ������-����������
	{
		TYPE_SIGNAL signal; //������ �� ����� ������� �������
		cl_base* h_obj; //��������� �� ������� ������, �������������� ������
		TYPE_HANDLER handler; //����� ����������� ������� �������� �������
	};
	vector <connections*> connections_of_obj; //������, �������� ��������� ������ ���� ������-����������
protected:
	int numb_of_class; //����� ������ �������� �������
};

#endif