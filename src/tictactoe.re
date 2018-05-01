[%bs.raw {|require('./tictactoe.css')|}];

let animationDataPlayer1 = [%bs.raw {|require('./x.json')|}];

let animationDataPlayer2 = [%bs.raw {|require('./o.json')|}];

open Player;

open Board;

type progress =
  | Turn(player)
  | Win(player)
  | Draw;

type state = {
  board,
  progress,
};

type action =
  | TokenAdded(rowId, colId);

let component = ReasonReact.reducerComponent("TicTacToe");

let isWinByToken = (board: board, rId: rowId, cId: colId, token: token) =>
  if (getRowLine(board, rId) |> isLineFullWith(token)) {
    true;
  } else if (getColumnLine(board, cId) |> isLineFullWith(token)) {
    true;
  } else {
    getDiagonalLines(board)
    |> List.map(isLineFullWith(token))
    |> List.fold_left((res, isFull) => res || isFull, false);
  };

let make = _children => {
  ...component,
  initialState: () => {
    board: (
      (Empty, Empty, Empty),
      (Empty, Empty, Empty),
      (Empty, Empty, Empty),
    ),
    progress: Turn(X),
  },
  reducer: (action, state) =>
    switch (action, state.progress) {
    | (TokenAdded(rId, cId), Turn(p)) =>
      let currentToken = getTokenForPlayer(p);
      let updateBoard = updateBoard(state.board, rId, cId, currentToken);
      if (isWinByToken(updateBoard, rId, cId, currentToken)) {
        ReasonReact.Update({progress: Win(p), board: updateBoard});
      } else if (! isBoardFull(updateBoard)) {
        ReasonReact.Update({
          progress:
            updateBoard === state.board ? Turn(p) : Turn(p === X ? O : X),
          board: updateBoard,
        });
      } else {
        ReasonReact.Update({progress: Draw, board: updateBoard});
      };
    | _ => ReasonReact.NoUpdate
    },
  render: ({state, send}) => {
    let title =
      switch (state.progress) {
      | Turn(p) => "Player " ++ p_to_str(p) ++ " turn"
      | Win(p) => "Player " ++ p_to_str(p) ++ " won"
      | Draw => "It's a draw"
      };
    <div className="tic-tac-toe">
      <div className="title">
        <div className="title__main">
          (ReasonReact.stringToElement("TIC TAC TOE"))
        </div>
        <div className="title__sub">
          (ReasonReact.stringToElement(title))
        </div>
      </div>
      <div className="board">
        (
          [R1, R2, R3]
          |> List.map(rId => [C1, C2, C3] |> List.map(cId => (rId, cId)))
          |> List.flatten
          |> List.map(((rId, cId)) =>
               <div
                 className="board__cell"
                 key=(row_to_str(rId) ++ col_to_str(cId))
                 onClick=(_event => send(TokenAdded(rId, cId)))>
                 (
                   switch (getToken(state.board, rId, cId)) {
                   | Board.X =>
                     <Lottie
                       options={
                         animationData: animationDataPlayer1,
                         loop: true,
                         autoplay: true,
                       }
                     />
                   | Board.O =>
                     <Lottie
                       options={
                         animationData: animationDataPlayer2,
                         loop: false,
                         autoplay: true,
                       }
                     />
                   | Empty =>
                     ReasonReact.stringToElement(token_to_str(Empty))
                   }
                 )
               </div>
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
    </div>;
  },
};