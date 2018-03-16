type action =
  | TODO;

type state = {ref: ref(option(Dom.element))};

let setRef = (theRef, {ReasonReact.state}) =>
  state.ref := Js.Nullable.toOption(theRef);

let component = ReasonReact.reducerComponent("Lottie");

let make = _children => {
  ...component,
  initialState: () => {ref: ref(None)},
  reducer: (action, _state) =>
    switch (action) {
    | TODO => ReasonReact.NoUpdate
    },
  render: self => <div ref=(self.handle(setRef)) />,
};