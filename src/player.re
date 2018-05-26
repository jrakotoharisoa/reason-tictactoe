type player =
  | Cross
  | Circle;

let toString = (p: player) =>
  switch (p) {
  | Cross => "X"
  | Circle => "O"
  };