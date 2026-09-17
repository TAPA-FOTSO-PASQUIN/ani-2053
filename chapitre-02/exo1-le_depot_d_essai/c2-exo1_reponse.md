Pour commencer j'ai cree le dossier "git-exo" que j'ai ouvert dans le terminal et j'ai initialise avec la commande git init le resultat est : 

```bash
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git init
hint: Using 'master' as the name for the initial branch. This default branch name
hint: will change to "main" in Git 3.0. To configure the initial branch name
hint: to use in all of your new repositories, which will suppress this warning,
hint: call:
hint:
hint: 	git config --global init.defaultBranch <name>
hint:
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint:
hint: 	git branch -m <name>
hint:
hint: Disable this message with "git config set advice.defaultBranchName false"
Dépôt Git vide initialisé dans /home/tapa-fotso-pasquin/Bureau/git-exo/.git/
```



# Ensuite j'ai cree 3 fichiers txt aapres cration de chaque fichier j'ai tape les commandes git add et git commit le resultat est le suivant :


```bash
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add fichier1.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git commit -m "ajout du fichier1.txt"
[master (commit racine) 861c8b4] ajout du fichier1.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier1.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add ficher2.txt 
fatal: le chemin 'ficher2.txt' ne correspond à aucun fichier
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add fichier2.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git commit -m "ajout du fichier2.txt"
[master 26cf23a] ajout du fichier2.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier2.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add fichier3.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git commit -m "ajout du fichier3.txt"
[master e6b538e] ajout du fichier3.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier3.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ 

```

APRES j'ai affiche l'historique avec la commande git log --oneline
 le resultat est :

 ```bash
 tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git log --oneline
e6b538e (HEAD -> master) ajout du fichier3.txt
26cf23a ajout du fichier2.txt
861c8b4 ajout du fichier1.txt
```

pour afficher le graphe j'ai utilise la commande : git log --oneline --graph
le resultat est :

```bash
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git log --oneline --graph
* e6b538e (HEAD -> master) ajout du fichier3.txt
* 26cf23a ajout du fichier2.txt
* 861c8b4 ajout du fichier1.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ 
```

voici tout ce qui a ete fait dans mon terminal

```bash
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git init
hint: Using 'master' as the name for the initial branch. This default branch name
hint: will change to "main" in Git 3.0. To configure the initial branch name
hint: to use in all of your new repositories, which will suppress this warning,
hint: call:
hint:
hint: 	git config --global init.defaultBranch <name>
hint:
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint:
hint: 	git branch -m <name>
hint:
hint: Disable this message with "git config set advice.defaultBranchName false"
Dépôt Git vide initialisé dans /home/tapa-fotso-pasquin/Bureau/git-exo/.git/
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add fichier1.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git commit -m "ajout du fichier1.txt"
[master (commit racine) 861c8b4] ajout du fichier1.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier1.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add ficher2.txt 
fatal: le chemin 'ficher2.txt' ne correspond à aucun fichier
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add fichier2.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git commit -m "ajout du fichier2.txt"
[master 26cf23a] ajout du fichier2.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier2.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git add fichier3.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ git commit -m "ajout du fichier3.txt"
[master e6b538e] ajout du fichier3.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier3.txt
tapa-fotso-pasquin@tapa-fotso-pasquin-Modern-14-C12MO:~/Bureau/git-exo$ 
```