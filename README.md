# cpp_module_09


### Clarifications and general tips:

* If you find any kind of error or have suggestions to improve, please do not hesitate to point them out in the `issues` section! Obviously always respectfully, thank you :D.
* Always remember that the output examples are just examples. They can vary in your own project and still be fine.
* This module focuses on **the STL (Standard Template Library)**, applying standard containers to solve different problems involving data processing, mathematical expressions and sorting algorithms.
* Remember that **once a container is used in one exercise, it cannot be used in the remaining exercises**. Exercise 02 requires two different containers.
* The entire module must comply with the **C++98 standard**. Compile your programs using `c++` with the flags `-Wall -Wextra -Werror`.


## ex00: Bitcoin Exchange

### Mandatory requirements completed and how:

* Create a program named `btc` that:
    * Takes a file as an argument.
		- The program ensures that there are enough arguments to run and opens the file itself to check its viability.
    * Reads a database in CSV format containing historical Bitcoin exchange rates.
		- Same file check that is done with the input file. Then, the database is saved in a map(string, float) container, spliting the value and the date data, so that the date is the key value, and the float is the number.
		 Althoug, while I was workign I made the mistake of storing the CSV file content in a container (including a parsing of the CSV file). But (en el transcurso del proyecto) I realised It wasnt necessary at all. The important thing to check is that the file exists.
    * Processes an input file where each line follows the format `date | value`.
		- The program reads every byte of the file and stores it in a line string.
		- When it founds a line break, the first thing it checks its the "header". In the subject, there isn`t any rules about how the file structure is suppose to be, it just gives you an imput example that starts with a header and ends in a empty line. So this program checks if the header is the same as the input example, if is not the same, an exception is thrown, but the program continues. This is very important, the program should be able to process and empty file, and it shouldn´t stop its execution even if it finds one error. Thats why this program use an structure that reads, checks, stores and prints the result for each line, even if it is an error message.
		- One of the problems founded in this logic, is that a file without an empy line at the end ist tecnically correct. So in that case, to process the last line that doesn't have a line break, I took the part of the function in charge of parsing and printing each line, and with that create a new function (`process_line`), that can be called outside the loop to process the last line of the file (if exists).
    	* Validates dates in the `Year-Month-Day` format.
			- `date_parser` is the function in charge of this task. Starting with the number of hypen symbols that are in the line, this checks te structure and also searchs for negative numbers, giving an error if there are`nt exactly two.
			- After that verification, the date is splited in three and each part is traversed to check that all of them are numbers, and that the format is YYYY-MM-DD with a char counter (the month and day verification are done by the same function).
			- Once whe can ensure that all the date parts are numbers, the program checks if there are possible dates (between 1 and 31). Here I nedeed to have exceptional care with the especial days such as leap years or months that do not end on the 31st. To solve this situation, the program checks the leap years only if the month is february. The other case is verified with the function `check_date`, verifying that the months end on the correct day, depending on whether they are even or odd, and then if the are in a certain group of numbers.
    	* Accepts positive integer or floating-point values between `0` and `1000`.
			- Since the requirementes for the value number are these few, `value_parser` only checks that they are integers or float numbers, and also that are in the correct range. These verfications are done in the if `isInt` and `isEsInt` functions, that iterate the hole number checking that they have all the elements to be a float or a integer, if not they return error.
    * Calculates the value of the given amount by multiplying it by the corresponding Bitcoin exchange rate.
		-  The calculation is done in the same function that prints the solution (`solution_printer`), right before showing it in the output and with the correct format, all the necessary values are recovered and used to form the result. The function searchs for the especific date in the container that has all the data of the CSV file. If it founds it, it does the calculation with the value in the map container that has the same key as the date
    * Uses the closest lower date from the database when the exact date is not available.
		- If inside `solution_printer`, the date isn't found. The function use `lower_bound` to find int the map container, the first key that is higer or equal than date. But that's not good enough for us, the subject said we need the "closest lower date", so thats why when `lower_bound` finds the date, we go back in the CSV container and choose the date before as our key. If that key is the first one in the list or there isn't any previous date, the program displays an error, if is the last one it goes back on the list, choosing the previous date, and since the databaseS is sorted by key, we will obtain the closest lower date.
