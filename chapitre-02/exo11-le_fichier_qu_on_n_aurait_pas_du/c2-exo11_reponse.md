# Chapitre 2 — Exercice 11 : Le fichier qu'on n'aurait pas dû

## 1. Description de mon expérimentation

Afin d'observer l'impact de l'ajout puis de la suppression d'un gros fichier binaire dans l'historique Git, j'ai généré un fichier aléatoire non compressible de 10 Mo (`gros.bin`) à l'aide de la commande `head -c 10485760 /dev/urandom`.

J'ai ensuite mesuré le volume du dossier `.git` à chaque étape de mes manipulations avec les commandes `du -sb .git` et `git count-objects -v` :

1. **Mon état initial :** Mon dossier `.git` pesait **27 095 octets** (3 objets enregistrés).
2. **Après l'ajout et le commit de `gros.bin` :** Mon dossier `.git` est passé à **10 516 793 octets** (environ 10,5 Mo de plus, 6 objets).
3. **Après ma suppression avec `git rm gros.bin` et commit :** Le fichier a disparu de ma copie de travail, mais mon dossier `.git` pèse désormais **10 517 218 octets** (7 objets).

---

## 2. Analyse de mes résultats

* **Taille initiale :** 27 095 octets
* **Taille après mon ajout :** 10 516 793 octets
* **Taille après ma suppression :** 10 517 218 octets

J'ai constaté que la suppression du fichier au commit suivant n'a absolument pas diminué la taille de mon dépôt. Au contraire, mon dossier `.git` a légèrement augmenté (425 octets supplémentaires correspondant aux métadonnées de mon nouveau commit de suppression).

En inspectant mon historique, j'ai pu confirmer la présence continue de l'objet :
* Ma commande `git show --stat HEAD~1` montre que le commit `6aca786` contient toujours `gros.bin`.
* Ma commande `git cat-file -s 6aca786:gros.bin` indique que le fichier binaire est conservé intact dans la base d'objets (10 485 760 octets).

---

## 3. Ma conclusion

Cette expérience m'a permis de vérifier le principe d'immuabilité des commits dans Git :
Un commit enregistré ne change jamais. Lorsque j'effectue un `git rm` suivi d'un commit, je ne supprime pas l'élément du dépôt ; je crée simplement un nouvel état où le fichier n'apparaît plus dans ma copie de travail actuelle.

Tant que le commit `6aca786` existe dans mon arbre d'historique, l'objet binaire reste stocké dans `.git` et sera téléchargé par toute personne qui clonera mon projet.

J'en déduis que pour retirer définitivement un tel fichier (ou une donnée sensible comme un secret/mot de passe), je devrais réécrire l'historique, ce qui modifierait l'empreinte de tous mes commits ultérieurs et poserait des problèmes sur un dépôt partagé. C'est pourquoi la meilleure pratique consiste à ne jamais committer de fichiers lourds ou sensibles dès le départ (en utilisant un fichier `.gitignore`).