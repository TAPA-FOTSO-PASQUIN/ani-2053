# Exercice 8 : Six manières de défaire

J'ai travaillé dans un dépôt `travail`, cloné depuis un serveur nu `serveur.git`. Le commit de départ est `30dbdba` (`jeu.txt` contient `vitesse: 180`).

## 1. Une modification non voulue : `git restore`

J'ai écrasé `jeu.txt` par erreur, puis j'ai annulé la modification. Elle n'était pas validée, donc elle est perdue pour de bon.

```bash
$ echo "vitesse: 9999" > jeu.txt
$ git diff
-vitesse: 180
+vitesse: 9999
$ git restore jeu.txt
$ cat jeu.txt
vitesse: 180
$ git status
rien à valider, la copie de travail est propre
```

## 2. Un `add` de trop : `git restore --staged`

J'ai ajouté `notes2.txt` à l'index alors qu'il ne devait pas partir dans le commit, puis je l'ai retiré de l'index. Le fichier existe toujours, seul le `add` est défait.

```bash
$ git add notes2.txt
$ git status
Modifications qui seront validées :
	nouveau fichier : notes2.txt
$ git restore --staged notes2.txt
$ git status
Fichiers non suivis:
	notes2.txt
```

## 3. Un commit de trop, non poussé : `git reset --soft`

J'ai fait le commit `4f2002f` et je l'ai retiré. Les modifications restent dans l'index, donc rien n'est perdu.

```bash
$ git log --oneline
4f2002f (HEAD -> master) Passer la vitesse à 250
30dbdba (origin/master) Ajouter jeu.txt
$ git reset --soft HEAD~1
$ git log --oneline
30dbdba (HEAD -> master, origin/master) Ajouter jeu.txt
$ git status
Modifications qui seront validées :
	modifié :         jeu.txt
$ cat jeu.txt
vitesse: 250
```

## 4. Un commit poussé à annuler : `git revert`

J'ai poussé un commit fautif (`2c3f619`). Comme il est partagé, je ne réécris pas l'historique : j'ajoute un commit qui fait l'inverse.

```bash
$ git push
   30dbdba..2c3f619  master -> master
$ git revert --no-edit HEAD
[master 6c14aa7] Revert "Passer la vitesse à 9999"
$ cat jeu.txt
vitesse: 180
$ git log --oneline
6c14aa7 (HEAD -> master) Revert "Passer la vitesse à 9999"
2c3f619 (origin/master) Passer la vitesse à 9999
30dbdba Ajouter jeu.txt
$ git push
   2c3f619..6c14aa7  master -> master
```

Le commit fautif reste visible dans l'historique, et c'est voulu.

## 5. Un travail en cours à mettre de côté : `git stash`

```bash
$ echo "vitesse: 220" > jeu.txt
$ git stash
Arbre de travail et état de l'index sauvegardés dans WIP on master: 6c14aa7 Revert "Passer la vitesse à 9999"
$ cat jeu.txt
vitesse: 180
$ git stash list
stash@{0}: WIP on master: 6c14aa7 Revert "Passer la vitesse à 9999"
$ git stash pop
refs/stash@{0} supprimé (ee56101944fde0f007f30c94bf3fb69fc039412b)
$ cat jeu.txt
vitesse: 220
```

Pendant que le travail était rangé, la copie de travail était propre. Après `pop`, mon travail est revenu et la pile est vide.

## 6. Un commit « perdu » retrouvé par le `reflog`

J'ai fait un commit non poussé (`751b9d2`), puis je l'ai « perdu » avec `git reset --hard`.

```bash
$ git commit -m "Passer la vitesse à 500" -m "Commit qui sera perdu puis retrouvé avec reflog."
[master 751b9d2] Passer la vitesse à 500
$ git reset --hard HEAD~1
HEAD est maintenant à 6c14aa7 Revert "Passer la vitesse à 9999"
$ git log --oneline
6c14aa7 (HEAD -> master, origin/master) Revert "Passer la vitesse à 9999"
2c3f619 Passer la vitesse à 9999
30dbdba Ajouter jeu.txt
```

Le commit a disparu du `git log`, mais le `reflog` l'a gardé :

```bash
$ git reflog
6c14aa7 (HEAD -> master, origin/master) HEAD@{0}: reset: moving to HEAD~1
751b9d2 HEAD@{1}: commit: Passer la vitesse à 500
[...]
```

Je l'ai retrouvé avec son empreinte :

```bash
$ git reset --hard 751b9d2
HEAD est maintenant à 751b9d2 Passer la vitesse à 500
$ git log --oneline
751b9d2 (HEAD -> master) Passer la vitesse à 500
6c14aa7 (origin/master) Revert "Passer la vitesse à 9999"
$ cat jeu.txt
vitesse: 500
```

Ensuite j'ai remis la branche sur le serveur avec `git reset --hard origin/master`.

Une erreur en chemin : j'avais tapé `git reset --hard <empreinte>` tel quel, et bash a répondu `erreur de syntaxe près du symbole inattendu « newline »`, car `<` et `>` sont des redirections. Il faut écrire l'empreinte réelle.
