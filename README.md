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
		- The program reads every byte of the file and store it in a line string.
		- When it founds a line break, the first thing it checks its the "header". In the subject, there isn`t any rules about how the file structure is suppose to be, it just gives you an imput example that starts with a header and ends in a empty line. So this program checks if the header is the same as the input example, if is not the same, an exception is thrown, but the program continues. This is very important, the program should be able to process and empty file, and it shouldn´t stop its execution even if it finds one error. Thats why this program use an structure that stores the result and print it in each line 
    	* Validates dates in the `Year-Month-Day` format.
    	* Accepts positive integer or floating-point values between `0` and `1000`.
    * Calculates the value of the given amount by multiplying it by the corresponding Bitcoin exchange rate.
    * Uses the closest lower date from the database when the exact date is not available.
* Use at least one STL container to store and process the data.
	* In this project `map` is used. As it is a containter that can store two different types of data with the same key. Perfect for searching the correct date and selecting the value for the result calculation.
* Handle possible errors with appropriate error messages, including invalid dates, negative values, values exceeding the allowed limit and malformed input.

### 
In the subject it didn`t specified how the input file should be, it just gives an 
### What can we learn about this exercise?

This exercise introduces **file parsing, data validation and associative containers** through a program that processes historical Bitcoin exchange rates. It also teaches us how to search for the closest available date in an ordered database and handle invalid input safely.

### Output example:

```text
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

![Example](images/ex00-output.png)


## ex01: Reverse Polish Notation

### Mandatory requirements completed:

* Create a program named `RPN` that:
    * Takes an inverted Polish mathematical expression as an argument.
    * Evaluates the expression and displays the correct result on the standard output.
    * Supports the following operators: `+`, `-`, `/` and `*`.
    * Handles single-digit numbers smaller than `10` in the input. The calculation and the resulting value are not restricted by this rule.
    * Displays an error message on the standard error if an error occurs during execution.
* Use at least one STL container to evaluate the expression.
* Handle invalid expressions and ensure that mathematical operations are performed correctly.
* Do not handle parentheses or decimal numbers.

### What can we learn about this exercise?

This exercise introduces **Reverse Polish Notation (RPN)**, a mathematical notation in which operators follow their operands. It teaches us how to evaluate expressions using an STL container, process tokens and perform arithmetic operations in the correct order without requiring parentheses or operator precedence rules.

### Output example:

```text
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42

$> ./RPN "7 7 * 7 -"
42

$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0

$> ./RPN "(1 + 1)"
Error
```

![Example](images/ex01-output.png)


## ex02: PmergeMe

### Mandatory requirements completed:

* Create a program named `PmergeMe` that:
    * Takes a sequence of positive integers as arguments.
    * Sorts the sequence using the **merge-insertion sort algorithm**, also known as the **Ford-Johnson algorithm**.
    * Uses at least two different STL containers to perform the sorting.
    * Handles sequences containing at least `3000` different integers.
    * Displays an error message on the standard error if an error occurs during execution.
* Display the unsorted sequence on the first line.
* Display the sorted sequence on the second line.
* Display the execution time for the first container on the third line.
* Display the execution time for the second container on the last line.
* Measure the time required for the complete operation, including sorting and data management.
* Use an appropriate time precision to make the performance difference between the two containers visible.

### What can we learn about this exercise?

This exercise introduces **advanced sorting algorithms, container comparison and performance measurement**. It focuses on the Ford-Johnson algorithm, which uses a merge-insertion strategy to sort elements efficiently. It also helps us understand how different STL containers can affect execution time when implementing the same algorithm.

### Output example:

```text
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us

$> ./PmergeMe "-1" "2"
Error
```

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