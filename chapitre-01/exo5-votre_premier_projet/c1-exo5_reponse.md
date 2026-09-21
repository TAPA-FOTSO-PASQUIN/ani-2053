# Exercice 5 : Votre premier projet

J'ai créé `Applications/MonEssai` dans le dépôt Nkentseu : un `main.cpp` qui n'affiche rien, un `MonEssai.jenga`, et la déclaration dans le workspace `Nkentseu.jenga`. Le dossier `MonEssai` existait déjà mais son `.jenga` était vide et `main.cpp` manquait, donc je les ai écrits.

## 1. Le programme

```bash
$ cat Applications/MonEssai/src/main.cpp
int main()
{
    return 0;
}
```

## 2. Le fichier de projet

```bash
$ cat Applications/MonEssai/MonEssai.jenga
from Jenga import *
from jengaconfig import *

with project("MonEssai"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")

    files(["src/**.cpp"])

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

    with filter("config:Debug"):
        defines(["_DEBUG"])
        optimize("Off")
        symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed")
        symbols(False)
```

J'ai choisi `consoleapp()` car le programme n'affiche rien et n'a pas besoin de fenêtre. Il n'a aucune dépendance, donc ni `dependson` ni `links`.

## 3. Je le déclare au workspace

Sans cette ligne, Jenga ne voit pas le projet. Je l'ai insérée à la ligne 899 de `Nkentseu.jenga`, entre `NkAudioDemo` et `NkCameraDemos`.

```bash
$ grep -n "MonEssai" Nkentseu.jenga
899:    with include("Applications/MonEssai/MonEssai.jenga"):
$ git diff --stat Nkentseu.jenga
 Nkentseu.jenga | 4 ++++
 1 file changed, 4 insertions(+)
```

## 4. Il apparaît dans `jenga info`

```bash
$ jenga info | grep -n "MonEssai"
144:MonEssai                     ConsoleApp    C++        No     Yes
```

## 5. Je le construis

```bash
$ jenga build --project MonEssai --config Debug
Build Order (1 projects):
  1. MonEssai [CONSOLE_APP]
ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build/Bin/Debug-Linux/MonEssai/MonEssai
Projects Built:  1/1
Time:           0.13s
Status:         ✓ SUCCESS
```

L'ordre de construction ne contient qu'un projet, car `MonEssai` ne dépend de rien.

## 6. Je le lance

```bash
$ ./Build/Bin/Debug-Linux/MonEssai/MonEssai
$ echo "code de sortie : $?"
code de sortie : 0
```

Le programme n'affiche rien et se termine avec le code 0.

## Ce qui n'a pas marché

`jenga run --project MonEssai` a échoué : `jenga run` n'accepte pas `--project`, le nom du projet se donne sans option (contrairement à `build`, comme l'indique le chapitre). Avec `jenga run MonEssai --config Debug`, Jenga a cherché un `.exe` Windows (`Build/Bin/Debug-Windows/...`) au lieu du binaire Linux. J'ai donc lancé le binaire directement.

## Ce que j'ai compris

Un projet n'existe pour Jenga que s'il est déclaré dans le workspace avec `include(...)` : sans cela, il est absent de `jenga info`, sans aucune erreur. Le nom du dossier de sortie (`Debug-Linux`) vient de `%{cfg.buildcfg}-%{cfg.system}` dans `targetdir`.