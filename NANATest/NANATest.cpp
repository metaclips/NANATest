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
#include <string>
#include <fstream>
#include <python3.6/Python.h>
#include <thread>

nana::form loginform,mainform; 
std::string pass, user;

//
void allow(std::string name, std::string pass)
{
	Py_Initialize();
	PyRun_SimpleString("from selenium import webdriver\n"
		"from selenium.webdriver.support.ui import Select\n"
		"from selenium.webdriver.chrome.options import Options\n"
		"from selenium.common.exceptions import TimeoutException\n"
		"from selenium.webdriver.common.desired_capabilities import DesiredCapabilities\n"
		"from selenium.webdriver.support.ui import WebDriverWait\n"
		"from selenium.webdriver.common.by import By\n"
		"from selenium.webdriver.support import expected_conditions as EC\n"
		"chrome_options = Options()\n"
		"chrome_options.Proxy = None\n"
		"chrome_options.add_experimental_option('prefs', { 'profile.managed_default_content_settings.javascript': 2 })\n"
		"driver = webdriver.Chrome(executable_path = 'c:\\chromedriver.exe', chrome_options = chrome_options)\n"
		"driver.set_window_position(-3000, 0)\n"
		"driver.get('https://smile.com.ng/scp/Login.action')\n"
		"fillName = driver.find_element_by_name('username')\n");
		std::string val = "fillName.send_keys('" + name + "')";
		PyRun_SimpleString(val.c_str());
		PyRun_SimpleString("fillPassword = driver.find_element_by_name('password')\n");
		val = "fillPassword.send_keys('" + pass + "')";
		PyRun_SimpleString(val.c_str());
		PyRun_SimpleString(
		"clic = driver.find_element_by_name('login')\n"
		"clic.click()\n"
		"select = Select(driver.find_element_by_name('account.status'))\n"
		"select.select_by_value('8')\n"
		"pressOK = driver.find_element_by_name('changeAccountStatus')\n"
		"pressOK.click()\n"
		"driver.delete_all_cookies()\n"
		"driver.close()\n"
		"driver.quit()"
	);
		Py_Finalize();
}
void fastpage()
{
	
	std::ifstream out("usr");
	out >> user;
	out.close();
	out.open("pswd");
	out >> pass;
	out.close();
	allow(user, pass);
}

void mainpage()
{
	nana::API::track_window_size(mainform, { 300,300 }, true);	//get windows min size note its true for min and max for false
	nana::API::track_window_size(mainform, { 400,300 }, false);
	mainform.caption("HautBot v1.0");	//header

	nana::label label(mainform, nana::rectangle(0, 0, 100, 100));
	mainform.caption("HautBot v1.0");	//header
	//make <bold> visible
	label.format(true);
	label.caption("<bold>HautBot v1.0</>");
	label.fgcolor(nana::color_rgb(0xFFFFFF));
	nana::API::effects_bground(label, nana::effects::bground_transparent(0), 0);
	nana::button fast(mainform, nana::rectangle(0, 15, 100, 100));
	nana::API::effects_bground(fast, nana::effects::bground_blur(2), 0.5);
	fast.caption("Fast");
	fast.edge_effects(true);
	nana::button slow(mainform, nana::rectangle(0, 15, 100, 100));
	slow.caption("Slow");
	slow.edge_effects(true);
	nana::API::effects_bground(slow, nana::effects::bground_blur(2), 0.5);
	nana::place place(mainform);
	place.div("<><weight=80% vertical<><weight=50% vertical fit label ><weight=30 gap=10 buttons>><>");
	place.field("label") << label;
	place.field("buttons") << fast << slow;
	place.collocate();
	fast.events().click([]() 
	{
		
		std::cout << "Hello" << std::endl;
		//fastpage();
		std::thread t(fastpage);
		t.detach();

	});
	nana::paint::image img("C:\\Users\\Michael\\Pictures\\mooo.jpg");
	nana::drawing dw(mainform);
	dw.draw([&img](nana::paint::graphics & graph)
	{
		img.stretch(nana::rectangle{ img.size() }, graph, nana::rectangle{ graph.size() });

	});
	mainform.modality();
}

void loginpage()
{
	nana::API::track_window_size(loginform, { 300,300 }, true);	//get windows min size note its true for min and max for false
	nana::API::track_window_size(loginform, { 400,300 }, false);
	loginform.caption("HautBot v1.0");	//header

	nana::textbox usr{ loginform }, pswd{ loginform };
	nana::button  login{ loginform, ("Login") },
		cancel{ loginform, ("Clear") };
	usr.tip_string(("User:")).multi_lines(false);
	pswd.tip_string(("Password:")).multi_lines(false).mask('*');
	usr.load("usr");
	usr.events().focus([&usr]() {usr.store("usr"); std::cout << usr.filename(); });
	pswd.load("pswd");
	pswd.events().focus([&pswd]() {pswd.store("pswd"); });
	cancel.events().click([&usr, &pswd]() {usr.reset(); pswd.reset(); });
	login.events().click([&usr, &pswd]() {loginform.close(); mainpage(); });
	// Define a place for the form.
	nana::place plc{ loginform };
	// Divide the form into fields
	plc.div("<><weight=80% vertical<><weight=70% vertical <vertical gap=10 textboxs arrange=[25,25]>  <weight=25 gap=10 buttons> ><>><>");
	//Insert widgets
	//The field textboxs is vertical, it automatically adjusts the widgets' top and height. 
	plc.field("textboxs") << usr << pswd;
	plc.field("buttons") << login << cancel;
	plc.collocate();

	nana::paint::image img("C:\\Users\\Michael\\Pictures\\mooo.jpg");
	nana::drawing dw(loginform);
	dw.draw([&img](nana::paint::graphics & graph)
	{
		img.stretch(nana::rectangle{ img.size() }, graph, nana::rectangle{ graph.size() });

	});
	dw.update();
	loginform.modality();
}



int main()
{
	// Define widgets
	loginpage();
	//Finially, the widgets should be collocated.
	//Do not miss this line, otherwise the widgets are not collocated
	//until the form is resized.
	

	nana::exec();
    std::cout << "Hello World!\n"; 
}
