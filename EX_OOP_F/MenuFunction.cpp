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

//////////Перегляд усіх папок та файлів//////////

void MenuFunction::show_file(string& dir_name, string& full_name, string& type)
{
    cout << "Введіть адрес директорії: ";
    getline(cin, dir_name);
    type = "*.*";
    full_name = dir_name + "\\" + type;
    cout << full_name << endl;

    _finddata_t f;//структура пошуку файлів, містить інфо про знайдений файл або каталог
    intptr_t desc = _findfirst(full_name.c_str(), &f);

    if (desc == -1)//перевірка чи вдалось відкрити директорію, на випадок якщо помилка 
    {
        cout << "Помилка при відкритті директорії " << dir_name << endl;
        return;
    }

    do//цикл на do...while, щоб спершу вивести інформацію про файл, який вже знайдено за допомогою _findfirst, а потім продовжити шукати наступні файли
    {
        if (strcmp(f.name, ".") == 0 || strcmp(f.name, "..") == 0)
        {
            continue;
        }

        if (f.attrib == _A_SUBDIR)//"_A_SUBDIR" один з бітових прапорців атрибутів файлів у структурі _finddata_t, який вказує на те, що файл, на який вказує результат пошуку, є папкою(каталогом)
        {
            cout << "Директорія\t" << f.name << endl;
        }
        else
        {
            cout << "Файл\t" << f.name << endl;
        }

    } while (_findnext(desc, &f) != -1);

    _findclose(desc);
}

//////////Створення нового каталогу//////////

void MenuFunction::make_dir(string& dir_adres, string& dir_name, string& full_adres)
{
    cout << "Введіть адресу, за якою потрібно створити нову папку: ";
    getline(cin, dir_adres);
    cout << "Введіть назву папки яку хочете створити: ";
    getline(cin, dir_name);
    full_adres = dir_adres + "\\" + dir_name;
    int result = _mkdir(full_adres.c_str());
    if (result == 0)
        cout << "Каталог "<< dir_name<<" за адресою: " << full_adres << ", був успішно створений" << endl;
    else
        cout << "При створені каталогу за адресою: " << full_adres << " виникла помилка" << endl;
}

//////////Видалення папки(каталогу)//////////

void MenuFunction::delete_dir(string& dir_adres, string& dir_name, string& full_adres)
{
    cout << "Введіть адресу, за якою знаходиться папка яку потрібно видалити: ";
    getline(cin, dir_adres);
    cout << "Введіть назву папки: ";
    getline(cin, dir_name);
    full_adres = dir_adres + "\\" + dir_name;

    if (_access(full_adres.c_str(), 0) == 0)
    {
        cout << "Видаляється каталог: " << dir_name << endl;

        if (_rmdir(full_adres.c_str()) == 0)
        {
            cout << "Каталог "<< dir_name <<" за адресою: " << full_adres << ", був успішно видалений" << endl;
        }
        else
        {
            cout << "Помилка при видаленні каталогу '" << dir_name << "'" << endl;
        }
    }
    else
    {
        cout << "Каталог " << dir_name << " за адресою: " << full_adres << " не існує." << endl;
    }
    return;
}

//////////Створення нового файлу//////////

void MenuFunction::create_file(string& dir_name, string& file_name, string& full_name)
{
    cout << "Введіть адресу папки в якій хочете створити файл: ";
    getline(cin, dir_name);
    cout << "Введіть назву файлу та його розширення: ";
    getline(cin, file_name);
    full_name = dir_name + "\\" + file_name;
    cout << "Створюється файл: " << file_name <<" у каталозі" << full_name << endl;
    ofstream file(full_name);

    if (!file)
    {
        cout << "Помилка при створенні файлу за адресою: " << full_name << endl;
    }
    else
    {
        cout << "Файл " << file_name << " за адресою " << full_name << ", був успішно створений" << endl;
    }
}

//////////Видалення файлу//////////

void MenuFunction::delete_file(string& dir_name, string& file_name, string& full_name)
{
    cout << "Введіть повну адресу папки знаходження файлу: ";
    getline(cin, dir_name);
    cout << "Введіть назву файлу та його розширення: ";
    getline(cin, file_name);
    full_name = dir_name + "\\" + file_name;
    cout << "Видаляється файл " << file_name << endl;

    if (remove(full_name.c_str()) == 0)
    {
        cout << "Файл " << file_name << " за адресою: " << full_name << ", був успішно видалений" << endl;
    }
    else
    {
        cout << "Помилка при видаленні файлу " << file_name << " за адресою " << full_name << " файлу не існує." << endl;
    }
}

//////////Переіменування файлу//////////

void MenuFunction::rename_file(string& dir_name, string& old_name, string& name, string& new_name, string& new_full_name)
{
    cout << "Введіть повну адресу папки знаходження файлу: ";
    getline(cin, dir_name);
    cout << "Введіть старе ім'я файлу: ";
    getline(cin, name);
    old_name = dir_name + "\\" + name;
    cout << "Введіть нове ім'я файлу: ";
    getline(cin, new_name);
    new_full_name = dir_name + "\\" + new_name;
    if (rename(old_name.c_str(), new_full_name.c_str()) == 0)
        cout << "Файл: " << name << ", був успішно перейменований на: " << new_name << endl;
    else
        cout << "При перейменувані файлу за адресою " << old_name << " виникла помилка" << endl;
}

//////////Переміщення файлу//////////

void MenuFunction::move_file(string& adres, string& name, string& full_adres, string& new_adres, string& new_full_adres)
{
    cout << "Введіть адресу знаходження файлу: ";
    getline(cin, adres);
    cout << "Введіть ім'я файлу: ";
    getline(cin, name);

    full_adres = adres + "\\" + name;

    cout << "Введіть адресу, куди потрібно перемістити файл: ";
    getline(cin, new_adres);

    new_full_adres = new_adres + "\\" + name;

    ifstream source(full_adres, ios::binary);
    if (!source)
    {
        cout << "Помилка читання файлу за адресою: " << full_adres << endl;
        return;
    }

    ofstream dest(new_full_adres, ios::binary);
    if (!dest)
    {
        cout << "Помилка запису файлу за адресою: " << new_full_adres << endl;
        return;
    }

    dest << source.rdbuf();

    source.close();
    dest.close();

    if (remove(full_adres.c_str()) == 0)
    {
        cout << "Файл " << name << " з адреси: " << full_adres << ", був успішно переміщений за адресою: " << new_full_adres << endl;
    }
    else
    {
        cout << "При переміщенні файлу: " << name << " виникла помилка" << endl;
    }
}

//////////Виведення змісту файлу на екран//////////

void MenuFunction::show_file_content(string& adres, string& name, string& full_name)
{
    cout << "Введіть адрес де знаходиться файл: ";
    getline(cin, adres);
    cout << "Введіть ім'я файлу: ";
    getline(cin, name);
    full_name = adres + "\\" + name;
    ifstream file(full_name);
    if (!file.is_open())
    {
        cout << "Помилка при відкритті текстового файлу за адресою " << full_name << endl;
        return;
    }

    string line;

    cout << endl;
    cout << "\t\t\t\t\t\tЗміст текстового файлу " << name << endl;
    cout << endl;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}


