# Evaluation expression postfixe

## 2.a

Step Pile
1     [1]
2     [2; 1]
3     [3; 2; 1]
4     [4; 3; 2; 1]
5     [5; 4; 3; 2; 1]

+     [9; 3; 2; 1]

+     [27; 2; 1]

+     [-25; 2; 1]

6     [6; -25; 2; 1]

+     [150; 2; 1]

+     [151; 1]

## 2.b

1 [1]
2 [2; 1]

+ [3]

+ => Ici il y a un problème, en effet on fait - avec 3, or il n y a moins de deux nombres dans la pile

1 2 3 + => A la fin, il reste deux éléments dans la pile

## 3

Pour que s soit bien formé, il faut que

+ ent_s(i) = op_s(i) - 1

# Expressions avec variables

Dans le cas où la valuation spécifie la valeur de toutes les variables, l'expression renvoyée doit être de la forme d'une expression de type expr2 entière
