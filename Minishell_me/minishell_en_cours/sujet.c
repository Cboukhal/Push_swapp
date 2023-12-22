notre shell devrait :
//• Afficher une prompt en attendant une nouvelle commande.
//• Avoir une historique. Mais a tester quand on peut
• Rechercher et lancer le bon exécutable (en fonction de la variable PATH ou en utilisant un
relative ou un chemin absolu).
• Éviter d’utiliser plus d’une variable globale pour indiquer un signal reçu.
les implications : cette approche garantit que votre gestionnaire de signal n’accédera pas à votre
principales structures de données.

Attention. Cette variable globale ne peut fournir aucune autre
accès aux informations ou aux données que le nombre d’un signal reçu.
Par conséquent, en utilisant des structures de type "norm" dans le périmètre global est
interdit.

Ne pas interpréter les guillemets non marqués ou les caractères spéciaux qui ne sont pas requis par le
sujet comme   (barre oblique inverse) ou ; (point-virgule).
• Poignée ’ (guillemets simples) qui devrait empêcher le shell d’interpréter la méta-
caractères dans la séquence citée.
• Poignée (") (guillemets doubles) qui devrait empêcher le shell d’interpréter la méta-
caractères dans la séquence citée sauf $ (signe dollar)

redirections d’échantillons :
< doit rediriger l’entrée.
> doit rediriger la sortie.
<< doit recevoir un délimiteur, puis lire l’entrée jusqu’à ce qu’une ligne contenant le
Le délimiteur est visible. Cependant, il n’a pas besoin de mettre à jour l’historique!
>> doit rediriger la sortie en mode ajout.
• Mettre en œuvre des tuyaux (| caractère). La sortie de chaque commande dans le pipeline est
connecté à l’entrée de la commande suivante via un tuyau.
• Gérer les variables d’environnement ($ suivies d’une séquence de caractères) qui
devraient s’étendre à leurs valeurs.
• Gérer $? qui doit passer au statut de sortie de la dernière exécution
pipeline de premier plan.
• Gérer ctrl-C, ctrl-D et ctrl-  qui doivent se comporter comme en bash.

En mode interactif :
ctrl-C affiche une nouvelle invite sur une nouvelle ligne.
//ctrl-D quitte le shell.
//ctrl-  ne fait rien.
• Votre shell doit implémenter les éléments suivants :
//echo avec option -n
//cd avec seulement un chemin relatif ou absolu
//pwd sans options
export sans option
unset sans option
//env sans options ni arguments
//exit sans option

Minishell Aussi belle qu’une coquille
La fonction readline() peut provoquer des fuites de mémoire. Vous n’avez pas à les réparer. Mais
cela ne signifie pas que votre propre code, oui le code que vous avez écrit, peut avoir de la mémoire
fuites.

Vous devez vous limiter à la description du sujet. Tout ce qui
n’est pas demandé n’est pas requis.
Si vous avez un doute sur une exigence, prenez bash comme référence.

