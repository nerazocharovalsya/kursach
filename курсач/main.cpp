#include <stdlib.h>
#include <stdio.h>

#include "cl_base.h"
#include "cl_application.h"

int main()
{

	cl_application ob_cl_application(nullptr); //�������� ��������� �������
	ob_cl_application.build_tree_object(); //���������� ������ ��������
	return ob_cl_application.exec_app(); //����� ������ �������� �� �����
}
