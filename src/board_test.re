open Jest;

open Board;

type case = (rowId, colId, token);

type suiteCase = list(case);

describe(
  "getToken",
  () => {
    let board = ((X, O, X), (Empty, O, Empty), (Empty, O, X));
    let testCases = [
      (R1, C1, X),
      (R1, C2, O),
      (R1, C3, X),
      (R2, C1, Empty),
      (R2, C2, O),
      (R2, C3, Empty),
      (R3, C1, Empty),
      (R3, C2, O),
      (R3, C3, X)
    ];
    testAll(
      "should return the right token for board coordinates",
      testCases,
      ((rId, cId, expectedToken)) =>
        Expect.(expect(getToken(board, rId, cId)) |> toBe(expectedToken))
    )
  }
);

describe(
  "updateBoard",
  () => {
    test(
      "should return updated board with given value for given rowId colId",
      () => {
        /* Given */
        let board = ((Empty, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty));
        /* When */
        let actual = updateBoard(board, R1, C1, X);
        /* Then */
        let expected = ((X, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty));
        Expect.(expect(actual) |> toEqual(expected))
      }
    );
    test(
      "should return same board if token in rowId and colId is not Empty",
      () => {
        /* Given */
        let board = ((X, Empty, Empty), (Empty, Empty, Empty), (Empty, Empty, Empty));
        /* When */
        let actual = updateBoard(board, R1, C1, O);
        /* Then */
        Expect.(expect(actual) |> toBe(board))
      }
    )
  }
);

describe(
  "isBoardFull",
  () => {
    test(
      "should return true if board is full",
      () => {
        /* Given */
        let board = ((X, O, X), (O, X, X), (X, O, O));
        /* When */
        let actual = isBoardFull(board);
        /* Then */
        Expect.(expect(actual) |> toBe(true))
      }
    );
    test(
      "should return false if board is not full",
      () => {
        /* Given */
        let board = ((X, O, Empty), (O, X, X), (X, O, O));
        /* When */
        let actual = isBoardFull(board);
        /* Then */
        Expect.(expect(actual) |> toBe(false))
      }
    )
  }
);

describe(
  "isLineFullWith",
  () => {
    test(
      "should return false if Empty on line",
      () => {
        /* Given */
        let line = (Empty, Empty, Empty);
        /* When */
        let actual = isLineFullWith(X, line);
        /* Then */
        Expect.(expect(actual) |> toEqual(false))
      }
    );
    test(
      "should return false if Full without given token",
      () => {
        /* Given */
        let line = (X, X, X);
        /* When */
        let actual = isLineFullWith(O, line);
        /* Then */
        Expect.(expect(actual) |> toEqual(false))
      }
    );
    test(
      "should return true if Full with given token",
      () => {
        /* Given */
        let line = (X, X, X);
        /* When */
        let actual = isLineFullWith(X, line);
        /* Then */
        Expect.(expect(actual) |> toEqual(true))
      }
    )
  }
);

describe(
  "getRowLine",
  () => {
    let board = ((X, O, X), (Empty, O, Empty), (Empty, O, X));
    let (r1, r2, r3) = board;
    let testCases = [(R1, r1), (R2, r2), (R3, r3)];
    testAll(
      "should return correct row",
      testCases,
      ((rId, expectedRow)) => Expect.(expect(getRowLine(board, rId)) |> toEqual(expectedRow))
    )
  }
);

describe(
  "getColumnLine",
  () => {
    let board = ((X, O, X), (Empty, O, Empty), (Empty, O, X));
    let testCases = [(C1, (X, Empty, Empty)), (C2, (O, O, O)), (C3, (X, Empty, X))];
    testAll(
      "should return correct col",
      testCases,
      ((cId, expectedColumn)) =>
        Expect.(expect(getColumnLine(board, cId)) |> toEqual(expectedColumn))
    )
  }
);