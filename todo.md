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
- [À FAIRE] Completer les erreurs manquantes
- Finitions de CTRL+...


--- Tests non réussi ---

quotes
|echo "hello" > one > two
|echo hi"     "hihi
|echo "_ _;_ _"
|'echo test'
|echo '$PWD'
|echo "$PWD"

echo $env
$?  # A verifier
CTRL+...

echo ><
echo "hello" > one > two
(ls < nope  # sans permission sur nope)

cat /dev/urandom | head


# A tester après
export PATH=$PATH:toto                                                          
                                                                                
export loop='bonjour$loop'                                                      
echo $loop  

# A vérifier
env: alpha sorting ????????? 
