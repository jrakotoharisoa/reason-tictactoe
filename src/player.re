type player =
  | X
  | O;

let p_to_str = (p: player) =>
  switch p {
  | X => "1"
  | O => "2"
  };