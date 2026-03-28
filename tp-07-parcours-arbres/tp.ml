type ('a, 'b) arbre = F of 'b | N of 'a * ('a, 'b) arbre * ('a, 'b) arbre

let t1 = N (12, N (4, N (7, F 20, F 30), N (14, F 1, F 2)), F 20)

let print_arbre (show_n : 'a -> string) (show_f : 'b -> string)
    (tree : ('a, 'b) arbre) : unit =
  (* Fonction utilitaire pour compléter une chaîne avec des espaces *)
  let pad str len =
    let l = String.length str in
    if l < len then str ^ String.make (len - l) ' ' else str
  in

  (* Fusionne deux blocs de texte (gauche et droit) côte à côte *)
  let rec merge_blocks b1 b2 w1 =
    match (b1, b2) with
    | [], [] -> []
    | h :: t, [] -> pad h w1 :: merge_blocks t [] w1
    | [], h :: t -> (String.make w1 ' ' ^ h) :: merge_blocks [] t w1
    | h1 :: t1, h2 :: t2 -> (pad h1 w1 ^ h2) :: merge_blocks t1 t2 w1
  in

  (* Fonction récursive qui renvoie : (lignes_du_dessin, largeur_totale, centre_du_noeud) *)
  let rec build t =
    match t with
    | F b ->
        let s = "[" ^ show_f b ^ "]" in
        let w = String.length s in
        ([ s ], w, w / 2)
    | N (a, g, d) ->
        let s = "(" ^ show_n a ^ ")" in
        let lw = String.length s in

        (* On calcule les sous-arbres récursivement *)
        let lg, wg, cg = build g in
        let ld, wd, cd = build d in

        (* Espace minimum entre le sous-arbre gauche et droit *)
        let gap = 4 in

        (* On assemble les lignes des enfants côte à côte *)
        let children_lines = merge_blocks lg ld (wg + gap) in
        let total_w = wg + gap + wd in

        (* Calcul de la position absolue du centre de l'enfant droit *)
        let cd_absolu = wg + gap + cd in

        (* Le parent se place exactement au milieu de ses deux enfants *)
        let root_c = (cg + cd_absolu) / 2 in

        (* Ligne du nœud parent *)
        let root_spaces = max 0 (root_c - (lw / 2)) in
        let root_line = String.make root_spaces ' ' ^ s in

        (* Dessin des branches :  ___/   \___  *)
        let branch_len = max (total_w + 1) (root_c + 1) in
        let b_bytes = Bytes.make branch_len ' ' in

        for i = cg + 1 to root_c - 1 do
          Bytes.set b_bytes i '_'
        done;
        for i = root_c + 1 to cd_absolu - 1 do
          Bytes.set b_bytes i '_'
        done;

        Bytes.set b_bytes cg '/';
        Bytes.set b_bytes cd_absolu '\\';
        Bytes.set b_bytes root_c '|';

        let branch_line = Bytes.to_string b_bytes in

        (* On empile le parent, les branches, et les enfants *)
        (root_line :: branch_line :: children_lines, total_w, root_c)
  in

  let lines, _, _ = build tree in
  List.iter print_endline lines

let rec hauteur (h : ('a, 'b) arbre) : int =
  match h with F _ -> 0 | N (_, g, d) -> 1 + max (hauteur g) (hauteur d)

(** On a monté dans le cours que sa complexité est en O(n)*)

let rec taille (h : ('a, 'b) arbre) : int =
  match h with F _ -> 1 | N (_, g, d) -> 1 + taille g + taille d

(** On a monté dans le cours que sa complexité est en O(n)*)

let rec dernier (h : ('a, 'b) arbre) : 'b =
  match h with F x -> x | N (_, _, d) -> dernier d

let rec affiche_prefixe (h : (int, int) arbre) : unit =
  match h with
  | F x ->
      print_int x;
      print_newline ()
  | N (x, g, d) ->
      print_int x;
      print_newline ();
      affiche_prefixe g;
      affiche_prefixe d

let rec affiche_infixe (h : (int, int) arbre) : unit =
  match h with
  | F x ->
      print_int x;
      print_newline ()
  | N (x, g, d) ->
      affiche_prefixe g;
      print_int x;
      print_newline ();
      affiche_prefixe d

let rec affiche_postfixe (h : (int, int) arbre) : unit =
  match h with
  | F x ->
      print_int x;
      print_newline ()
  | N (x, g, d) ->
      affiche_prefixe g;
      affiche_prefixe d;
      print_int x;
      print_newline ()

type ('a, 'b) token = Ft of 'b | Nt of 'a

let rec postfixe_naif (a : ('a, 'b) arbre) : ('a, 'b) token list =
  match a with
  | F x -> [ Ft x ]
  | N (x, g, d) -> postfixe_naif g @ postfixe_naif d @ [ Nt x ]

(** Cette fonction va être inefficace au vu du cout de la complexité de "@"*)

let postfixe (a : ('a, 'b) arbre) : ('a, 'b) token list =
  let rec aux (a : ('a, 'b) arbre) (b : ('a, 'b) token list) :
      ('a, 'b) token list =
    match a with
    | F x -> Ft x :: b
    | N (x, g, d) ->
        let b1 = aux g b in
        let b2 = aux d b1 in
        Nt x :: b2
  in
  let ans = aux a [] in
  List.rev ans

let prefixe (a : ('a, 'b) arbre) : ('a, 'b) token list =
  let rec aux (a : ('a, 'b) arbre) (b : ('a, 'b) token list) :
      ('a, 'b) token list =
    match a with
    | F x -> Ft x :: b
    | N (x, g, d) ->
        let b1 = aux g (Nt x :: b) in
        let b2 = aux d b1 in
        b2
  in
  List.rev (aux a [])

let infixe (a : ('a, 'b) arbre) : ('a, 'b) token list =
  let rec aux (a : ('a, 'b) arbre) (b : ('a, 'b) token list) :
      ('a, 'b) token list =
    match a with
    | F x -> Ft x :: b
    | N (x, g, d) ->
        let b1 = aux g b in
        let b2 = aux d (Nt x :: b1) in
        b2
  in
  List.rev (aux a [])

let postfixe_term (a : ('a, 'b) arbre) : ('a, 'b) token list =
  let rec aux (a : ('a, 'b) arbre list) (l : ('a, 'b) token list) :
      ('a, 'b) token list =
    match a with
    | [] -> l
    | x :: xs -> (
        match x with
        | F b -> aux xs (Ft b :: l)
        | N (b, g, d) -> aux (d :: g :: xs) (Nt b :: l))
  in
  aux [ a ] []

let largeur (a : ('a, 'b) arbre) : ('a, 'b) token list =
  let q = Queue.create () in
  let rec aux a =
    match a with
    | [] -> ()
    | t :: ts -> (
        match t with
        | F x ->
            Queue.push (Ft x) q;
            aux ts
        | N (x, g, d) ->
            Queue.push (Nt x) q;
            aux (g :: d :: ts))
  in
  aux [ a ];
  let rec aux2 l =
    if Queue.is_empty q then l
    else
      let element = Queue.pop q in
      aux2 (element :: l)
  in
  List.rev (aux2 [])

let rec lire_etiquette (c : bool list) (t : ('a, 'b) arbre) : ('a, 'b) token =
  match c with
  | x :: xs -> (
      if x then
        match t with
        | F b -> failwith "Impossible"
        | N (a, g, d) -> lire_etiquette xs d
      else
        match t with
        | F b -> failwith "Impossible"
        | N (a, g, d) -> lire_etiquette xs g)
  | [] -> ( match t with F x -> Ft x | N (x, g, d) -> Nt x)

let rec incremente (t : (int, int) arbre) (c : bool list) : (int, int) arbre =
  match (t, c) with
  | N (x, g, d), [] -> N (x + 1, g, d)
  | F x, [] -> F (x + 1)
  | N (x, g, d), b :: bs ->
      if b then begin
        N (x, g, incremente d bs)
      end
      else N (x, incremente g bs, d)
  | F _, _ -> failwith "Impossible"

let affiche (x : int) (c : bool list) : unit =
  List.iter (fun b -> print_int (if b then 1 else 0)) c;
  Printf.printf " : %i\n" x

let rec tableau_adresses (t : (int, int) arbre) : unit =
  let rec aux (t : (int, int) arbre) (bl : bool list) =
    match t with
    | F x -> affiche x (List.rev bl)
    | N (x, g, d) ->
        affiche x (List.rev bl);
        aux g (false :: bl);
        aux d (true :: bl)
  in
  aux t []

let lire_postfixe (tk : ('a, 'b) token list) : ('a, 'b) arbre =
  let rec aux (tk : ('a, 'b) token list)  =
    match tk with
    | [] -> F 0
    | x :: xs ->
      match x with
      | Ft b -> F b
      | Nt a -> N (a, aux )