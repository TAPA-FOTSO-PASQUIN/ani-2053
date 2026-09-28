# Exercice 2 : Les sept droits

J'ai créé sept fenêtres, chacune avec un seul droit de `NkWindowConfig` désactivé, dans `Applications/LesSeptDroits`. J'ai d'abord cherché chaque champ dans le code du backend Linux/XLib (`NkXLibWindow.cpp`), puis vérifié à l'œil ce qui se passait réellement.

## Recherche dans le code

```bash
$ grep -n "\.frame\|resizable\|minimizable\|movable\|closable\|maximizable\|canFullscreen" Kernel/Runtime/NKWindow/src/NKWindow/Platform/XLib/NkXLibWindow.cpp
338:  // ── Fenetre SANS bordure (config.frame == false) ─────────────────────
340:  // config.frame etait purement IGNORE ici : le gestionnaire de fenetres
350:  SetDecorated(config.frame);
372:  // Size constraints : non-resizable -> taille fixe ; resizable -> taille MINI.
375:  if (!config.resizable) {

$ grep -rn "minimizable\|movable\|closable\|maximizable\|canFullscreen" Kernel/Runtime/NKWindow/src --include=*.cpp --include=*.h | grep -v "NkWindowConfig.h"
(aucun résultat)
```

Seuls `frame` et `resizable` sont lus par du code, dans ce seul fichier. Les cinq autres droits (`minimizable`, `movable`, `closable`, `maximizable`, `canFullscreen`) n'apparaissent nulle part ailleurs que dans leur déclaration (`NkWindowConfig.h`). Aucun code du module ne les lit : c'est une réponse complète, pas un échec de ma recherche.

## Le tableau

| Droit | Effet attendu | Effet observé |
|---|---|---|
| `frame` | Pas de bordure ni barre de titre système | Confirmé : fenêtre nue, sans aucune bordure ni barre de titre |
| `resizable` | Taille fixe, bords non redimensionnables | Confirmé : en tirant un coin ou un bord, la taille ne bouge pas |
| `minimizable` | Sans effet, car aucun code ne lit ce champ | Fenêtre identique aux autres, bouton réduire présent et normal |
| `movable` | Sans effet, car aucun code ne lit ce champ | Fenêtre identique aux autres |
| `closable` | Sans effet, car aucun code ne lit ce champ | Fermée normalement par la croix, comme les autres |
| `maximizable` | Sans effet, car aucun code ne lit ce champ | Fenêtre identique aux autres |
| `canFullscreen` | Sans effet, car aucun code ne lit ce champ | Fenêtre identique aux autres |

## Explication des écarts

Deux droits sur sept ont un effet réel sur Linux/XLib :

- **`frame`** : ligne 350, `SetDecorated(config.frame)` transmet directement la valeur au gestionnaire de fenêtres X11, qui retire la décoration système. Le commentaire ligne 340 précise même qu'avant une correction, ce champ était « purement IGNORE ».
- **`resizable`** : ligne 375, `if (!config.resizable)` impose une contrainte de taille (le commentaire ligne 372 dit qu'une fenêtre non redimensionnable reçoit une taille fixe, alors qu'une fenêtre redimensionnable reçoit seulement une taille minimale).

Les cinq autres droits n'ont aucune ligne qui les lit dans tout le dossier `NKWindow/src`. C'est cohérent avec ce que j'ai observé : les fenêtres 3 à 7 se comportaient toutes comme des fenêtres ordinaires, avec leurs boutons système habituels (réduire, agrandir, fermer) pleinement fonctionnels, quelle que soit la valeur que je leur avais donnée. Le gestionnaire de fenêtres de mon bureau décide seul de ces comportements, sans jamais consulter la configuration demandée par le programme.
