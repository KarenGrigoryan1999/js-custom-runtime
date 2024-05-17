// vs-runtime.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    Variables::setupDefaultPrototypes();

    ifstream file("C:\\Users\\Karen\\Desktop\\program.vs");

    if (!file.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        return 1;
    }

    string code;
    string line;
    while (getline(file, line)) {
        code += line + '\n';
    }

    file.close();

    try {
        Lexer* LexicalAnalizer = new Lexer(code);
        vector<Token>* list = LexicalAnalizer->tokenize();
        Parser* ASTGenerator = new Parser(list);
        Node* program = ASTGenerator->parse();
        program->eval();
    }
    catch (string msg) {
        cout << msg;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
