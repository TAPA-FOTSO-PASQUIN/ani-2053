# Exercice 3 : Les bornes

J'ai fixé une taille minimale sur une fenêtre (`minWidth = 400`, `minHeight = 300`), puis je l'ai réduite au maximum en tirant les bords. J'ai retiré ces deux lignes, recompilé, et recommencé pour observer les valeurs par défaut du moteur.

## Premier essai : `minWidth = 400`, `minHeight = 300`

```cpp
NkWindowConfig cfg;
cfg.width = 800;
cfg.height = 600;
cfg.resizable = true;
cfg.minWidth = 400;
cfg.minHeight = 300;
```

En réduisant la largeur, les logs (`NkWindowResizeEvent`) montrent une diminution progressive : 800 → 798 → 772 → ... → 412 → **400**, puis plus aucune valeur en dessous, quels que soient mes essais de tirer davantage.

En réduisant ensuite la hauteur : 600 → 598 → 538 → ... → 312 → **300**, puis arrêt net.

**Plus petite taille atteinte : 400×300**, exactement les valeurs fixées dans le code.

## Deuxième essai : sans `minWidth`/`minHeight`

J'ai retiré ces deux lignes et reconstruit. Le programme utilise alors les valeurs par défaut de `NkWindowConfig.h` :

```bash
$ grep -n -i "minwidth\|minheight" Kernel/Runtime/NKWindow/src/NKWindow/Core/NkWindowConfig.h
73:  uint32 minWidth = 160;
74:  uint32 minHeight = 90;
```

En réduisant la largeur : 800 → 798 → 768 → ... → 174 → 166 → **160**, puis arrêt net.

En réduisant la hauteur : 600 → 598 → 568 → ... → 108 → **90**, puis arrêt net.

**Plus petite taille atteinte : 160×90**, exactement les valeurs par défaut lues dans le code.

## Tableau récapitulatif

| Essai | Valeur demandée | Plus petite taille observée |
|---|---|---|
| `minWidth`/`minHeight` fixés | 400 × 300 | 400 × 300 |
| Valeurs par défaut (non fixées) | 160 × 90 (par défaut) | 160 × 90 |

