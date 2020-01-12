#include<iostream>
#include<cassert>
#include "project_1.hpp"

int main();
void print_program();
bool does_delimiter_match(char del);
bool do_delimiters_nest();

int main()
{
	 print_program();
	 std::cout << does_delimiter_match( '(' ) << std::endl;
	 std::cout << does_delimiter_match( '[' ) << std::endl;
	 std::cout << does_delimiter_match( '{' ) << std::endl;
	 std::cout << do_delimiters_nest() << std::endl;
	return 0;
}

void print_program()
{
	char t;
	ece150::start_reading_file();
	while(!ece150::at_eof())
	{
	t= ece150::get_next_character();
	std::cout<<t;
	}
	std::cout<<std::endl;
}

bool does_delimiter_match(char delimiter)
{
	bool flag=true;
	if(!(delimiter=='('||delimiter=='['||delimiter=='{'))
			return false;
	else
	{
		int count=0;
		char t;
		ece150::start_reading_file();
		while(!ece150::at_eof())
		{
			t= ece150::get_next_character();
			if(t==delimiter)
				count++;
			else if(t==delimiter+1 || t==delimiter+2)
				{
					if(count==0)
					{
						std::cout<<"Unmatched ";
						if(delimiter=='(')
							std::cout<<char(delimiter+1)<<std::endl;
						else
							std::cout<<char(delimiter+2)<<std::endl;
						flag=false;
					}
					else
						count--;
				}
		}

		if(count)
			std::cout<<"Missing ";

		while(count)
		{
			if(delimiter=='(')
				std::cout<<char(delimiter+1);
			else
				std::cout<<char(delimiter+2);
			count--;
			flag=false;

		}
		std::cout<<std::endl;

	}

return flag;

	}


bool do_delimiters_nest()
{
	bool flag=true;
	ece150::initialize_table();
	ece150::start_reading_file();
	char t;
	while(!ece150::at_eof())
	{
		t= ece150::get_next_character();
		if(t=='('||t=='['||t=='{')
		{
			ece150::place_character(t);
		}
		if(t=='}'||t==')'||t==']')
		{
			char z= ece150::get_right_most_character();
			if(z=='(')
				z=char(z+1);
			else if (z=='['|| z=='{')
				z=char(z+2);
			if(t==z)
			{
				ece150::erase_right_most_character();
			}
			else
			{
				std::cout<<"Unmatched "<<t<<std::endl;
				flag=false;
			}
		}


	}
	if(ece150::at_eof())
			{
				if(!ece150::is_table_empty())
				{
					std::cout<<"Missing ";
					flag=false;
				}
				while(!ece150::is_table_empty())
				{
					char temp;
					temp=ece150::get_right_most_character();
					if(temp=='(')
						std::cout<<char(temp+1);
					else
						std::cout<<char(temp+2);

					ece150::erase_right_most_character();
				}
				std::cout<<std::endl;
			}

	return flag;
}
