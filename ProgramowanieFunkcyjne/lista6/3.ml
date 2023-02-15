module Counter : sig
  val next: unit -> int
  val reset: unit -> unit
end = struct
  let cnt = ref 0
  let next () =
    let r = !cnt in
    cnt := r + 1;
    r
  let reset () =
    cnt := 0
  end