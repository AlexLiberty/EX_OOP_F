#include "MenuFunction.h"

MenuFunction::MenuFunction()
{
    dir_name = "";
    type = "*.*";
    full_name = "";
    dir_adres = "";
    full_adres = "";
    file_name = "";
    old_name = "";
    name = "";
    new_name = "";
    adres = "";
    new_adres = "";
    new_full_adres = "";
    new_full_name = "";
}

//////////�������� ��� ����� �� �����//////////

void MenuFunction::show_file(string& dir_name, string& full_name, string& type)
{
    cout << "������ ����� ��������: ";
    getline(cin, dir_name);
    type = "*.*";
    full_name = dir_name + "\\" + type;
    cout << full_name << endl;

    _finddata_t f;//��������� ������ �����, ������ ���� ��� ��������� ���� ��� �������
    intptr_t desc = _findfirst(full_name.c_str(), &f);

    if (desc == -1)//�������� �� ������� ������� ���������, �� ������� ���� ������� 
    {
        cout << "������� ��� ������� �������� " << dir_name << endl;
        return;
    }

    do//���� �� do...while, ��� ������ ������� ���������� ��� ����, ���� ��� �������� �� ��������� _findfirst, � ���� ���������� ������ ������� �����
    {
        if (strcmp(f.name, ".") == 0 || strcmp(f.name, "..") == 0)
        {
            continue;
        }

        if (f.attrib == _A_SUBDIR)//"_A_SUBDIR" ���� � ������ ��������� �������� ����� � �������� _finddata_t, ���� ����� �� ��, �� ����, �� ���� ����� ��������� ������, � ������(���������)
        {
            cout << "���������\t" << f.name << endl;
        }
        else
        {
            cout << "����\t" << f.name << endl;
        }

    } while (_findnext(desc, &f) != -1);

    _findclose(desc);
}

//////////��������� ������ ��������//////////

void MenuFunction::make_dir(string& dir_adres, string& dir_name, string& full_adres)
{
    cout << "������ ������, �� ���� ������� �������� ���� �����: ";
    getline(cin, dir_adres);
    cout << "������ ����� ����� ��� ������ ��������: ";
    getline(cin, dir_name);
    full_adres = dir_adres + "\\" + dir_name;
    int result = _mkdir(full_adres.c_str());
    if (result == 0)
        cout << "������� "<< dir_name<<" �� �������: " << full_adres << ", ��� ������ ���������" << endl;
    else
        cout << "��� ������� �������� �� �������: " << full_adres << " ������� �������" << endl;
}

//////////��������� �����(��������)//////////

void MenuFunction::delete_dir(string& dir_adres, string& dir_name, string& full_adres)
{
    cout << "������ ������, �� ���� ����������� ����� ��� ������� ��������: ";
    getline(cin, dir_adres);
    cout << "������ ����� �����: ";
    getline(cin, dir_name);
    full_adres = dir_adres + "\\" + dir_name;

    if (_access(full_adres.c_str(), 0) == 0)
    {
        cout << "����������� �������: " << dir_name << endl;

        if (_rmdir(full_adres.c_str()) == 0)
        {
            cout << "������� "<< dir_name <<" �� �������: " << full_adres << ", ��� ������ ���������" << endl;
        }
        else
        {
            cout << "������� ��� �������� �������� '" << dir_name << "'" << endl;
        }
    }
    else
    {
        cout << "������� " << dir_name << " �� �������: " << full_adres << " �� ����." << endl;
    }
    return;
}

//////////��������� ������ �����//////////

void MenuFunction::create_file(string& dir_name, string& file_name, string& full_name)
{
    cout << "������ ������ ����� � ��� ������ �������� ����: ";
    getline(cin, dir_name);
    cout << "������ ����� ����� �� ���� ����������: ";
    getline(cin, file_name);
    full_name = dir_name + "\\" + file_name;
    cout << "����������� ����: " << file_name <<" � �������" << full_name << endl;
    ofstream file(full_name);

    if (!file)
    {
        cout << "������� ��� �������� ����� �� �������: " << full_name << endl;
    }
    else
    {
        cout << "���� " << file_name << " �� ������� " << full_name << ", ��� ������ ���������" << endl;
    }
}

//////////��������� �����//////////

void MenuFunction::delete_file(string& dir_name, string& file_name, string& full_name)
{
    cout << "������ ����� ������ ����� ����������� �����: ";
    getline(cin, dir_name);
    cout << "������ ����� ����� �� ���� ����������: ";
    getline(cin, file_name);
    full_name = dir_name + "\\" + file_name;
    cout << "����������� ���� " << file_name << endl;

    if (remove(full_name.c_str()) == 0)
    {
        cout << "���� " << file_name << " �� �������: " << full_name << ", ��� ������ ���������" << endl;
    }
    else
    {
        cout << "������� ��� �������� ����� " << file_name << " �� ������� " << full_name << " ����� �� ����." << endl;
    }
}

//////////������������� �����//////////

void MenuFunction::rename_file(string& dir_name, string& old_name, string& name, string& new_name, string& new_full_name)
{
    cout << "������ ����� ������ ����� ����������� �����: ";
    getline(cin, dir_name);
    cout << "������ ����� ��'� �����: ";
    getline(cin, name);
    old_name = dir_name + "\\" + name;
    cout << "������ ���� ��'� �����: ";
    getline(cin, new_name);
    new_full_name = dir_name + "\\" + new_name;
    if (rename(old_name.c_str(), new_full_name.c_str()) == 0)
        cout << "����: " << name << ", ��� ������ �������������� ��: " << new_name << endl;
    else
        cout << "��� ������������ ����� �� ������� " << old_name << " ������� �������" << endl;
}

//////////���������� �����//////////

void MenuFunction::move_file(string& adres, string& name, string& full_adres, string& new_adres, string& new_full_adres)
{
    cout << "������ ������ ����������� �����: ";
    getline(cin, adres);
    cout << "������ ��'� �����: ";
    getline(cin, name);

    full_adres = adres + "\\" + name;

    cout << "������ ������, ���� ������� ���������� ����: ";
    getline(cin, new_adres);

    new_full_adres = new_adres + "\\" + name;

    ifstream source(full_adres, ios::binary);
    if (!source)
    {
        cout << "������� ������� ����� �� �������: " << full_adres << endl;
        return;
    }

    ofstream dest(new_full_adres, ios::binary);
    if (!dest)
    {
        cout << "������� ������ ����� �� �������: " << new_full_adres << endl;
        return;
    }

    dest << source.rdbuf();

    source.close();
    dest.close();

    if (remove(full_adres.c_str()) == 0)
    {
        cout << "���� " << name << " � ������: " << full_adres << ", ��� ������ ���������� �� �������: " << new_full_adres << endl;
    }
    else
    {
        cout << "��� ��������� �����: " << name << " ������� �������" << endl;
    }
}

//////////��������� ����� ����� �� �����//////////

void MenuFunction::show_file_content(string& adres, string& name, string& full_name)
{
    cout << "������ ����� �� ����������� ����: ";
    getline(cin, adres);
    cout << "������ ��'� �����: ";
    getline(cin, name);
    full_name = adres + "\\" + name;
    ifstream file(full_name);
    if (!file.is_open())
    {
        cout << "������� ��� ������� ���������� ����� �� ������� " << full_name << endl;
        return;
    }

    string line;

    cout << endl;
    cout << "\t\t\t\t\t\t���� ���������� ����� " << name << endl;
    cout << endl;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}


