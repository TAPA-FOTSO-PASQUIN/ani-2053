# Démo 3 : Ce que le reflog sauve

Dans un dépôt neuf `demo3`, j'ai fait un travail de trois commits (`niveau1.txt`, `niveau2.txt`, `niveau3.txt`) au-dessus du commit de départ `4395887`. Rien n'est poussé. Je l'ai détruit avec `reset --hard`, j'ai constaté la perte, puis je l'ai retrouvé avec le `reflog`.

## 1. Le travail avant la destruction

```bash
$ git log --oneline
222a48e (HEAD -> master) Ajouter niveau3.txt
a68cd2c Ajouter niveau2.txt
1070e9f Ajouter niveau1.txt
4395887 Ajouter jeu.txt
$ ls
jeu.txt  niveau1.txt  niveau2.txt  niveau3.txt
```

## 2. Je détruis le travail

```bash
$ git reset --hard 4395887
HEAD est maintenant à 4395887 Ajouter jeu.txt
$ git log --oneline
4395887 (HEAD -> master) Ajouter jeu.txt
$ ls
jeu.txt
$ git status
rien à valider, la copie de travail est propre
```

La perte est constatée : mes trois commits ont disparu de `git log`, et mes trois fichiers ont disparu du dossier. Git ne signale rien.

## 3. Je le retrouve avec le reflog

```bash
$ git reflog
4395887 (HEAD -> master) HEAD@{0}: reset: moving to 4395887
222a48e HEAD@{1}: commit: Ajouter niveau3.txt
a68cd2c HEAD@{2}: commit: Ajouter niveau2.txt
1070e9f HEAD@{3}: commit: Ajouter niveau1.txt
4395887 (HEAD -> master) HEAD@{4}: commit (initial): Ajouter jeu.txt
```

Le reflog garde les endroits où `HEAD` est passé. La ligne `HEAD@{1}` donne l'empreinte du dernier commit perdu : `222a48e`.

```bash
$ git reset --hard 222a48e
HEAD est maintenant à 222a48e Ajouter niveau3.txt
$ git log --oneline
222a48e (HEAD -> master) Ajouter niveau3.txt
a68cd2c Ajouter niveau2.txt
1070e9f Ajouter niveau1.txt
4395887 Ajouter jeu.txt
$ ls
jeu.txt  niveau1.txt  niveau2.txt  niveau3.txt
$ cat niveau3.txt
niveau 3
```
