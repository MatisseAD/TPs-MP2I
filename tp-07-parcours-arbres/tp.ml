type ('a, 'b) arbre = F of 'b | N of 'a * ('a, 'b) arbre * ('a, 'b) arbre

let t1 = N (12, N (4, N (7, F 20, F 30), N (14, F 1, F 2)), F 20)

(* ========================================================================== *)
(* MOTEUR DE RENDU 2D : ARBRE CLASSIQUE (HAUT EN BAS)                         *)
(* ========================================================================== *)

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
