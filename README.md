# Batalla Naval

Este juego es un juego maquina vs jugador por turnos.

## Instrucciones y recomendaciones

El juego esta diseñado por turnos una vez que usted dispare, la IA del mapa enemigo tambien poseera un turno para atacar de nuevo, eso usted puede verificarlo
en su parte del mapa que es el inferior si la IA dispara al agua aparecera una 'X' y si dispara a un barco una 'O'.

Usted puede ver todo el tiempo en estado de sus barcos y donde dispara la IA, pero no puede ver el estado de los barcos enemigos, solo puede ver que varco derribo una vez haya disparado a todas las piezas del barco.

Los barcos que puede colocar son 5: Porta Aviones, Acorazado, Submarino, Crucero y Destructor
Cada barco esta representado en la consola por el numero de espacios que ocupa de la siguiente manera: 'PPPPP' 'AAAA' 'SSS' 'CCC' 'DD'

:warning: **Es recomendable o casi necesario usar el editor de texto Zinjai para visualisar correctamente los resultados**: puedes descargarlo [aqui](https://zinjai.sourceforge.net)

## modo de uso

Para iniciar el juego es necesario compilar y ejecutar el codigo o ejecutar el archivo **GuerraNaval.exe**

Al momento de ejecutar el programa con zinjai se abrira la consola mostrando 2 tableros de 10x10.

El tablero de la parte inferior correspone al jugador, donde se podra mover mover con las teclas 'a','d','w','s'.

Para poder colocar su barco debe precionar la tecla 'c', en caso de querer rotar su barco presione la tecla 'b'.

Una vez posicionados sus barcos le aparecera un '*' en el mapa superior, eso significa que puede atacar a los barcos posicionados en el mapa enemigo
usando la tecla 'v', ahi puede verificar que al momento de atacar aparece una 'X' es poque diparó al agua y si sale 'O' disparo correctamente a la pieza de un barco enemigo.

:warning: **En caso de que la primera pieza aparezca fuera del tablero, vuelva a compilar el juego**

 