* Use at least one STL container to store and process the data.
	* In this project `map` is used. As it is a containter that can store data and its unique key. Here the key is date and it is used to find the bitcoin value of that day. Perfect for doing our calculations and find the right value depending on the date.
* Handle possible errors with appropriate error messages, including invalid dates, negative values, values exceeding the allowed limit and malformed input.
	- The errors are handled with exceptions classes, and the messages are implemented in the .cpp file.


### What can we learn about this exercise?

This exercise introduces **file parsing, data validation and associative containers** through a program that processes historical Bitcoin exchange rates. It also teaches us how to search for the closest available date in an ordered database and handle invalid input safely.

### Output example:

![Example](images/ex00-output.png)


## ex01: Reverse Polish Notation

### Mandatory requirements completed and how:

* Create a program named `RPN` that:
    * Takes an inverted Polish mathematical expression as an argument.
	- The program checks if there are only the necessary number of arguments in the input, if not an error message is displayed and the program ends.
	* Handle invalid expressions displaying an error message on the standard error if an error occurs during execution.
	- When the program has enough numbers to work, `line_parser` ensures that the mayority of the strucutre of the mathematical expression is correct. Serarching for characters that aren't integers, spaces or the required mathematical expressions. Other important structre part that it checks are the spaces, this program doesn't allow spaces at the beginning or at the end of the expression, also any permitted character must have an space after (not including the ending). This is done by checking the character following the one currently being iterated over (taking into account the spaces), and being careful whith the acces to empty data. 
    * Evaluates the expression and displays the correct result on the standard output.
	- The other function that checks the expression before any mathematical calculation is done is `expression_parser`, this function in particular count the numbers and the symbols of the expression, because for the expression to be considered correctly expressed in Reverse Polish Notation, there must be two operands available for every operator. 
	- [Once we are sure that he expression is valid, the program starts storing its parts, the first thing that does is chekcing out that the first two permited characters are numbers, (activating a flag so this check is only done one time), and stores the result until it founds an operator, if they aren't it displays an error. When the program has all the elements to perform a calculation, it calls `stack_resolver` to solve it, storing the result in a temporary stack container that is again called as the first operand when the function has again enough elements. This way, to solve all the expression, the program solves a part and recursively use it to solve the next part of the epression, having as final result the correct output of the expression.]
    * Supports the following operators: `+`, `-`, `/` and `*`.
	- Delving into `stack_resolver`, the function takes the first and second operands stored in stack (before deleting them to free stack for the next part of the expression), change them to normal ints, and depending on the operator that is passed from `expression_processor`, performing the relevant mathematical operations. The result is stored in the structre `final_result`, and printed when the loop in `expression_processor` is over.
* Use at least one STL container to evaluate the expression.
- The container `std::stack` is used here because of its FIFO logic (Fist In First Out), that is useful to store the numbers, but also for the `stack_resolver` part to collect the necessary operands to solve the expression.

### What can we learn about this exercise?

This exercise introduces **Reverse Polish Notation (RPN)**, a mathematical notation in which operators follow their operands. It teaches us how to evaluate expressions using an STL container, process tokens and perform arithmetic operations in the correct order without requiring parentheses or operator precedence rules.

### Output example:

![Example](images/ex01-output.png)


## ex02: PmergeMe

### Mandatory requirements completed:

* Create a program named `PmergeMe` that:
    * Takes a sequence of positive integers as arguments.
	- This program needs at least two arguments to work, so first it chekcs the number of the arguments to make sure that there aren't only one.
	- To check that the numbers are valid, `ArgumentParsing` checks each one making sure that there aren't below zero or more than the maximum integer limit.
    * Uses at least two different STL containers to validate this exercise.
	- In this exercise are used three containers: `std::vector`, `std::deque` and `std::pair`.
    * Sorts the sequence using the **merge-insertion sort algorithm**, also known as the **Ford-Johnson algorithm**.
	- The **Ford-Johnson algorithm**, is a sorting algorithm that aims to order a sequence using the minimum number of comparisons between elements—unlike functions such as `sort`, where this is not a priority. This is achieved, in part, because the algorithm leverages information from previous comparisons to avoid unnecessary ones.
	- To archieve the efficiency of the **Ford-Johnson algorithm**, each one of their tasks are defined and implemented in this way:
		- Making pairs: A contanier (`std::vector` or `std::deque`), is created and prepared to store `PairNumbers` objects (a structure made so that each object can store a big number, a small number and an unique id that identifies the pair). When the `main_creator` function is called (a function template to work with `std::vector` and `std::deque`), its saves the extra number if the number of arguments is odd. Then it change them to integers, analise the numbers and forms pairs in order of arrival, for each pair an `PairNumbers` object with an unique id is created, in each object there would be a big and a small number.
		- Sorting the bigger ones: For each pair made, the recently classified big numbers will be stored in a separate container, and before making any comparisons, the `main_creator` function will be called recursively to sort this big numbers with the **Ford-Johnson algorithm**, allways if there are enough big numbers to sort.
		- Creating the "main chain": Once we have our big numbers ordered, `chair_function` will take the container with all the pairs and this big numbers sorted as reference. Becaus insided this function, all the ids in the container will change and have the same order spcified by big nubmers order, (controlling repeated numbers with a used flag).
		- With these new order, two new groups will be created storing all the bigger ones and all the smaller ones chair_function respectively, but they will be stored in a container that holds pairs (an `std::vector` that holds `std::pair` objects), it must be pairs, because each small or big number will have also the id of their specific pair. In this way, the relationship between pairs it stays together even if the members are in separated containers, because the still have the id of their pairs.
		- Now that everything is in its place, we start creating the "main chain". For that we have to collect all our big numbers and place them in the `main_chain` variable. After that it searchs in the `SmallOnes` container for the smallest number of the first pair (the one with the id zero), and place it at the beginning of the `main_chain`. This reduce the number of comparisons as we surely know that this number is smaller than all the big ones ordered.
		- Finally is time to insert our smaller numbers in the `main_chain`. But first, to reduce the number of comparisongs, `jacky_resolution` has to sort the small numbers, and it does this using the Jacobsthal sequence previously generated in `jacky_secuency`. In practice, we insert the pending elements in "groups" based on their position in the secuency, processing each group backwards between consecutive Jacobsthal numbers. For example, if the Jacobstahl secuency generated is 1 2 3 5 we insert backwards the elements at index 5 - 3, at index 3 - 2, then index 2 - 1, and then index 1. The number of elements generated in the secuency are equal than the size of `SmallOnes`.
		- Once our small numbers are sorted, we insert them in the `main_chain` through binary insertion. That means that before inserting the number, the function searchs for the middle number of the chain, when it founds it, it checks if the number is higher or lower than the number in the middle, depending of the result it iterates until if founds the correct position of the number. However, in the **Ford-Johnson algorithm** we want the least number of comparsiongs, and to archieve this, `binary_insertion` searchs the middle number between the start of the chain and the Big number, what big number?, the partner of the small number we want to insert in the chain. Searching by the id, the function founds it and do the search within does limits, reducing the number of comparisons even more.
    * Displays an error message on the standard error if an error occurs during execution.
* Display the unsorted sequence, the sorted sequence, the execution time for the first and the second container on the last line. Measure the time required for the complete operation, including sorting and data management.
- The display of the time is done with the `std::clock` function. For each cointainer, `std::clock` registers the time when `main_chain` is called and when it its done with the sorting. Finally, the difference between `endV` and `startV` is converted to a double and multiplied by one million, then divided by CLOCKS_PER_SEC to calculate the CPU time in microseconds. This allows us to measure how much CPU time the function takes to execute.

### What can we learn about this exercise?

This exercise introduces **advanced sorting algorithms, container comparison and performance measurement**. It focuses on the Ford-Johnson algorithm, which uses a merge-insertion strategy to sort elements efficiently. It also helps us understand how different STL containers can affect execution time when implementing the same algorithm.

### Output example:


![Example](images/ex02-output.png)


#### Last but not least, check out these other repositories if you feel lost, they helped me a lot through the project:

* [42 C++ Module 09 — Reference repository](https://github.com/qduong42/42_cpp_Module09)
* [C++ Module 09 — STL exercises and explanations](https://github.com/tigran-sargsyan-w/cpp-module-09)




# cpp_module_09

Hay que explicar bien el código de ex00, contenedores y su lógica, por que lo he escogido, etc...
PUEDES PONER CONTRUCTORES EN LAS CLASES y mensajes en las excepciones

ex02, cuidado cuando se comparan direcciones de memoria en vez de los números en si

https://github.com/leske42/CPP09
https://github.com/0x416c6941/cpp09/tree/main/cpp09/ex00
https://github.com/tigran-sargsyan-w/cpp-module-09#ex02--pmergeme


template <typename Q, typename S>
void binary_insertion(Q& result, const S& SmallOnesOrg)
{
    for (size_t i = 0; i < SmallOnesOrg.size(); ++i)
    {
        int small = SmallOnesOrg[i].first;
        int id = SmallOnesOrg[i].second;

        // Buscar el big asociado mediante su id.
        size_t bigPos = 0;
        while (bigPos < result.size()
            && result[bigPos].second != id)
        {
            ++bigPos;
        }

        // Si no existe el big asociado, no podemos acotar la búsqueda.
        if (bigPos == result.size())
            continue;

        // Búsqueda binaria desde el inicio hasta antes del big asociado.
        size_t first = 0;
        size_t last = bigPos;

        while (first < last)
        {
            size_t mid = first + (last - first) / 2;

            if (result[mid].first < small)
                first = mid + 1;
            else
                last = mid;
        }

        // Insertar el small conservando el id de su big.
        result.insert(result.begin() + first,
                      std::make_pair(small, id));
    }
}

¿Qué hace exactamente?
Lee el número pequeño y su id desde SmallOnesOrg.

Busca en result el elemento grande que tiene ese mismo id.

Guarda su posición en bigPos.

Busca la posición correcta del pequeño únicamente en el rango [0, bigPos).

Inserta el pequeño como std::make_pair(small, id), conservando la asociación.

Por ejemplo, si result contiene:

text
(4, 10)  (8, 20)  (12, 30)
Y SmallOnesOrg contiene:

text
(6, 20)
La búsqueda queda limitada a los elementos anteriores al 8, y el resultado es:

text
(4, 10)  (6, 20)  (8, 20)  (12, 30)
El 6 conserva el id 20, igual que su asociado 8.

Dos detalles importantes
Duplicados: esta función identifica el asociado por el id, no por el valor numérico. Así, dos números iguales pueden mantener asociaciones distintas, siempre que los id identifiquen de forma única cada pareja.

Orden de inserción: en Ford-Johnson, los pequeños se insertan siguiendo el orden determinado por los números de Jacobsthal, no necesariamente en el orden en el que aparecen en SmallOnesOrg. Limitar cada búsqueda al big asociado es parte del algoritmo, pero para respetar su estrategia de comparaciones también debes mantener ese orden de inserción. 

Wikipedia
+1

Importante: el ejemplo anterior presupone que los id de SmallOnesOrg y result coinciden y que cada big asociado sigue presente en result. Si eliminas los pequeños de SmallOnesOrg al insertarlos, tendrás que hacerlo mediante un iterador o una estructura auxiliar para no invalidar las posiciones que recorres.