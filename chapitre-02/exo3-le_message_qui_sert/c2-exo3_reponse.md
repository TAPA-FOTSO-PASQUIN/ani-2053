

J'ai pris les trois derniers commits du dépôt Nkentseu avec la commande `git log --oneline -3`. Voici le résultat :

```bash
$ git log --oneline -3
6fb634fc (HEAD -> main, origin/main, origin/HEAD) NKCode : le web sort du polissage et devient la phase 14, avec une echeance reelle
860e9d7f Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)
c1c815ff CI : les huit epinglages de Jenga passent par JENGA_VERSION (#87)
```
```bash
Pour chaque commit, je regarde trois choses : est-ce qu'il dit ce qu'il fait, est-ce qu'il dit pourquoi, et est-ce qu'il n'a qu'un seul sujet.

## Commit 1 : 6fb634fc

- **Ce qu'il fait :** en partie. On comprend qu'une phase change de statut, mais on ne sait pas ce qui est modifié exactement (la feuille de route, la documentation, du code ?).
- **Pourquoi :** un indice seulement, « avec une échéance réelle ». Le web devient une priorité datée, mais la raison n'est pas écrite.
- **Un seul sujet :** oui, un seul changement, celui du statut du web dans NKCode.

## Commit 2 : 860e9d7f

- **Ce qu'il fait :** non. « Refonte » ne dit pas ce qui est refondu, et « à jour avec main » décrit une opération de Git, pas un changement du programme.
- **Pourquoi :** non, aucune raison n'apparaît dans la ligne de sujet.
- **Un seul sujet :** non. Le message relie deux sujets par « et » : la refonte de NK3DModeler et la signature de NKCode par certificat. Le chapitre 2 dit que si un message contient « et aussi », il faut faire deux commits. Ici on ne peut pas annuler l'un sans l'autre.

## Commit 3 : c1c815ff

- **Ce qu'il fait :** oui, et précisément. Les huit versions de Jenga écrites en dur passent par une seule variable, `JENGA_VERSION`.
- **Pourquoi :** pas écrit, mais on le devine : il n'y a plus qu'un seul endroit à modifier pour changer de version de Jenga, au lieu de huit.
- **Un seul sujet :** oui, un seul changement dans la CI.

## Le plus faible : 860e9d7f

C'est celui qui échoue sur les trois questions : il ne dit pas clairement ce qu'il fait, il ne dit pas pourquoi, et il mélange deux sujets. Le « (#85) » montre que c'est une fusion de pull request, ce qui explique le mélange mais ne le justifie pas. Un commit comme celui-là est impossible à annuler proprement.

**Message d'origine :**

    Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)

**Ma réécriture, en deux commits :**

    Refondre NK3DModeler

    Mettre NK3DModeler à jour avec main. Ce changement est séparé de la
    signature de NKCode pour qu'on puisse l'annuler seul.

et

    Signer NKCode par certificat

    NKCode est maintenant signé avec un certificat. Ce changement est séparé
    de la refonte de NK3DModeler pour qu'on puisse l'annuler seul.
```