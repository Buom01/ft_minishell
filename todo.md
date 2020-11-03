# To do

## fdeĉ:

- [FAIT] Afficher un prompt en l’attente d’une nouvelle commande
- [FAIT] Parsing
- [FAIT] Executer le bon executable
- Gérer correctement les fd / pipes / redirections


## badam:

- [FAIT] [À REVOIR] Chercher ~~et lancer~~ le bon executable (basé sur une variable d’environnement PATH ou en utilisant un path absolu), comme dans bash
		Le code devrait être réécris avec utils/paths
- [TESTED] Gestion basique des variables d'environements (initialisation, obtention, réinitialisation)
- [TESTED] Builtins: export, unset, env, echo, pwd, cd, exit
- [À REVOIR] Builtins: cd (tester tout les cas!)
