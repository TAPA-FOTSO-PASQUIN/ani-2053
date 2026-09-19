# Exercice 5 : La branche mesurée

Dans mon dépôt d'essai `git-exo`, j'ai créé une branche, fait trois commits dessus, et mesuré la taille du dossier `.git` (où Git stocke tout l'historique) à trois moments. J'ai utilisé deux commandes : `du -sb .git` (taille en octets) et `git count-objects -v` (nombre d'objets).

## Mesure avant la branche

```bash
$ git branch
* master

$ du -sb .git
31355	.git

$ git count-objects -v
count: 19
size: 76
in-pack: 0
packs: 0
size-pack: 0
prune-packable: 0
garbage: 0
size-garbage: 0
```

## Création de la branche

```bash
$ git switch -c ma-branche
Basculement sur la nouvelle branche 'ma-branche'

$ git branch
* ma-branche
  master

$ du -sb .git
31741	.git

$ git count-objects -v
count: 19
size: 76
in-pack: 0
packs: 0
size-pack: 0
prune-packable: 0
garbage: 0
size-garbage: 0
```

## Trois commits sur la branche

```bash
$ git commit -m "Ajouter branche1.txt" -m "Premier fichier créé sur ma-branche, pour mesurer le coût des commits."
[ma-branche ecba714] Ajouter branche1.txt
 1 file changed, 1 insertion(+)
 create mode 100644 branche1.txt

$ git commit -m "Ajouter branche2.txt" -m "Deuxième fichier créé sur ma-branche."
[ma-branche 77a0d9e] Ajouter branche2.txt
 1 file changed, 1 insertion(+)
 create mode 100644 branche2.txt

$ git commit -m "Ajouter branche3.txt" -m "Troisième fichier créé sur ma-branche."
[ma-branche 91ae134] Ajouter branche3.txt
 1 file changed, 1 insertion(+)
 create mode 100644 branche3.txt

$ git log --oneline --graph --all
* 91ae134 (HEAD -> ma-branche) Ajouter branche3.txt
* 77a0d9e Ajouter branche2.txt
* ecba714 Ajouter branche1.txt
* aea9b26 (master) Passer la vitesse de 180 à 250
* d90b822 Renommer le projet en « mon projet de jeu »
* 5d34d46 Ajouter fichier4.txt
* 8fd0241 modification du fichier1.txt
* e6b538e ajout du fichier3.txt
* 26cf23a ajout du fichier2.txt
* 861c8b4 ajout du fichier1.txt
```

## Mesure après les trois commits

```bash
$ du -sb .git
34242	.git

$ git count-objects -v
count: 28
size: 112
in-pack: 0
packs: 0
size-pack: 0
prune-packable: 0
garbage: 0
size-garbage: 0
```


```bash
## Résultats

**Avant la branche :**
- `du -sb .git` : 31 355 octets
- `count` : 19 objets
- `size` : 76 ko

**Branche créée, sans aucun commit :**
- `du -sb .git` : 31 741 octets
- `count` : 19 objets
- `size` : 76 ko

**Après les trois commits :**
- `du -sb .git` : 34 242 octets
- `count` : 28 objets
- `size` : 112 ko

Créer la branche a donc coûté 386 octets et 0 objet. Faire les trois commits a coûté 2 501 octets et 9 objets.

## Explication

**La création de la branche n'a copié aucun fichier.** Le nombre d'objets est resté à 19. Le dépôt a seulement gagné 386 octets : un petit fichier (`refs/heads/ma-branche`) qui contient l'empreinte du commit sur lequel la branche pointe, et une ligne dans le journal des références. Une branche est un nom qui pointe sur un commit, pas une copie du code. C'est pour cela que la créer est instantané et gratuit.

**Ce sont les commits qui ont fait grossir le dépôt.** J'ai gagné 9 objets pour 3 commits, donc 3 objets par commit : le fichier lui-même (blob), le dossier racine (tree) et le commit. Le dépôt a grossi de 2 501 octets, environ 830 octets par commit. Chaque commit ne coûte que ce qu'il change : les fichiers que je n'ai pas touchés (`fichier1.txt`, etc.) ne sont pas recopiés, Git réutilise leurs objets.

**Pourquoi `size` passe de 76 à 112 alors que `du -sb` ne monte que de 2 501 octets.** `du -sb` compte les octets réels, alors que `size` compte l'espace occupé sur le disque en blocs de 4 ko. Mes 9 nouveaux objets, très petits, occupent chacun un bloc : 9 × 4 = 36 ko, soit exactement 112 − 76.

**Conclusion :** ce qui coûte de la place, ce n'est pas la branche, c'est ce qu'on y commite, et même cela reste petit tant que les fichiers sont petits.
```