#include <stdlib.h>
#include <stdio.h>

#include "cl_base.h"
#include "cl_application.h"

int main()
{

	cl_application ob_cl_application(nullptr); //создание корневого объекта
	ob_cl_application.build_tree_object(); //построение дерева иерархии
	return ob_cl_application.exec_app(); //вывод дерева иерархии на экран
}
