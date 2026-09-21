# Exercice 7 : Le conflit qui n'en est pas un

J'ai créé un serveur `serveur.git` et deux clones, `pasquin` et `audrey`, comme à l'exercice 6. Cette fois, j'ai modifié deux endroits éloignés du même fichier : la ligne 1 dans `pasquin` (le titre), et la dernière ligne dans `audrey` (la vitesse), séparées par dix lignes.

## 1. Le fichier de départ

Dans `pasquin`, j'ai créé `jeu.txt` (12 lignes), je l'ai validé, puis poussé. Ensuite, `audrey` l'a récupéré avec `git pull`.

```bash
$ git commit -m "Ajouter jeu.txt" -m "Fichier de départ : un titre, dix lignes, une vitesse."
[master (commit racine) bb8931b] Ajouter jeu.txt
 1 file changed, 12 insertions(+)
$ git push -u origin master
 * [new branch]      master -> master
```

## 2. Mes deux modifications

Dans `audrey`, j'ai changé la vitesse de 180 à 250 et j'ai validé sans pousser.

```bash
$ git diff
@@ -9,4 +9,4 @@ ligne 7
-vitesse: 180
+vitesse: 250
$ git commit -m "Passer la vitesse de 180 à 250" -m "La vitesse de 180 rendait le personnage trop lent."
[master f4e6f98] Passer la vitesse de 180 à 250
```

Dans `pasquin`, j'ai changé le titre et j'ai validé, toujours sans pousser.

```bash
$ git show HEAD
9f803ef Renommer le projet en « mon projet de jeu »
@@ -1,4 +1,4 @@
-titre: mon projet
+titre: mon projet de jeu
```

Mes deux changements sont dans deux morceaux différents (`@@ -1,4` et `@@ -9,4`).

## 3. J'ai poussé depuis pasquin, puis depuis audrey

Depuis `pasquin`, mon `git push` est passé. Depuis `audrey`, il a été refusé, car le serveur avait un commit que `audrey` n'avait pas. Je n'ai pas utilisé `--force`.

```bash
# pasquin
$ git push
   bb8931b..9f803ef  master -> master

# audrey
$ git push
 ! [rejected]        master -> master (fetch first)
error: impossible de pousser des références vers '.../exo7/serveur.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. [...]
```

## 4. Git a tout assemblé sans rien me demander

Dans `audrey`, j'ai fait `git fetch`, puis `git pull`. Aucun `CONFLIT` n'est apparu. Git a fusionné seul et créé un commit de fusion à deux parents.

```bash
$ git fetch
   bb8931b..9f803ef  master     -> origin/master
$ git pull --no-rebase --no-edit
Fusion automatique de jeu.txt
Merge made by the 'ort' strategy.
 jeu.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
$ cat jeu.txt
titre: mon projet de jeu
ligne 1
[...]
ligne 10
vitesse: 250
$ git log --oneline --graph --all
*   40fa8eb (HEAD -> master) Merge branch 'master' of .../exo7/serveur
|\
| * 9f803ef (origin/master, origin/HEAD) Renommer le projet en « mon projet de jeu »
* | f4e6f98 Passer la vitesse de 180 à 250
|/
* bb8931b Ajouter jeu.txt
```

## 5. J'ai vérifié le résultat

J'ai poussé la fusion depuis `audrey`, puis je l'ai récupérée dans `pasquin`, sans aucun conflit. J'ai ensuite comparé le point de départ au résultat.

```bash
# audrey
$ git push
   9f803ef..40fa8eb  master -> master

# pasquin
$ git pull
Fast-forward
 jeu.txt | 2 +-
$ git diff bb8931b HEAD
@@ -1,4 +1,4 @@
-titre: mon projet
+titre: mon projet de jeu
@@ -9,4 +9,4 @@ ligne 7
-vitesse: 180
+vitesse: 250
```

Le diff montre exactement mes deux changements, et rien d'autre.

