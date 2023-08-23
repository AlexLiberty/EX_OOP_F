#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>// ƒл€ _rmdir та _mkdir
#include <io.h>//_access та _mkdir
#include <windows.h>

using namespace std;

class MenuFunction
{
protected:
	string dir_name;
	string type;
	string full_name;
	string dir_adres;
	string full_adres;
	string file_name;
	string old_name;
	string name;
	string new_name;
	string adres;
	string new_adres;
	string new_full_adres;
	string new_full_name;
	int photoID;
public:
	MenuFunction();
	void show_dir(string& dir_name, string& full_name, string& type);
	void show_file(string& dir_name, string& full_name, string& type);
	void make_dir(string& dir_adres, string& dir_name, string& full_adres);
	void delete_dir(string& dir_adres, string& dir_name, string& full_adres);
	void create_file(string& dir_name, string& file_name, string& full_name);
	void delete_file(string& dir_name, string& file_name, string& full_name);
	void rename_file(string& dir_name, string& old_name, string& name, string& new_name, string& new_full_name);
	void move_file(string& adres, string& name, string& full_adres, string& new_adres, string& new_full_adres);
	void show_file_content(string& adres, string& name, string& full_name);
};

