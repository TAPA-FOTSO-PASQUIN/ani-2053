# Démo 2 : Le conflit résolu en direct

J'ai préparé la scène avant : un serveur `serveur.git` et deux clones, `pasquin` et `audrey`, avec un fichier `jeu.txt` contenant `vitesse: 180` (commit `f4ae763`). Puis j'ai provoqué un conflit et je l'ai résolu en suivant toujours le même ordre : lire, décider, reconstruire, vérifier, valider.

## 1. Je provoque le conflit

`pasquin` change la vitesse en 250 et pousse. `audrey` la change en 300 et essaie de pousser : le serveur refuse.

```bash
# pasquin
$ git push
   f4ae763..ceb5584  master -> master

# audrey
$ git push
 ! [rejected]        master -> master (fetch first)
error: impossible de pousser des références vers '.../demo2/serveur.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. [...]
```

Je ne force pas : je rapatrie et j'intègre.

```bash
$ git pull --no-rebase
Fusion automatique de jeu.txt
CONFLIT (contenu) : Conflit de fusion dans jeu.txt
La fusion automatique a échoué ; réglez les conflits et validez le résultat.
$ git status
Chemins non fusionnés :
	modifié des deux côtés :  jeu.txt
```

## 2. Je lis les marqueurs

```bash
$ cat jeu.txt
<<<<<<< HEAD
vitesse: 300
=======
vitesse: 250
>>>>>>> ceb55849d9dd3387683c516fda2cdabe396faf8f
```

Entre `<<<<<<< HEAD` et `=======`, c'est ma version (300). Entre `=======` et `>>>>>>>`, c'est celle qui arrive (250).

## 3. Je décide

Je ne colle pas les deux : je choisis une valeur. Je retiens 275, entre les deux.

## 4. Je reconstruis et je vérifie

J'écris le fichier entier d'un coup, ce qui efface les trois marqueurs, puis je vérifie avec `grep`.

```bash
$ echo "vitesse: 275" > jeu.txt
$ cat jeu.txt
vitesse: 275
$ grep -n '<<<<<<<\|=======\|>>>>>>>' jeu.txt
(aucun résultat)
```

## 5. Je valide, je pousse, je contrôle

```bash
$ git add jeu.txt
$ git status
Tous les conflits sont réglés mais la fusion n'est pas terminée.
$ git commit -m "Fusionner les vitesses de pasquin et d'audrey" -m "250 et 300 étaient en conflit ; on retient 275, entre les deux."
[master 2708c36] Fusionner les vitesses de pasquin et d'audrey
$ git push
   ceb5584..2708c36  master -> master
$ git log --oneline --graph --all
*   2708c36 (HEAD -> master, origin/master, origin/HEAD) Fusionner les vitesses de pasquin et d'audrey
|\
| * ceb5584 Passer la vitesse à 250
* | 7a51089 Passer la vitesse à 300
|/
* f4ae763 Ajouter jeu.txt
```
