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

int main()
{
	nana::form form;
	nana::API::track_window_size(form, { 300,300 }, true);	//get windows min size note its true for min and max for false
	nana::API::track_window_size(form, { 400,300 }, false);
	nana::label label(form,nana::rectangle(0,0,100,100));
	form.caption("HautBot v1.0");	//header
	//make <bold> visible
	label.format(true);
	label.caption("<bold>HautBot v1.0</>");
	label.fgcolor(nana::color_rgb(0xFFFFFF));
	nana::API::effects_bground(label, nana::effects::bground_transparent(0), 0);
	nana::button fast(form, nana::rectangle(0, 15, 100, 100));
	nana::API::effects_bground(fast, nana::effects::bground_blur(2), 0.5);
	fast.caption("Fast");
	nana::button slow(form, nana::rectangle(0, 15, 100, 100));
	slow.caption("Slow");
	nana::API::effects_bground(slow, nana::effects::bground_blur(2), 0.5);
	nana::place place(form);
	place.div("<><weight=80% vertical<><weight=50% vertical fit label ><weight=30 gap=10 buttons>><>");
	place.field("label") << label;
	place.field("buttons") << fast << slow;
	place.collocate();
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
