type op = Plus | Fois
type expr3 = C of int | V of int | N of op * expr3 * expr3
type expr_naire = Cn of int | Vn of int | Nn of op * expr_naire list
