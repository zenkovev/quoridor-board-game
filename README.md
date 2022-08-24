В проекте реализуется настольная игра Коридор. Правила и описание игры можно прочитать здесь: https://www.igroved.ru/games/quoridor/quoridor/. Кратко: в игре два/четыре игрока перемещают свои фишки и устанавливают стенки/перегородки, препятствующие движению. Цель игры: первым добраться до противоположного края поля.
Проект ставит перед собой цель реализовать компьютерную программу, имитирующую настольную игру. Реализовываются те действия, которые можно выполнить в настольной игре. Производится обработка простых ошибок: если ход некорректен (включает все ситуации, которые физически невозможны в настольной игре), то программа ничего не делает (или выводит сообщение: ход невозможен). При этом программа не гарантирует соблюдение абсолютно всех правил: сложные ситуации, которые просто заметить игроку, но достаточно долго обрабатывать машинным кодом, (пример: правило, что всегда должен существовать путь до финиша, или сам критерий победы: достижение противоположной линии) не проверяются. При этом гарантируется, что список этих правил исчерпывается тем, что в настольной версии должны проверять сами игроки. Также предполагается сделать возможными корректные модификации размеров поля и количества стенок а также количества игроков (два или четыре) перед началом игры. Для всего этого планируется создать хороший графический интерфейс.
Выполнение ходов производится так: на экране отображается участник, выполняющий текущий ход. Все данные от источника ввода воспринимаются как его действия до момента выполнения корректного хода. После этого автоматически меняется "ходящий" и игра продолжается. Это мотивировано тем, что игра не является турнирной, с закрытыми данными, с элементами случайности, поэтому игроки не заинтересованы сделать что-то вредное.
Эта часть, сформулированная до начала работы над проектом, реализована практически без изменений.

Установка проекта.

Для сборки необходимо установить графическую библиотеку gtkmm. Здесь http://www.gtkmm.org/en/download.html указано, каким образом это можно сделать. Затем сборка производится стандартным образом: клонируется данный репозиторий и собирается cmake в текущей директории.
Пример для сборки из текущей директории для Linux:
mkdir build
cd build
cmake ..
make
После этого появится директория bin, в которой будет содержаться исполяемый файл Quoridor. Его запуск и запустит игру.

Изменение параметров игры и исправление ошибок.

В текущей директории находится файл main.h. Он содержит только численные константы и много комментариев, объясняющих, за что они отвечают и какие у них допустимые численные значения. Изменение первых трёх параметров изменит характеристики игры, по умолчанию предлагается играть с установленными параметрами. Последний параметр SquarePixelSizes нужно использовать, если поле игры слишком мало или наоборот слишком велико и не вмещается на экран. Можно выбрать любое из допустимых указанных там значений и собрать проект с ним.

Процесс игры.

В левом верхнем углу расположены четыре кнопки, из которых в любой момент можно выбрать только одну. Она отвечает за тип хода, выполняемый в данный момент. После смены кнопки все выбранные для невыполненного хода параметры автоматически сбрасываются. Для выполнения хода "Ходить фигурой" нужно указать конечную клетку движения. Для выполнения хода "Установить стенку" необходимо выбрать перекрёсток и одну из двух частей стены. Для выполнения хода "Обойти фигуру противника" (перепрыгуть через неё) указывается конечная клетка движения. Если что-то мешает перепрыгнуть прямо (стенка, другая фигура), то можно выбрать ход "Обойти фигуру противника с препятствием" (перепрыгнуть со смещением в сторону), нужно выбрать фигуру противника и конечную клетку движения. Выбор производится непосредственно на игровом поле. Любой выбор клеток будет воспринят как ход и как-то разумно обработан, но рекомендуется использовать указанные выше способы. В процессе игры при некотором расположении может пропасть изображение фигуры игрока. После обнаружения этой проблемы клетки, в которых стоит фигура, были раскрашены в цвет этой фигуры, так что эта проблема не помешает корректно продолжить игру. Слева внизу расположены карточки игроков, в которых указано, выполняет ли он сейчас ход, сколько у него осталось стенок, сообщение об ошибке при выполнении хода, если она была совершена.

06.05.2022 Добавлен выбор параметров игры после запуска. Теперь перед появлением окна с игрой появляется окно, в котором можно выбрать, с какими параметрами запустить игру. При этом старый способ изменения файла-хедера остаётся рабочим - тогда в окне нужно выбрать пункты: значения по умолчанию. Гарантируется, что при любом выборе запуск будет корректен, за исключением того, что при некоторых комбинациях поле с игрой может не умещаться на экран монитора (исправляется последним столбцом с выбором размеров). После выбора нужных позиций необходимо закрыть это окно, тогда появится окно с самой игрой.
