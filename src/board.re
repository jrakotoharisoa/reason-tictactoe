open Player;

type token =
  | Mark(player)
  | Empty;

type row = (token, token, token);

type board = (row, row, row);

type colId =
  | C1
  | C2
  | C3;

let col_to_str = (colId: colId) =>
  switch (colId) {
  | C1 => "C1"
  | C2 => "C2"
  | C3 => "C3"
  };

type rowId =
  | R1
  | R2
  | R3;

let row_to_str = (rowId: rowId) =>
  switch (rowId) {
  | R1 => "R1"
  | R2 => "R2"
  | R3 => "R3"
  };

let getToken = (board: board, rid: rowId, cid: colId) => {
  let (r1, r2, r3) = board;
  let fromRow = ((t1, t2, t3): row, cid) =>
    switch (cid) {
    | C1 => t1
    | C2 => t2
    | C3 => t3
    };
  switch (rid) {
  | R1 => fromRow(r1, cid)
  | R2 => fromRow(r2, cid)
  | R3 => fromRow(r3, cid)
  };
};

let updateBoard = (board: board, rid: rowId, cid: colId, value: token) => {
  let (r1, r2, r3) = board;
  let updateRow = (row: row, cid: colId, value: token) => {
    let (c1, c2, c3) = row;
    switch (cid, row) {
    | (C1, (Empty, _, _)) => (value, c2, c3)
    | (C2, (_, Empty, _)) => (c1, value, c3)
    | (C3, (_, _, Empty)) => (c1, c2, value)
    | _ => row
    };
  };
  switch (rid) {
  | R1 =>
    let r = updateRow(r1, cid, value);
    r === r1 ? board : (r, r2, r3);
  | R2 =>
    let r = updateRow(r2, cid, value);
    r === r2 ? board : (r1, r, r3);
  | R3 =>
    let r = updateRow(r3, cid, value);
    r === r3 ? board : (r1, r2, r);
  };
};

type line = (token, token, token);

let isLineContainToken = (t: token, (t1, t2, t3): line) =>
  t1 === t || t2 === t || t3 === t;

let isBoardFull = ((r1, r2, r3): board) =>
  ! (
    isLineContainToken(Empty, r1)
    || isLineContainToken(Empty, r2)
    || isLineContainToken(Empty, r3)
  );

let isLineFullWith = (t: token, l: line) => {
  let (t1, t2, t3) = l;
  t1 == t && t2 == t && t3 == t;
};

let getRowLine = (board: board, rId: rowId) => {
  let (r1, r2, r3) = board;
  switch (rId) {
  | R1 => r1
  | R2 => r2
  | R3 => r3
  };
};

let getColumnLine = (board: board, colId: colId) => {
  let ((r1c1, r1c2, r1c3), (r2c1, r2c2, r2c3), (r3c1, r3c2, r3c3)) = board;
  switch (colId) {
  | C1 => (r1c1, r2c1, r3c1)
  | C2 => (r1c2, r2c2, r3c2)
  | C3 => (r1c3, r2c3, r3c3)
  };
};

let getDiagonalLines = (board: board) : list(line) => {
  let ((r1c1, _, r1c3), (_, r2c2, _), (r3c1, _, r3c3)) = board;
  [(r1c1, r2c2, r3c3), (r1c3, r2c2, r3c1)];
};