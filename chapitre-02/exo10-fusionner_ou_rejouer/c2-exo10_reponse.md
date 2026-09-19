# Exercice 10 : Fusionner ou rejouer

Dans un dépôt local, j'ai créé `feature` (2 commits : `menu.txt`, `options.txt`) et fait avancer `master` de 2 commits (`niveau1.txt`, `niveau2.txt`). Les deux branches partent de `685baae` et touchent des fichiers différents, donc sans conflit. J'ai fait la même intégration deux fois, chacune sur sa branche : `integration-merge` (fusion) et `feature-copie` (rejeu).

## Départ

```bash
$ git log --oneline --graph --all
* 35493a7 (HEAD -> master) Ajouter niveau2.txt
* 3182786 Ajouter niveau1.txt
| * 65f8c05 (feature) Ajouter options.txt
| * 9851a65 Ajouter menu.txt
|/
* 685baae Ajouter jeu.txt
```

## Première intégration : la fusion

```bash
$ git switch -c integration-merge master
$ git merge --no-edit feature
Merge made by the 'ort' strategy.
 menu.txt    | 1 +
 options.txt | 1 +
 2 files changed, 2 insertions(+)
$ git log --oneline --graph --all
*   dc9107e (HEAD -> integration-merge) Merge branch 'feature' into integration-merge
|\
| * 65f8c05 (feature-copie, feature) Ajouter options.txt
| * 9851a65 Ajouter menu.txt
* | 35493a7 (master) Ajouter niveau2.txt
* | 3182786 Ajouter niveau1.txt
|/
* 685baae Ajouter jeu.txt
```

## Deuxième intégration : le rejeu

```bash
$ git switch feature-copie
$ git rebase master
Rebasage et mise à jour de refs/heads/feature-copie avec succès.
$ git log --oneline --graph feature-copie
(coller ici la sortie)
```

## Comparaison

- **Fusion** : le graphe garde les deux chemins et ajoute `dc9107e`, qui a deux parents. Mes commits gardent leurs empreintes (`9851a65`, `65f8c05`).
- **Rejeu** : le graphe est une ligne droite, sans commit de fusion. Mes deux commits ont de nouvelles empreintes (`babdae8`, `9b2d55a`), donc ce sont d'autres commits, même s'ils contiennent les mêmes changements.
- **Résultat** : `git diff integration-merge feature-copie` n'affiche rien. Les fichiers sont identiques, seule l'histoire diffère.

## Ma préférence

Je préfère lire le graphe du **rejeu**, parce qu'il se lit de haut en bas comme une liste : chaque commit vient après le précédent, sans avoir à suivre deux chemins. Mais je ne l'utiliserais que sur mes propres commits, pas encore partagés : le chapitre 2 interdit de rejouer des commits que quelqu'un d'autre a déjà récupérés, car leurs empreintes changent. Pour du travail partagé, la fusion est la seule sans danger, même si son graphe est plus long à lire.