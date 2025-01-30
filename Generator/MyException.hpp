#pragma once
#ifndef _MYEXCEPTION_HPP_
#define _MYEXCEPTION_HPP_
#include <iostream>
#include <string>

struct GeneratorOperationError : public std::exception {
	virtual const char* what() const noexcept = 0; //Сообщение для печати
};

struct IncorrectResult : GeneratorOperationError{
        const char* what() const noexcept override { return "Ошибка: Неверная генерация результата!"; }
};

struct UnknownOperation : GeneratorOperationError {
	const char* what() const noexcept override { return "Ошибка: Неизвестная арифметическая операция!"; }
};

struct IncorrectNumOfExamples : GeneratorOperationError {
	const char* what() const noexcept override { return "Ошибка: Некорректно задано количество примеров!"; }
};

struct IncorrectNumOfActions : GeneratorOperationError {
	const char* what() const noexcept override { return "Ошибка: Некорректно задано количество арифметических действий!"; }
};

struct IncorrectNumMinMax : GeneratorOperationError {
	const char* what() const noexcept override { return "Ошибка: Некорректно задан диапазон минимума! Допустимый диапазон от -100000 до 100000"; }
};

struct IncorrectMinMax : GeneratorOperationError {
	const char* what() const noexcept override { return "Ошибка: Некорректно заданы диапазоны минимума и максимума! Проверьте, чтобы последовательность была возрастающей!"; }
};

struct IncorrectNameFile : GeneratorOperationError {
	const char* what() const noexcept override { return "Ошибка: Некорректно задано расширение файла, либо название файла не содержит более 4 символов!"; }
};
#endif // _MYEXCEPTION_HPP_
