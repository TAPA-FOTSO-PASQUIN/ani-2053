# Exercice 8 : Debug contre Release

J'ai construit `NKMath` (une bibliothèque statique, donc son « binaire » est un `.a`) dans les deux configurations, après un `jenga clean --project NKMath` pour chaque, avec `time`. `MonEssai` était trop petit pour montrer un écart.

## Debug

```bash
$ time jenga build --project NKMath --config Debug
Projects Built:  5/5
Warnings:       31
Time:           7.53s
Status:         ✓ SUCCESS
real	0m8,544s
$ ls -l Build/Lib/Debug-Linux/NKMath.a
-rw-rw-r-- 1 ... 1401012 Sep 21 09:37 Build/Lib/Debug-Linux/NKMath.a
```

## Release

```bash
$ time jenga build --project NKMath --config Release
Projects Built:  5/5
Warnings:       31
Time:           9.51s
Status:         ✓ SUCCESS
real	0m10,414s
$ ls -l Build/Lib/Release-Linux/NKMath.a
-rw-rw-r-- 1 ... 172392 Sep 21 09:39 Build/Lib/Release-Linux/NKMath.a
```

## Les quatre nombres

- Taille Debug : 1 401 012 octets.
- Taille Release : 172 392 octets, soit environ 8 fois moins.
- Temps Debug : 8,5 s (`real`).
- Temps Release : 10,4 s (`real`), soit environ 2 s de plus.

Les deux constructions ont bâti 5 projets (`NKMath` et ses dépendances) avec 31 avertissements, donc la comparaison est équitable. Je n'ai fait qu'un essai par configuration, l'écart de temps est petit et peut varier.

## Les lignes du `.jenga` qui l'expliquent

```bash
$ grep -n -A4 'filter("config:' Kernel/Foundation/NKMath/NKMath.jenga
63:    with filter("config:Debug"):
64-        defines(["_DEBUG", "DEBUG"])
65-        optimize("Off")
66-        symbols(True)
67:    with filter("config:Release"):
68-        defines(["NDEBUG"])
69-        optimize("Speed")
70-        symbols(False)
```

- **Taille** : en Debug, `symbols(True)` (ligne 66) garde les informations de débogage, ce qui gonfle le `.a`. En Release, `symbols(False)` (ligne 70) les retire. Je n'ai pas mesuré la part exacte de `symbols` et celle d'`optimize` (?).
- **Temps** : `optimize("Speed")` (ligne 69) demande au compilateur de travailler davantage, ce qui explique que le Release soit plus long à construire que le Debug, où `optimize("Off")` (ligne 65) ne fait rien.
- **Macros** : `_DEBUG`/`DEBUG` (ligne 64) contre `NDEBUG` (ligne 68) activent ou retirent du code selon la configuration. Je ne sais pas ce que le moteur en fait précisément (?).

