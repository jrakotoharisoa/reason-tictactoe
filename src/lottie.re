type lottieAnimation = {. setSpeed: int => unit};

type action =
  | Pause;

type optionProps = {
  loop: bool,
  autoplay: bool,
  animationData: string,
};

type animationOptions = {
  .
  "container": Dom.element,
  "renderer": string,
  "loop": bool,
  "autoplay": bool,
  "animationData": string,
};

[@bs.val] [@bs.module "lottie-web"]
external loadAnimation : animationOptions => lottieAnimation = "";

let defaultSize = "100%";

type state = {
  ref: ref(option(Dom.element)),
  animation: ref(option(lottieAnimation)),
};

let setRef = (theRef, {ReasonReact.state}) =>
  state.ref := Js.Nullable.toOption(theRef);

let component = ReasonReact.reducerComponent("Lottie");

let make =
    /* ~eventListeners=[], */
    (
      ~options: optionProps,
      ~width=defaultSize,
      ~height=defaultSize,
      /* ~isStopped=false, */
      /* ~isPaused=false, */
      /* ~speed=1, */
      /* ~direction=1, */
      ~ariaRole="button",
      ~isClickToPauseDisabled=false,
      ~title="",
      _children,
    ) => {
  let clickPause = (_event, {ReasonReact.send}) =>
    isClickToPauseDisabled ? () : send(Pause);
  {
    ...component,
    initialState: () => {ref: ref(None), animation: ref(None)},
    didMount: ({state}) => {
      switch (state.ref^) {
      | Some(ref) =>
        Js.log(ref);
        let animationOptions = {
          "container": ref,
          "renderer": "svg",
          "loop": options.loop !== false,
          "autoplay": options.autoplay !== false,
          "animationData": options.animationData,
        };
        let animation = loadAnimation(animationOptions);
        state.animation := Some(animation);
      | None => ()
      };
      ReasonReact.NoUpdate;
    },
    reducer: (action, _state) =>
      switch (action) {
      | Pause => ReasonReact.NoUpdate
      },
    render: self => {
      let lottieStyles =
        ReactDOMRe.Style.make(
          ~overflow="hidden",
          ~marginTop="0",
          ~marginRight="auto",
          ~marginBottom="0",
          ~marginLeft="auto",
          ~height,
          ~width,
          (),
        );
      <div
        ref=(self.handle(setRef))
        style=lottieStyles
        title
        role=ariaRole
        onClick=(self.handle(clickPause))
      />;
    },
  };
};