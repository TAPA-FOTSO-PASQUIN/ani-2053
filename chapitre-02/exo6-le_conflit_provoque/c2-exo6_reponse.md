# Exercice 6 : Le conflit provoqué

Pour reproduire un travail à deux, j'ai créé un dépôt « nu » `serveur.git` (qui joue le rôle de GitHub, sur mon disque) et deux clones : `pasquin` et `audrey`. Ils modifient la même ligne d'un même fichier, `jeu.txt`. J'ai gardé tous les messages affichés.

## 1. Le serveur et les deux clones

```bash
$ mkdir ~/Bureau/exo6
$ cd ~/Bureau/exo6
$ git init --bare serveur.git
hint: Using 'master' as the name for the initial branch. This default branch name
hint: will change to "main" in Git 3.0. [...]
Dépôt Git vide initialisé dans /home/tapa-fotso-pasquin/Bureau/exo6/serveur.git/

$ git clone serveur.git pasquin
$ git clone serveur.git audrey
Clonage dans 'pasquin'...
warning: Vous semblez avoir cloné un dépôt vide.
fait.
Clonage dans 'audrey'...
warning: Vous semblez avoir cloné un dépôt vide.
fait.

$ ls
audrey  pasquin  serveur.git
```

## 2. Le fichier de départ

Dans `pasquin` :

```bash
$ echo "vitesse: 180" > jeu.txt
$ git add jeu.txt
$ git commit -m "Ajouter jeu.txt" -m "Fichier de départ avec la vitesse du personnage."
[master (commit racine) ef14ef9] Ajouter jeu.txt
 1 file changed, 1 insertion(+)
 create mode 100644 jeu.txt

$ git push -u origin master
Énumération des objets: 3, fait.
Décompte des objets: 100% (3/3), fait.
Écriture des objets: 100% (3/3), 267 octet | 267.00 KiB/s, fait.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To /home/tapa-fotso-pasquin/Bureau/exo6/serveur.git
 * [new branch]      master -> master
la branche 'master' est paramétrée pour suivre 'origin/master'.
```

Dans `audrey` (avec une identité propre, `git config user.name "Audrey"`) :

```bash
$ git pull origin master
remote: Énumération des objets: 3, fait.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Dépaquetage des objets: 100% (3/3), 247 octet | 247.00 KiB/s, fait.
Depuis /home/tapa-fotso-pasquin/Bureau/exo6/serveur
 * branch            master     -> FETCH_HEAD
 * [nouvelle branche] master     -> origin/master

$ cat jeu.txt
vitesse: 180
```

## 3. Deux modifications de la même ligne

```bash
# dans pasquin
$ sed -i 's/vitesse: 180/vitesse: 250/' jeu.txt
$ cat jeu.txt
vitesse: 250
$ git add jeu.txt
$ git commit -m "Passer la vitesse à 250" -m "Pasquin veut un personnage plus rapide."
[master e31dc7d] Passer la vitesse à 250
 1 file changed, 1 insertion(+), 1 deletion(-)

# dans audrey
$ sed -i 's/vitesse: 180/vitesse: 300/' jeu.txt
$ cat jeu.txt
vitesse: 300
$ git add jeu.txt
$ git commit -m "Passer la vitesse à 300" -m "Audrey veut un personnage encore plus rapide."
[master dfdc8fd] Passer la vitesse à 300
 1 file changed, 1 insertion(+), 1 deletion(-)

$ git log --oneline
dfdc8fd (HEAD -> master) Passer la vitesse à 300
ef14ef9 (origin/master) Ajouter jeu.txt
```

Le serveur ne connaît encore que `ef14ef9` : les deux ont travaillé en même temps sur la même ligne.

## 4. Pasquin pousse, audrey est refusée

```bash
# dans pasquin
$ git push
Énumération des objets: 5, fait.
Décompte des objets: 100% (5/5), fait.
Écriture des objets: 100% (3/3), 293 octet | 293.00 KiB/s, fait.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To /home/tapa-fotso-pasquin/Bureau/exo6/serveur.git
   ef14ef9..e31dc7d  master -> master

# dans audrey
$ git push
To /home/tapa-fotso-pasquin/Bureau/exo6/serveur.git
 ! [rejected]        master -> master (fetch first)
error: impossible de pousser des références vers '/home/tapa-fotso-pasquin/Bureau/exo6/serveur.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

Le refus veut dire que le serveur a un commit qu'audrey n'a pas. Je n'ai pas utilisé `git push --force`, qui aurait écrasé le travail de pasquin. La réponse est : rapatrier, intégrer, repousser.

## 5. Rapatrier, puis le conflit

```bash
$ git fetch
remote: Énumération des objets: 5, fait.
remote: Décompte des objets: 100% (5/5), fait.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Dépaquetage des objets: 100% (3/3), 273 octet | 273.00 KiB/s, fait.
Depuis /home/tapa-fotso-pasquin/Bureau/exo6/serveur
   ef14ef9..e31dc7d  master     -> origin/master

$ git log --oneline --graph --all
* dfdc8fd (HEAD -> master) Passer la vitesse à 300
| * e31dc7d (origin/master, origin/HEAD) Passer la vitesse à 250
|/  
* ef14ef9 Ajouter jeu.txt
```

Le graphe montre la divergence : deux chemins partent de `ef14ef9`.

```bash
$ git pull --no-rebase
Fusion automatique de jeu.txt
CONFLIT (contenu) : Conflit de fusion dans jeu.txt
La fusion automatique a échoué ; réglez les conflits et validez le résultat.

