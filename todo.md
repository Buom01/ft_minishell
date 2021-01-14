# To do

## fdeĉ:

- [FAIT] Afficher un prompt en l’attente d’une nouvelle commande
- [FAIT] Parsing
- [FAIT] Executer le bon executable
- [FAIT] Gérer correctement les fd / pipes / redirections
- [EN COURS] Fix bugs, fix norme
- BONUS ?


## badam:

- [FAIT] Chercher ~~et lancer~~ le bon executable (basé sur une variable d’environnement PATH ou en utilisant un path absolu), comme dans bash
	`-> [En considération] Le code devrait être réécris avec utils/paths
- [TESTED] Gestion basique des variables d'environements (initialisation, obtention, réinitialisation)
- [TESTED] Builtins: export, unset, env, echo, pwd, cd, exit
- [FAIT] Processing
- [FAIT] Revoir CD
- [FAIT]Vérifier les builtins quant au man

--- À faire ---
valeur de $?
fermer les pipes en cas d'arrêt: cat /dev/urandom | head (si c'est important ?)
vérifier les leaks (grossièrement) (normalement OK)
vérifier les fonctions intérdites et autorisées (cd srcs && ag 'fonctioninterdite')
norme (libft aussi ? on peut considérer qu'il ne fait pas partie du projet donc exclue de la norme)
supprimer ce todo et push
