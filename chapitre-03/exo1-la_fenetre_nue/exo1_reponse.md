# Exercice 1 : La fenêtre nue

J'ai écrit le plus petit programme qui ouvre une fenêtre Nkentseu, la garde ouverte, et tente de se terminer proprement, dans `Applications/LaFenetreNue`.

## Le programme (28 lignes)

```cpp
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "La fenetre nue";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsValid()) {
        logger.Error("[LaFenetreNue] Creation fenetre KO");
        return 1;
    }

    while (window.IsOpen()) {
        NkEvents().PollEvents();
    }

    window.Close();
    return 0;
}
```

## Chaque ligne retrouvée dans le chapitre

| Lignes | Ce que ça fait | D'où ça vient |
|---|---|---|
| 1 | `NKMain.h` | Fournit le point d'entrée natif (`WinMain`, etc.). Sans lui : `undefined reference to WinMain`. |
| 2-3 | `NkWindow.h`, `NkWindowConfig.h` | La classe fenêtre et sa configuration. |
| 4 | `NkLog.h` | Pour `logger.Error(...)`. |
| 6 | `using namespace nkentseu` | Tout le module vit dans ce namespace. |
| 8 | `int nkmain(const NkEntryState &state)` | On n'écrit pas `main`, mais `nkmain` — le chapitre insiste là-dessus. |
| 11-14 | `NkWindowConfig cfg` + `title`/`width`/`height` | La configuration se donne au constructeur, par familles (ici : identité et taille). |
| 16 | `NkWindow window(cfg)` | La fenêtre est créée dès la construction de l'objet. |
| 17-20 | `if (!window.IsValid())` | Vérifier que la création n'a pas échoué. |
| 22-24 | `while (window.IsOpen()) { NkEvents().PollEvents(); }` | La boucle qui garde la fenêtre ouverte ; c'est là que les événements arriveraient. |
| 26-27 | `window.Close()`, `return 0` | Fin propre voulue. |

## Un écart avec le résumé du sprint

Le résumé du cours utilise `window.IsOpen()` pour vérifier la création, mais le vrai tutoriel du dépôt (`Tutoriels3D/01-Fenetre/main.cpp`) utilise `window.IsValid()`. J'ai suivi le vrai code, qui compile.

## Compiler ce programme minimal n'a pas suffi

`NKWindow` seul (`nkentseudependson(["NKWindow"])`) a permis de tout compiler, y compris `NKWindow.a`. Mais l'édition de liens a échoué : `référence indéfinie vers « nkentseu::NkChrono::Now() »` et `BeginPreciseTiming()`, des fonctions de `NKTime` appelées en cascade par `NKEvent` et `NKWindow`. J'ai dû ajouter explicitement `NKEvent` et `NKTime` dans `includedirs`, `links` et `dependson` de `LaFenetreNue.jenga` pour que ça compile et se lie. `MonEssai`/`MonLib` à l'exercice 6 n'avait pas eu ce problème : c'est la première fois que `nkentseudependson` seul ne suffisait pas.

## Ce que j'ai observé en le lançant

```bash
$ ./Build/Bin/Debug-Linux/LaFenetreNue/LaFenetreNue
```

Une fenêtre noire de 1280×720, intitulée « La fenetre nue », s'est ouverte normalement. En revanche, **cliquer sur la croix ne l'a pas fermée** : le processus est resté actif et j'ai dû le tuer depuis un autre terminal avec `pkill -f LaFenetreNue`.

```bash
$ ps aux | grep LaFenetreNue
tapa-fo+ ... grep --color=auto LaFenetreNue
```
