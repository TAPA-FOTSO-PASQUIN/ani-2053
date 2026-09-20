# Démo 4 : La revue de branche

## Ce que j'ai deja fait

Avant de relire la branche de l'autre groupe, je me suis entraîné sur une branche de test, `essai-revue`, créée dans mon dépôt `demo3` avec deux défauts volontaires : de mauvais messages et un faux secret.

```bash
$ git log --oneline master..essai-revue
ff9be9c update
b3cde7a fix

$ git diff --stat master...essai-revue
 niveau4.txt | 1 +
 secret.txt  | 1 +
 2 files changed, 2 insertions(+)

$ git grep -n 'mot de passe' essai-revue
essai-revue:secret.txt:1:mot de passe: 1234
```

## Ma revue d'entraînement

- **Ce que fait la branche :** elle ajoute deux fichiers, `niveau4.txt` (`niveau 4`) et `secret.txt` (un mot de passe).
- **Les commits :** `b3cde7a` « fix » et `ff9be9c` « update » ne disent ni ce qu'ils font ni pourquoi. Le premier n'a rien corrigé, il ajoute un fichier. Le second cache qu'il ajoute un secret.
- **Ce qui manque :** un sujet à l'impératif (« Ajouter le niveau 4 ») et un corps qui dit pourquoi.
- **Ce qui ne devrait pas y être :** `secret.txt`, qui contient un mot de passe. Un secret committé reste dans l'historique même après suppression.
- **Verdict :** refuser, à cause du secret.

J'ai ensuite supprimé cette branche avec `git branch -D essai-revue`. Elle n'avait jamais été poussée.

## Ce que cet entraînement m'a appris

Une bonne revue regarde quatre choses : ce que fait la branche, si les messages disent quoi et pourquoi, ce qui manque, et ce qui ne devrait pas s'y trouver. Le `git grep` permet de chercher un secret ou un marqueur de conflit dans toute la branche.

