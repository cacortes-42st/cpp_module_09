# cpp_module_09

Hay que explicar bien el código de ex00, contenedores y su lógica, por que lo he escogido, etc...
PUEDES PONER CONTRUCTORES EN LAS CLASES y mensajes en las excepciones

ex02, cuidado cuando se comparan direcciones de memoria en vez de los números en si

https://github.com/leske42/CPP09
https://github.com/0x416c6941/cpp09/tree/main/cpp09/ex00
https://github.com/tigran-sargsyan-w/cpp-module-09#ex02--pmergeme


Una función extra debe de recorrer result, y en un objecto pair guardar el número grande y su posición actual, el resultado se guardará en un objecto llamado BigCopy
Debe recibir el objecto que almacena los números pequeños ordenados por Jacobsthal (SmallOnesOrg), la "main chain" (result) con los números grandes y el más pequeño ordenados, el PairNumbers que almacena todas las parejas con el id ya correcto de acuerdo al orden hecho en chair function y BigCopy.
Debe de recorrer SmallOnesOrg, y por cada número de ahí buscar en result a su pareja más grande. Esto se hace buscando en BigCopy y Pair Numbers, en el momento en que se encuentre un idX y un aX y su smallnumber coincida con el que está iterando el smallonesorg, el número va ahí ¿se entiende? podría funcionar?