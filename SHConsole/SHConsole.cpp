// SHConsole.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "StreamHandler.h"

int main()
{
    std::string test("1 5 6\n2 8 6 5\n3 6 7 8 7 8 9 123\n1 5 5\n1 6 5\n2 7 7 7\n3 6 7 8 7 5 5\n4 6 7 8 7 5 5");
    while (true) {
        std::cout << "Enter block stream, type test for default or exit:" << std::endl;
        std::string input;
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "")
                break;
            input += line;
        }
        if (*(input.end()-1) == '\n') input.erase(input.end());
        if (input.compare("exit") == 0) {
            return 0;
        }
        auto sh = StreamHandler::Processing(7);
        if (input.compare("test") == 0) {
            input = test;
        }
        auto r_stream = sh.compute_blocks(input);
        std::cout << "\nr_stream:" << std::endl;
        for (auto item : r_stream) std::cout << std::to_string(item) << std::endl;
        sh.push(r_stream);
        if (sh.queue_is_full()) {
            std::cout << "\nmedian:" << std::endl;
            auto median = sh.median();
            std::cout << std::to_string(median) << "\n\n";
        }
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
