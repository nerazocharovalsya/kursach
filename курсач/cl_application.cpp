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
int cl_application::get_result()//���������� ������ ��������� �������� ���������� ����������
{
	return result;
}
void cl_application::set_result(int result)//���������� ������ �������� ������ �������� ���������� ����������
{
	this->result = result;
}
string cl_application::get_primer()//���������� ������ ��������� �������� ���������
{
	return this->primer;
}
void cl_application::set_primer(string primer)//���������� ������ ��������� �������� ���������
{
	this->primer = primer;
}
void cl_application::signal_proc(string& message)//���������� ������ �������
{
	message += " ";
}
void cl_application::handler_proc(string& message) {}//���������� ������ �����������
int cl_application::exec_app() //����� ������ ������ �������� �� �����
{
	this->set_ready_for_all_objects(1);//��������� ���� ��������
	this->set_primer("");
	string primer = "";//������� ������ � �������
	cl_base* cur_obj;//��������� �� ������, ���������� ������
	int k = 0;//�������� �������� �� ����� ������
	while (this->get_primer() != "Off")
	{
		this->emit_signal(TOSIGNAL(cl_application::signal_proc), primer);//������ ������� �� ������ �������
		primer = this->get_primer();
		if (primer == "C")
		{
			cur_obj = this->find_obj_by_name("reader");
			cur_obj->emit_signal(TOSIGNAL(cl_1::signal_proc_c), primer);//�������� ������� �������-����������� ���� �������
		}
		else if (primer == "SHOWTREE")
		{
			cout << "Object tree with their readiness:" << endl;
			this->get_tree_with_ready();
			exit(0);
		}
		else if (primer != "Off")//�������������� �������� ��� �����
		{
			if (k != 0) {//������ ������ ��� �������� ������
				cout << endl;
			}
			cout << this->get_primer();//����� �������� �������
			k = 1;
			cur_obj = this->find_obj_by_name("reader");
			//������� ���������� ������
			if ((primer[primer.find_last_of(' ') - 1] == '<') || (primer[primer.find_last_of(' ') - 1] == '>'))
			{
				cur_obj->emit_signal(TOSIGNAL(cl_1::signal_proc_sdvig), primer);//�������� ������� �������, ������������ ��������� �����
				cur_obj = this->find_obj_by_name("sdvig");
				cur_obj->emit_signal(TOSIGNAL(cl_3::signal_proc), primer);//������ ������� ������� ��� ������ ���������� �� �����
			}
			//�������������� ��������
			else
			{
				cur_obj->emit_signal(TOSIGNAL(cl_1::signal_proc_count), primer);//�������� ������� �������, ������������ �������������� ��������
				cur_obj = this->find_obj_by_name("count");
				primer = this->get_primer();
				cur_obj->emit_signal(TOSIGNAL(cl_2::signal_proc), primer);//������ ������� ������� ��� ������ ���������� �� �����
			}
		}
		primer = this->get_primer();
	}
	return 0;
}
void cl_application::build_tree_object() //����� ���������� �������� ��������
{
	this->set_name("system");//��������� ����� ��������� �������
	cl_base* reader = new cl_1(this, "reader");//������, ����������� ���������������� �������
	cl_base* count = new cl_2(this, "count");//������, ������������ �������������� ��������
	cl_base* sdvig = new cl_3(this, "sdvig");//������, ����������� �������� ���������� ������
	cl_base* c = new cl_4(this, "c");//������, �������������� ����� ������������ � �������� ���������
	cl_base* print = new cl_5(this, "print");//������, ��������� ��������� ���������� �� �����
	//��������� ������ ���� ������(������,�������� ������)->����������(������,�������������� ������)
	//�������->��������� ������
	this->set_connect(TOSIGNAL(cl_application::signal_proc), reader, TOHANDLER(cl_1::handler_proc));
	//����������� ������->�������������� ��������
	reader->set_connect(TOSIGNAL(cl_1::signal_proc_count), count, TOHANDLER(cl_2::handler_proc));
	//����������� ������->��������� �����
	reader->set_connect(TOSIGNAL(cl_1::signal_proc_sdvig), sdvig, TOHANDLER(cl_3::handler_proc));
	//����������� ������->����� ������������ � �������� ���������
	reader->set_connect(TOSIGNAL(cl_1::signal_proc_c), c, TOHANDLER(cl_4::handler_proc));
	//������������� ��������->����� �� �����
	count->set_connect(TOSIGNAL(cl_2::signal_proc), print, TOHANDLER(cl_5::handler_proc));
	//��������� �����->�����
	sdvig->set_connect(TOSIGNAL(cl_3::signal_proc), print, TOHANDLER(cl_5::handler_proc));
}