# Démo 1 : Le graphe au tableau

J'ai pris un dépôt réel de mes exercices (l'exercice 7 : un serveur et deux clones, `pasquin` et `audrey`). Il contient une divergence et une fusion. Faute de tableau, j'ai fait le dessin en texte, puis je l'ai comparé à `git log --graph`.

## Le graphe donné par Git

```bash
$ git log --oneline --graph --all
*   40fa8eb (HEAD -> master, origin/master, origin/HEAD) Merge branch 'master' of /home/tapa-fotso-pasquin/Bureau/exo7/serveur
|\
| * 9f803ef Renommer le projet en « mon projet de jeu »
* | f4e6f98 Passer la vitesse de 180 à 250
|/
* bb8931b Ajouter jeu.txt
```

## Mon dessin

```
        40fa8eb  (fusion, 2 parents)   <- HEAD, origin/master
        /      \
       v        v
  f4e6f98      9f803ef
  (audrey)     (pasquin)
       \        /
        v      v
        bb8931b  (divergence : point de départ)
```

Chaque flèche va d'un commit vers son parent.

## La correspondance

- **Un rond du dessin** correspond à une ligne de `git log --graph` qui commence par `*`.
- **Le point de divergence** est `bb8931b`, la ligne du bas, juste sous `|/`. À partir de lui, `pasquin` (`9f803ef`) et `audrey` (`f4e6f98`) ont chacun avancé de leur côté : il a deux enfants.
- **Les deux branches** sont les deux colonnes du graphe : `f4e6f98` à gauche, `9f803ef` à droite (`| *`).
- **La fusion** est `40fa8eb`, la ligne du haut, suivie de `|\` qui ouvre les deux chemins qu'elle réunit : c'est le seul commit à deux parents.

