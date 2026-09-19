# Exercice 4 : Le commit partiel

Dans mon dépôt d'essai `git-exo`, j'ai modifié deux choses sans rapport dans `fichier4.txt` : le titre (première ligne) et la vitesse (dernière ligne). Dix lignes les séparent, pour que Git les voie comme deux morceaux distincts.

## Le diff avant de séparer

```bash
$ git diff
diff --git a/fichier4.txt b/fichier4.txt
index 16d5f06..9dcdbb5 100644
--- a/fichier4.txt
+++ b/fichier4.txt
@@ -1,4 +1,4 @@
-titre: mon projet
+titre: mon projet de jeu
 ligne 1
 ligne 2
 ligne 3
@@ -9,4 +9,4 @@ ligne 7
 ligne 8
 ligne 9
 ligne 10
-vitesse: 180
+vitesse: 250
```

Il y a bien deux morceaux (deux lignes `@@`), un par sujet.

## Premier commit : le titre seulement

J'ai lancé `git add -p fichier4.txt`. J'ai répondu `y` au premier morceau (le titre) et `n` au second (la vitesse).

```bash
$ git status
Sur la branche master
Modifications qui seront validées :
	modifié :         fichier4.txt

Modifications qui ne seront pas validées :
	modifié :         fichier4.txt

$ git diff --staged
diff --git a/fichier4.txt b/fichier4.txt
index 16d5f06..09bf405 100644
--- a/fichier4.txt
+++ b/fichier4.txt
@@ -1,4 +1,4 @@
-titre: mon projet
+titre: mon projet de jeu
 ligne 1
 ligne 2
 ligne 3
```

Le même fichier apparaît à deux endroits : la moitié « titre » est dans l'index, la moitié « vitesse » est encore dans le répertoire de travail.

```bash
$ git commit -m "Renommer le projet en « mon projet de jeu »" -m "Le titre ne disait pas qu'il s'agit d'un jeu."
[master d90b822] Renommer le projet en « mon projet de jeu »
 1 file changed, 1 insertion(+), 1 deletion(-)
```

## Second commit : la vitesse

J'ai relancé `git add -p fichier4.txt` et répondu `y` au seul morceau restant.

```bash
$ git diff --staged
diff --git a/fichier4.txt b/fichier4.txt
index 09bf405..9dcdbb5 100644
--- a/fichier4.txt
+++ b/fichier4.txt
@@ -9,4 +9,4 @@ ligne 7
 ligne 8
 ligne 9
 ligne 10
-vitesse: 180
+vitesse: 250

$ git commit -m "Passer la vitesse de 180 à 250" -m "La vitesse de 180 rendait le personnage trop lent."
[master aea9b26] Passer la vitesse de 180 à 250
 1 file changed, 1 insertion(+), 1 deletion(-)

$ git status
Sur la branche master
rien à valider, la copie de travail est propre
```

## Vérification dans l'historique

```bash
$ git log --oneline
aea9b26 (HEAD -> master) Passer la vitesse de 180 à 250
d90b822 Renommer le projet en « mon projet de jeu »
5d34d46 Ajouter fichier4.txt
8fd0241 modification du fichier1.txt
e6b538e ajout du fichier3.txt
26cf23a ajout du fichier2.txt
861c8b4 ajout du fichier1.txt
```

```bash
$ git show HEAD~1
commit d90b82257ba3a9dd97b1982d96bd25c9ba6641a1

    Renommer le projet en « mon projet de jeu »

    Le titre ne disait pas qu'il s'agit d'un jeu.

@@ -1,4 +1,4 @@
-titre: mon projet
+titre: mon projet de jeu
```

Ce commit ne contient que le changement du titre.

```bash
$ git show HEAD
commit aea9b264b2b94b0863e752a9d24fce580969b822

    Passer la vitesse de 180 à 250

    La vitesse de 180 rendait le personnage trop lent.

@@ -9,4 +9,4 @@ ligne 7
-vitesse: 180
+vitesse: 250
```

Ce commit ne contient que le changement de la vitesse.

## Ce que j'ai compris

Deux modifications sans rapport dans un même fichier n'ont pas besoin d'être validées ensemble. Avec `git add -p`, je choisis morceau par morceau ce qui entre dans l'index, donc je peux faire deux commits, chacun avec un seul sujet et son propre message. Si la vitesse pose un problème plus tard, je peux annuler ce commit seul avec `git revert`, sans toucher au changement de titre.