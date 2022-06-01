#include "cl_5.h"
#include "cl_application.h"

cl_5::cl_5(cl_base* pparent, string name) :cl_base(pparent, name)
{
	numb_of_class = 6; //присвоение полю номера текущего класса
}
void cl_5::signal_proc(string& message) {}//реализация метода сигнала объекта
void cl_5::handler_proc(string message)//реализация метода обработчика объекта
{
	string hex = "", bin = "", dec = message;
	bool negative = false;
	if ((message == "Division by zero") || (message == "Overflow"))//переполнение или деление на ноль
	{
		cout << "     " << message;
		((cl_application*)this->get_parent())->set_primer("0");//обнуление вычислений
		((cl_application*)this->get_parent())->set_result(0);//обнуление примера
	}
	else
	{
		int r = stoi(message);
		if (r < 0)
		{
			r = (-1) * r - 1;//представление в виде дополнительного кода
			negative = true;
		}
		//перевод в двоичную систему счисления
		for (int i = 15; i >= 0; i--)
		{
			if (r >= pow(2, i))
			{
				r -= pow(2, i);
				bin += "1";
			}
			else
			{
				bin += "0";
			}
			if (i % 4 == 0)
			{
				bin += " ";
			}
		}
		r = stoi(message);
		if (negative) {
			r = (-1) * r - 1;
		}
		//перевод в шестнадцатеричную систему счисления
		for (int i = 3; i >= 0; i--)
		{
			if (r % 16 > 9) {
				hex = char(int('A') - 10 + (r % 16)) + hex;
			}
			else {
				hex = to_string(r % 16) + hex;
			}
			r = (r - (r % 16)) / 16;
		}
		if (negative)
		{
			for (int i = 0; i < bin.size(); i++)
			{
				if (bin[i] == '0')
					bin[i] = '1';
				else if (bin[i] == '1')
					bin[i] = '0';
			}
			for (int i = 0; i < hex.size(); i++)
			{
				if (hex[i] - '0' <= 9)
				{
					if (hex[i] - '0' <= 5)
						hex[i] = char(int('F') - hex[i] + '0');
					else
						hex[i] = (15 + int('0') - int(hex[i])) + '0';
				}
				else {
					hex[i] = int('F') - int(hex[i]) + '0';
				}
			}
		}
		cout << "     ";
		bin.erase(bin.begin() + bin.size() - 1);//удаление последнего пробела
		cout << "HEX " << hex << "  DEC " << message << "  BIN " << bin;
	}
}