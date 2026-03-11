type op = Plus | Fois | Moins
type expr = C of int | N of op * expr * expr

(** Q1 **)

let abre_ci_dessus =
  N (Plus, N (Fois, C 4, N (Moins, C 8, C 9)), N (Plus, C 6, C 7))

(** Q2 **)

(** 2 + 3 * 4 **)

let arb1 = N (Plus, C 2, N (Fois, C 3, C 4))

(** (2+3)*4 **)
let arb2 = N (Fois, N (Plus, C 2, C 3), C 4)

(** Q3 **)

let applique (p : op) (x : int) (y : int) : int =
  match p with Plus -> x + y | Moins -> x - y | Fois -> x * y

(** Q4 **)

let rec eval (arbre : expr) : int =
  match arbre with
  | C x -> x
  | N (p, x, y) -> (
      match p with
      | Plus -> eval x + eval y
      | Fois -> eval x * eval y
      | Moins -> eval x - eval y)

(** 1. Notation infixe

    (6 + 7) + (4 * (8 - 9))

    2. Notation préfixe

    + 6 7 * 4 - 8 9

    3. Notation suffixe

    8 9 - 4 * 6 7 + + *)