$ git status
Sur la branche master
Votre branche et 'origin/master' ont divergé,
et ont 1 et 1 commits différents chacune respectivement.
  (use "git pull" if you want to integrate the remote branch with yours)

Vous avez des chemins non fusionnés.
  (réglez les conflits puis lancez "git commit")
  (utilisez "git merge --abort" pour annuler la fusion)

Chemins non fusionnés :
  (utilisez "git add <fichier>..." pour marquer comme résolu)
	modifié des deux côtés :  jeu.txt

aucune modification n'a été ajoutée à la validation (utilisez "git add" ou "git commit -a")

$ cat jeu.txt
<<<<<<< HEAD
vitesse: 300
=======
vitesse: 250
>>>>>>> e31dc7dd1feede5b42700dacae1877bbf37b67f1
```

Entre `<<<<<<< HEAD` et `=======`, c'est la version d'audrey (300). Entre `=======` et `>>>>>>>`, c'est celle qui arrive de pasquin (250).

## 6. Première résolution (incomplète)

J'ai décidé de retenir 275, entre les deux. J'ai ouvert `jeu.txt` avec `nano`, mais je n'ai changé que `300` en `275` : les trois marqueurs et la ligne `250` sont restés.

```bash
$ nano jeu.txt
$ cat jeu.txt
<<<<<<< HEAD
vitesse: 275
=======
vitesse: 250
>>>>>>> e31dc7dd1feede5b42700dacae1877bbf37b67f1

$ grep -n '<<<<<<<\|=======\|>>>>>>>' jeu.txt
1:<<<<<<< HEAD
3:=======
5:>>>>>>> e31dc7dd1feede5b42700dacae1877bbf37b67f1
```

Le `grep` a trouvé les marqueurs, ce qui voulait dire que le fichier n'était pas prêt. Je ne l'ai pas vu à ce moment-là et j'ai continué :

```bash
$ git add jeu.txt
$ git status
Sur la branche master
Votre branche et 'origin/master' ont divergé,
et ont 1 et 1 commits différents chacune respectivement.
  (use "git pull" if you want to integrate the remote branch with yours)

Tous les conflits sont réglés mais la fusion n'est pas terminée.
  (utilisez "git commit" pour terminer la fusion)

Modifications qui seront validées :
	modifié :         jeu.txt

$ git commit -m "Fusionner les vitesses de pasquin et d'audrey" -m "250 et 300 étaient en conflit ; on retient 275, entre les deux."
[master ab611ba] Fusionner les vitesses de pasquin et d'audrey

$ git push
Énumération des objets: 10, fait.
Décompte des objets: 100% (10/10), fait.
Compression par delta en utilisant jusqu'à 12 fils d'exécution
Compression des objets: 100% (3/3), fait.
Écriture des objets: 100% (6/6), 667 octet | 667.00 KiB/s, fait.
Total 6 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To /home/tapa-fotso-pasquin/Bureau/exo6/serveur.git
   e31dc7d..ab611ba  master -> master
```

`git add` marque le fichier comme réglé sans vérifier son contenu : Git m'a fait confiance. J'ai donc poussé un fichier qui contenait encore les marqueurs. C'est l'erreur que décrit le chapitre 2 : un marqueur oublié donne un fichier cassé.

## 7. La correction

Le commit `ab611ba` était déjà partagé, donc je n'ai pas réécrit l'historique (ni `git reset`, ni `git push --force`). J'ai ajouté un nouveau commit de correction.

```bash
$ nano jeu.txt
$ cat jeu.txt
vitesse: 275

$ grep -n '<<<<<<<\|=======\|>>>>>>>' jeu.txt
(aucun résultat)

$ git add jeu.txt
$ git commit -m "Retirer les marqueurs de conflit de jeu.txt" -m "Le commit de fusion ab611ba avait gardé les marqueurs ; le fichier ne contient plus que vitesse: 275."
[master 4e53453] Retirer les marqueurs de conflit de jeu.txt
 1 file changed, 4 deletions(-)

$ git push
Énumération des objets: 5, fait.
Décompte des objets: 100% (5/5), fait.
Compression par delta en utilisant jusqu'à 12 fils d'exécution
Compression des objets: 100% (1/1), fait.
Écriture des objets: 100% (3/3), 335 octet | 335.00 KiB/s, fait.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To /home/tapa-fotso-pasquin/Bureau/exo6/serveur.git
   ab611ba..4e53453  master -> master

$ git log --oneline --graph --all
* 4e53453 (HEAD -> master, origin/master, origin/HEAD) Retirer les marqueurs de conflit de jeu.txt
*   ab611ba Fusionner les vitesses de pasquin et d'audrey
|\  
| * e31dc7d Passer la vitesse à 250
* | dfdc8fd Passer la vitesse à 300
|/  
* ef14ef9 Ajouter jeu.txt
```

Le commit de correction affiche `4 deletions(-)` : il retire les trois marqueurs et la ligne `vitesse: 250`.

## 8. Vérification côté pasquin

```bash
$ git pull
remote: Énumération des objets: 13, fait.
remote: Décompte des objets: 100% (13/13), fait.
remote: Compression des objets: 100% (4/4), fait.
remote: Total 9 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Dépaquetage des objets: 100% (9/9), 950 octet | 316.00 KiB/s, fait.
Depuis /home/tapa-fotso-pasquin/Bureau/exo6/serveur
   e31dc7d..4e53453  master     -> origin/master
Mise à jour e31dc7d..4e53453
Fast-forward
 jeu.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

$ cat jeu.txt
vitesse: 275
```

Pasquin a récupéré la fusion et la correction sans conflit. Les deux clones et le serveur contiennent `vitesse: 275`.

