# CG-projekt-brickpong

Projekt na zajęcia z Grafiki (OpenGL). Gra "Brickpong".

*Wszystkie podane niżej ścieżki są relatywne do głównego folderu repozytorium.*

## Instrukcje dotyczące bibliotek

Nie należy edytować żadnych plików w folderach `/glfw`, `/glm` oraz `/OpenGL-Tutorial`.
Aby przygotować bilioteki **GLFW** oraz **GLM** do użycia, należy to zrobić przy pomocy aplikacji **CMake** ustawiając jako folder docelowy odpowiednio:
- `/biblioteki/glfw`
- `/biblioteki/glm`

Jeżeli mają być użyte jakiekolwiek pliki z folderu `/OpenGL-Tutorial`, należy je skopiować do osobnego folderu roboczego - poza `/OpenGL-Tutorial`.

<!-- TODO: Uzupełnić instrukcje o informacje jak odpowiednio "podpiąć" biblioteki do projektu w odpowiednich IDE. -->

## Sterowanie w grze

- `Mysz` - poruszanie paletką
- `A`/`Strzałka w lewo` - przesuń paletkę w lewo
- `D`/`Strzałka w prawo` - przesuń paletkę w prawo
- `Spacja` - zatrzymaj piłkę
- `R` - zrestartuj grę
- `ESC` - zamknij grę
