type 'a file_fonct = 'a list * 'a list

let file_vide : 'a file_fonct = ([], [])

let rec miroir (t : 'a list) : 'a list =
  let rec renverse_into t res =
    match t with [] -> res | x :: xs -> renverse_into xs (x :: res)
  in
  renverse_into t []

let ajoute (x : 'a) (f : 'a file_fonct) : 'a file_fonct =
  let a, b = f in
  (x :: a, b)

let enleve (f : 'a file_fonct) : (int * 'a file_fonct) option =
  if f = file_vide then None
  else
    let a, b = f in
    if b = [] then
      let (x :: xs) = miroir a in
      Some (x, (miroir xs, b))
    else
      let (x :: xs) = miroir b in
      Some (x, (a, miroir xs))

let rec somme (f : 'a file_fonct) : int =
  match f with
  | f when f <> file_vide -> (
      let m = enleve f in
      match m with
      | Some (x, f_prime) -> x + somme f_prime
      | Some (0, file_vide) -> 0
      | _ -> failwith "Error")
  | liste_vide -> 0

(**let file_fonct_of_list (t : 'a list) : 'a file_fonct = let temp = miroir t in
   let rec aux (t : 'a list) (f : 'a file_fonct) = match temp with [] ->
   file_vide | x :: xs -> ajoute (x, f) in aux temp file_vide**)

let file_fonct_of_list_eff (t : 'a list) : 'a file_fonct =
  let rec aux (t : 'a list) (lf : 'a file_fonct) =
    match t with
    | [] -> lf
    | x :: xs ->
        let a, b = lf in
        aux xs (x :: a, b)
  in
  aux (miroir t) file_vide

let rec iter_file (a : 'a -> unit) (file : 'a file_fonct) =
  match file with
  | f when f <> file_vide -> (
      let m = enleve f in
      match m with
      | Some (x, f_prime) when f_prime = file_vide -> a x
      | Some (x, f_prime) ->
          a x;
          iter_file a f_prime
      | None -> failwith "Impossible, file est non vide")
