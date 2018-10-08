// NANATest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/effects.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/textbox.hpp>

int main()
{

	// Define widgets
	nana::form form;
	nana::textbox usr{ form },
		pswd{ form };
	nana::button  login{ form, ("Login") },
		cancel{ form, ("Clear") };
	usr.tip_string(("User:")).multi_lines(false);
	pswd.tip_string(("Password:")).multi_lines(false).mask('*');
	// Define a place for the form.
	nana::place plc{ form };
	// Divide the form into fields
	plc.div("<><weight=80% vertical<><weight=70% vertical <vertical gap=10 textboxs arrange=[25,25]>  <weight=25 gap=10 buttons> ><>><>");
	//Insert widgets
	//The field textboxs is vertical, it automatically adjusts the widgets' top and height. 
	plc.field("textboxs") << usr << pswd;
	plc.field("buttons") << login << cancel;
	//Finially, the widgets should be collocated.
	//Do not miss this line, otherwise the widgets are not collocated
	//until the form is resized.
	plc.collocate();
	form.show();
	nana::paint::image img("C:\\Users\\Michael\\Pictures\\mooo.jpg");
	nana::drawing dw(form);
	dw.draw([&img](nana::paint::graphics & graph)
	{
		img.stretch(nana::rectangle{ img.size() }, graph, nana::rectangle{ graph.size() });
		
	});
	dw.update();
	
	nana::exec();
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
