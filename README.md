# OiAK project - SPOILER, 2020




Cel i przeznaczenie projektu
--------

Celem projektu jest poznanie natury i mechaniki działania ataku SPOILER. Atak ten ma na celu wykorzystanie spekulatywnego wykonywania instrukcji przy przetwarzaniu potokowym procesora, w celu uzyskania mapy pamięci podręcznej. Wyciek mapy pamięci sam w sobie nie szkodzi urządzeniu czy danym na nim zawartych, lecz może zostać wykorzystany w celu zwiększenia skuteczności innych ataków na pamięć, przykładowo wzmocnić skuteczność ataku Rowhammer, bez potrzeby zakładania specjalnych warunków, jednocześnie posiadając uprawnienia zwykłego użytkownika. 

Wymagania systemowe i sposób uruchamiania / kompilacji
--------

Jako, że jest to podatność procesorów z rodziny Intel, koniecznym jest, aby test był uruchamiany na sprzęcie opartym o taki procesor. Dodatkowo, procesor ten musi obsługiwać spekulatywne wykonywanie instrukcji, gdyż jest to kluczowy element problemu. Program został napisany na systemy Unixowe.

Kompilacja następuje poprzez wywołanie z wiersza poleceń instrukcji "**make**" w folderze "src", następnie uruchamiamy program poleceniem "**./main**".

Przydatne informacje
--------
Dodatkowe informacje odnośnie ataku typu SPOILER i naszego programu znajdują się w raporcie **SPOILER.pdf**.
