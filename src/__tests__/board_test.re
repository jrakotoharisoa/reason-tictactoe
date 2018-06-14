open Board;
open Jest;
open Expect;

type case = (rowId, colId, token);

type suiteCase = list(case);

describe("getToken", () => {
  let board = (
    (Mark(Cross), Mark(Circle), Mark(Cross)),
    (Empty, Mark(Circle), Empty),
    (Empty, Mark(Circle), Mark(Cross)),
  );
  let testCases = [
    (R1, C1, Mark(Cross)),
    (R1, C2, Mark(Circle)),
    (R1, C3, Mark(Cross)),
    (R2, C1, Empty),
    (R2, C2, Mark(Circle)),
    (R2, C3, Empty),
    (R3, C1, Empty),
    (R3, C2, Mark(Circle)),
    (R3, C3, Mark(Cross)),
  ];
  testAll(
    "should return the right token for board coordinates",
    testCases,
    ((rId, cId, expectedToken)) =>
    expect(getToken(board, rId, cId)) |> toEqual(expectedToken)
  );
});

describe("updateBoard", () => {
  test(
    "should return updated board with given value for given rowId colId", () => {
    /* Given */
    let board = (
      (Empty, Empty, Empty),
      (Empty, Empty, Empty),
      (Empty, Empty, Empty),
    );
    /* When */
    let actual = updateBoard(board, R1, C1, Mark(Cross));
    /* Then */
    let expected = (
      (Mark(Cross), Empty, Empty),
      (Empty, Empty, Empty),
      (Empty, Empty, Empty),
    );
    expect(actual) |> toEqual(expected);
  });
  test("should return same board if token in rowId and colId is not Empty", () => {
    /* Given */
    let board = (
      (Mark(Cross), Empty, Empty),
      (Empty, Empty, Empty),
      (Empty, Empty, Empty),
    );
    /* When */
    let actual = updateBoard(board, R1, C1, Mark(Circle));
    /* Then */
    expect(actual) |> toBe(board);
  });
});

describe("isBoardFull", () => {
  test("should return true if board is full", () => {
    /* Given */
    let board = (
      (Mark(Cross), Mark(Circle), Mark(Cross)),
      (Mark(Circle), Mark(Cross), Mark(Cross)),
      (Mark(Cross), Mark(Circle), Mark(Circle)),
    );
    /* When */
    let actual = isBoardFull(board);
    /* Then */
    expect(actual) |> toBe(true);
  });
  test("should return false if board is not full", () => {
    /* Given */
    let board = (
      (Mark(Cross), Mark(Circle), Empty),
      (Mark(Circle), Mark(Cross), Mark(Cross)),
      (Mark(Cross), Mark(Circle), Mark(Circle)),
    );
    /* When */
    let actual = isBoardFull(board);
    /* Then */
    expect(actual) |> toBe(false);
  });
});

describe("isLineFullWith", () => {
  test("should return false if Empty on line", () => {
    /* Given */
    let line = (Empty, Empty, Empty);
    /* When */
    let actual = isLineFullWith(Mark(Cross), line);
    /* Then */
    expect(actual) |> toEqual(false);
  });
  test("should return false if Full without given token", () => {
    /* Given */
    let line = (Mark(Cross), Mark(Cross), Mark(Cross));
    /* When */
    let actual = isLineFullWith(Mark(Circle), line);
    /* Then */
    expect(actual) |> toEqual(false);
  });
  test("should return true if Full with given token", () => {
    /* Given */
    let line = (Mark(Cross), Mark(Cross), Mark(Cross));
    /* When */
    let actual = isLineFullWith(Mark(Cross), line);
    /* Then */
    expect(actual) |> toEqual(true);
  });
});

describe("getRowLine", () => {
  let board = (
    (Mark(Cross), Mark(Circle), Mark(Cross)),
    (Empty, Mark(Circle), Empty),
    (Empty, Mark(Circle), Mark(Cross)),
  );
  let (r1, r2, r3) = board;
  let testCases = [(R1, r1), (R2, r2), (R3, r3)];
  testAll("should return correct row", testCases, ((rId, expectedRow)) =>
    expect(getRowLine(board, rId)) |> toEqual(expectedRow)
  );
});

describe("getColumnLine", () => {
  let board = (
    (Mark(Cross), Mark(Circle), Mark(Cross)),
    (Empty, Mark(Circle), Empty),
    (Empty, Mark(Circle), Mark(Cross)),
  );
  let testCases = [
    (C1, (Mark(Cross), Empty, Empty)),
    (C2, (Mark(Circle), Mark(Circle), Mark(Circle))),
    (C3, (Mark(Cross), Empty, Mark(Cross))),
  ];
  testAll("should return correct col", testCases, ((cId, expectedColumn)) =>
    expect(getColumnLine(board, cId)) |> toEqual(expectedColumn)
  );
});