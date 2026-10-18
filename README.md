# ZPG projekt

Otevři `zpg_projekt.sln` ve Visual Studiu s nainstalovanou podporou vývoje desktopových aplikací v C++ a Windows SDK. Vyber `Debug | x64` nebo `Release | x64` a spusť projekt přes F5.

GLAD, GLFW a GLM jsou ve složce `Dependencies`. Cesty v projektu vycházejí z `$(ProjectDir)`. Projekt používá výchozí C++ toolset dané instalace Visual Studia a standard C++17. Dodaná GLFW knihovna je pro Windows x64.

Při sestavení se shadery zkopírují do složky `Shaders` vedle programu a knihovna `glfw3.dll` přímo vedle programu. Výstup je v `bin/x64/Debug` nebo `bin/x64/Release`. Visual Studio má pracovní adresář nastavený na tuto výstupní složku. Při spuštění z terminálu je potřeba nejprve přejít do ní.

| Klávesa / myš | Akce |
|---|---|
| 1–6 | Přepnutí scény: trojúhelníky, koule, les, login, sluneční soustava, hodiny |
| W / S | Pohyb kamery dopředu / dozadu |
| A / D | Pohyb kamery doleva / doprava |
| Držení pravého tlačítka a pohyb myši | Rozhlížení |
| Esc | Ukončení programu |

Ve scéně 4 ovládají klávesy objekt loginu: šipky posun X/Y, Page Up / Page Down posun Z, W/S rotaci kolem X, A/D kolem Y, Q/E kolem Z, Z/X zvětšení/zmenšení. R obnoví transformaci loginu.

Les obsahuje 74 stromů a 15 keřů. Kamera nemá kolize s objekty. Hodiny používají místní čas počítače a celý model včetně ručiček vykreslují jedním `glDrawArrays`. Jednotlivé části hodin rozlišuje shader podle barev vrcholů. Logo má barvu RGB 5, 195, 222 (#05C3DE). Název okna je vždy ZPG.

Do Gitu patří zdrojové soubory, `Models`, `Shaders`, `Dependencies`, `.sln`, `.vcxproj` a `.vcxproj.filters`. Složky `.vs`, `bin`, `obj`, staré lokální výstupy a soubory `.user` jsou ignorované. Po přenosu těchto změn přes Git není potřeba ve škole znovu nastavovat cesty ke knihovnám.

GLM licenci obsahuje `Dependencies/glm/copying.txt`, GLFW licenci `Dependencies/glfw/LICENSE.md`. GLAD má licenční informace v hlavičce `Dependencies/glad/include/glad/gl.h`.
