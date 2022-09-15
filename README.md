# SmartCalc

## Реализация расширенной версии обычного калькулятора.
Помимо базовых арифметических операций, 
существует возможность вычисления арифметических выражений с учетом приоритетов, а так же математических функциий. 
Помимо вычисления выражений калькулятор поддерживает использование переменной x и построение графика соответствующей функции. 

- Программа разработана на языке C++
- Сборка программы настроена с помощью Makefile
- Для реализации калькулятора использован алгоритм Дейкстры для перевода выражений в обратную польскую нотацию
- Реализация графического интерфейса осуществлена на базе библиотеки Qt
- Программа реализована с использованием паттерна MVC
- На вход могут подаваться как целые, так и вещественные числа, записанные и через точку и в экспоненциальной форме записи
- Вычисление производится после полного ввода вычисляемого выражения и нажатия на символ =
- Программа поддерживает построение графика функции, заданной с помощью выражения в инфиксной нотации с переменной x
- Область определения и область значения функций ограничиваются числами от -1000000 до 1000000
- Возможность ввода до 255 символов
- Предусмотреть специальный режим "кредитный калькулятор" 
- Предусмотреть специальный режим "калькулятор доходности вкладов"