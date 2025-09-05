#include <iostream>
#include <fstream>
#include <random>
#include "ConsoleInterface.hpp"
#include "GeneratorArithmetics.hpp"
#include "MyException.hpp"

//Глобальные переменные
std::random_device rd;   // Источник случайных чисел
std::mt19937 gen(rd());  // Генератор случайных чисел

main() {
	setlocale(LC_ALL, "Rus");
	std::ofstream fileOut;
	int result;
	std::string name_file_txt;
        ConsoleInterface obj(0, 0, 0, 0, "");
	try {
                obj.setConfigureInterface();
		obj.setSymbols();
		std::cin >> name_file_txt;
                if (name_file_txt.size() < 4 || name_file_txt.substr(name_file_txt.size() - 4) != ".txt") throw IncorrectNameFile();
		fileOut.open(name_file_txt, std::ios::out);
	}
	catch (const std::ios_base::failure& e) {
		std::cerr << "Ошибка работы с файлом!" << e.what() << '\n';
	}
	catch (IncorrectNameFile& e) {
		std::cout << e.what() << '\n';
	}
	catch (IncorrectNumMinMax& e) {
		std::cout << e.what() << '\n';
	}
	catch (IncorrectMinMax& e) {
		std::cout << e.what() << '\n';
	}
	catch (IncorrectNumOfExamples& e) {
		std::cout << e.what() << '\n';
	}
	catch (IncorrectNumOfActions& e) {
		std::cout << e.what() << '\n';
	}
	catch (UnknownOperation& e) {
		std::cout << e.what() << '\n';
	}
	catch (...) {
		std::cerr << "Ошибка: Вызвано общее исключение!" << '\n';
	}
        
        try{
                std::uniform_int_distribution<int> distribResult(obj.getRangeNumMin(), obj.getRangeNumMax());
		
                short int count = obj.getCountArithExpres();
                while (count != 0) {
			result = distribResult(gen);
			std::unique_ptr<Node> expression = generateExpression(result, obj.getCountOperation(), obj);
			count--;
			fileOut << *expression << " = " << '\n' << "Ответ: " << result << '\n';
		}
		fileOut.close();
         }
        catch (IncorrectResult& e){
                std::cout << e.what() << '\n';
        }
	catch (const std::overflow_error& e) {
		std::cerr << e.what() << '\n';
	}
         catch (const std::runtime_error& e) {
		std::cerr << "Нет доступных операций для генерации выражения" << '\n';
	}
        catch (...) {
		std::cerr << "Ошибка: Вызвано общее исключение!" << '\n';
	}
        system ("pause");
	return 0;
}
