# Magic Hand Solitary(solitui - Beta TUI)

Soitario Klondike Clasico jugable completamente desde la terminal.

Classic Klondike Solitary, completely playable from terminal.

## Controls/Controles

| Tecla/Key | Accion/ACtion |
| ----------- | --------------- |
| 'n' | juego nuevo/new game |
| 'q' | salir/exit |
| ' ' | robar/draw |
| 'u' | deshacer/undo |
| 'h' | mano magica/magic hand |
| 'f' | (auto) fundacion/foundation |
| 't' | (auto) tableau |
| '1-7' | seleccionar tableau/ select tableau |
| 'zxcv' | seleccionar fundacion/ select foundation |
> Para mover entre tableaus es necesario seleccionar desde cual se quiere
> mover y luego el tableau destino. De igual forma para mover de la fundacion
> a un tableau es necesario primero escoger la fundacion y luego el tableau
> de desetino.

> To move between tableaus you need to select source tableau and then select
> goal tableau. Likewise to move from foundation to tableau it's necesary to
> first select source foundation and then goal tableau.

## Compilacion/Compilation

```bash
cmake -B build
cmake --build build
./build/solitui
```

## Licencia/License

MIT - [LICENSE](./LICENSE)
```
Copyright (c) 2025-2026 Orkiin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

## Estado/Status

Version Beta TUI - funcional pero con posibles bugs. Reportar issues en [GitHub](https://gihub.com/Orkiin/MagicHandSolitary).

Beta TUI Version - may contain bugs. Report issues on [GitHub](https://gihub.com/Orkiin/MagicHandSolitary).
