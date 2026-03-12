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

    + * 4 - 8 9 + 6 7

    3. Notation postfixe *)

type lexeme = PO | PF | Op of op | Val of int

let rec prefixe (p : expr) : lexeme list =
  match p with
  | C x -> [ Val x ]
  | N (op, exp1, exp2) -> (
      match op with
      | Plus -> [ Op Plus ] @ prefixe exp1 @ prefixe exp2
      | Fois -> [ Op Fois ] @ prefixe exp1 @ prefixe exp2
      | Moins -> [ Op Moins ] @ prefixe exp1 @ prefixe exp2)

let rec postfixe (p : expr) : lexeme list =
  match p with
  | C x -> [ Val x ]
  | N (op, exp1, exp2) -> (
      match op with
      | Plus -> prefixe exp1 @ prefixe exp2 @ [ Op Plus ]
      | Fois -> prefixe exp1 @ prefixe exp2 @ [ Op Fois ]
      | Moins -> prefixe exp1 @ prefixe exp2 @ [ Op Moins ])

let rec infixe (p : expr) : lexeme list =
  match p with
  | C x -> [ Val x ]
  | N (op, exp1, exp2) -> (
      match op with
      | Plus -> [ PO ] @ infixe exp1 @ [ Op Plus ] @ infixe exp2 @ [ PF ]
      | Fois -> infixe exp1 @ [ Op Fois ] @ infixe exp2
      | Moins -> infixe exp1 @ [ Op Moins ] @ infixe exp2)

let eval_post (p : lexeme list) : int =
  let pile = ref [] in
  let rec aux (p : lexeme list) =
    match p with
    | [] -> (
        match !pile with [ x ] -> x | _ -> failwith "Conditions non respectés")
    | x :: xs -> (
        match x with
        | PO | PF -> failwith "Impossible"
        | Val t ->
            pile := t :: !pile;
            aux xs
        | Op t -> (
            match t with
            | Fois -> (
                match !pile with
                | x :: y :: ys ->
                    pile := (x * y) :: ys;
                    aux xs
                | _ -> failwith "Conditions non respectés")
            | Moins -> (
                match !pile with
                | x :: y :: ys ->
                    pile := (y - x) :: ys;
                    aux xs
                | _ -> failwith "Conditions non respectés")
            | Plus -> (
                match !pile with
                | x :: y :: ys ->
                    pile := (x + y) :: ys;
                    aux xs
                | _ -> failwith "Conditions non respectés")))
  in
  aux p

type expr2 = N of op * expr2 * expr2 | C of int | V of int
type valuation = int array

let max_var (p : expr2) : int =
  let rec aux (p : expr2) =
    match p with
    | N (operation, exp1, exp2) -> max (aux exp1) (aux exp2)
    | C _ -> 0
    | V entier -> entier
  in
  aux p

let rec eval_contexte (e : expr2) (v : valuation) : int =
  match e with
  | C x -> x
  | V x -> v.(x)
  | N (operation, exp1, exp2) ->
      applique operation (eval_contexte exp1 v) (eval_contexte exp2 v)

let check (i : int) (v : valuation) : bool =
  if Array.length v <= i then false else true

let rec eval_partielle (e : expr2) (v : valuation) : expr2 =
  let rec transfo e v =
    match e with
    | C x -> C x
    | N (operation, exp1, exp2) -> N (operation, transfo exp1 v, transfo exp2 v)
    | V x -> if check x v then C v.(x) else V x
  in
  let ebis = transfo e v in
  let rec aux e v =
    match e with
    | V x -> V x
    | C x -> C x
    | N (operation, exp1, exp2) -> (
        match (exp1, exp2) with
        | C x, C y -> C (applique operation x y)
        | _ -> N (operation, aux exp1 v, aux exp2 v))
  in
  aux ebis v

type op_bis = Plus | Fois
type expr3 = C of int | V of int | N of op * expr3 * expr3
type expr_naire = Cn of int | Vn of int | Nn of op * expr_naire list


let normalise (e : expr3) (v : valuation) : expr_naire =
  let rec transfo e v =
    match e with
    | C x -> C x
    | N (operation, exp1, exp2) -> N (operation, transfo exp1 v, transfo exp2 v)
    | V x -> if check x v then C v.(x) else V x
  in
  let ebis = transfo e v in
  let rec aux e v =
    match e with
    | V x -> V x
    | C x -> C x
    | N (operation, exp1, exp2) -> (
        match (exp1, exp2) with
        | C x, C y -> C (applique operation x y)
        | _ -> N (operation, aux exp1 v, aux exp2 v))
  in
  let efinal = aux ebis v in
  let rec aux2 e = 
    match efinal with
    | C x -> [Cn x]
    | V x -> [Vn x]
    | 
