# Exercice 6 : Les deux erreurs de dépendance

`MonEssai` n'avait aucune dépendance, donc il n'y avait rien à retirer. J'ai d'abord créé une petite bibliothèque statique `MonLib` (une fonction `MonLibDouble`), déclarée au workspace, et fait appeler cette fonction par `MonEssai` avec `includedirs`, `links` et `dependson`. Avant chaque essai, j'ai supprimé `MonLib.a` et les objets pour repartir de zéro.

## Point de départ : `links` et `dependson` présents

```bash
$ jenga build --project MonEssai --config Debug
Build Order (2 projects):
  1. MonLib [STATIC_LIB]
  2. MonEssai [CONSOLE_APP] (depends: MonLib)
✓ Built: Build/Lib/Debug-Linux/MonLib.a
✓ Built: Build/Bin/Debug-Linux/MonEssai/MonEssai
Status:         ✓ SUCCESS
```

## Essai 1 : je retire `dependson` (je garde `links`)

```bash
$ grep -n "links\|dependson" Applications/MonEssai/MonEssai.jenga
12:    links(["MonLib"])
$ jenga build --project MonEssai --config Debug
Build Order (1 projects):
  1. MonEssai [CONSOLE_APP]
✓   [1/1] Compiled: main.cpp
ℹ Linking...
Compilation Error: Link Failed
/usr/bin/x86_64-linux-gnu-ld.bfd : ne peut pas trouver -lMonLib : Aucun fichier ou dossier de ce nom
collect2: error: ld returned 1 exit status
Build Failed  (Projects Built: 0/1)
```

**Message :** `ne peut pas trouver -lMonLib : Aucun fichier ou dossier de ce nom`. L'ordre de construction n'a plus qu'un projet : `MonLib` n'est pas construit avant, donc `MonLib.a` n'existe pas au moment de lier. `main.cpp` a compilé, l'échec est à l'édition de liens.

## Essai 2 : je remets `dependson` et je retire `links`

```bash
$ grep -n "links\|dependson" Applications/MonEssai/MonEssai.jenga
12:    dependson(["MonLib"])
$ jenga build --project MonEssai --config Debug
Build Order (2 projects):
  1. MonLib [STATIC_LIB]
  2. MonEssai [CONSOLE_APP] (depends: MonLib)
✓ Built: Build/Lib/Debug-Linux/MonLib.a
✓ Built: Build/Bin/Debug-Linux/MonEssai/MonEssai
Status:         ✓ SUCCESS
$ ./Build/Bin/Debug-Linux/MonEssai/MonEssai ; echo "code de sortie : $?"
code de sortie : 0
```

**Message :** aucun, la construction a réussi et le programme renvoie 0. Je n'ai pas réussi à provoquer l'erreur « undefined reference » annoncée par le chapitre.

## Ce qui distingue les deux

- **Sans `dependson`** : échec. La bibliothèque n'est pas construite, et le message parle d'un fichier introuvable. L'ordre de construction affiché passe de 2 projets à 1, ce qui le trahit.
- **Sans `links`** : succès. Avec cette version de Jenga (2.8.0) sur Linux, `dependson` a suffi à lier `MonLib`. Je ne connais pas la raison exacte, car je n'ai pas lu le code de Jenga (?). C'est peut-être propre aux bibliothèques du même workspace, et le cas d'une bibliothèque système comme `pthread` reste à tester.

Dans les deux cas, j'ai remis `links` et `dependson` ensuite, et la construction réussit de nouveau.

## Ce que j'ai compris

`dependson` a un effet visible et immédiat : sans lui, la bibliothèque n'est pas construite et l'édition de liens échoue. Le chapitre présente `links` comme indispensable, mais ici Jenga l'a compensé. Devant une erreur de liens, le premier réflexe est de regarder l'ordre de construction : s'il manque un projet, c'est `dependson`.