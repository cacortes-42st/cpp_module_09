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