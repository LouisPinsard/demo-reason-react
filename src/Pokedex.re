[%bs.raw {|require('./pokedex.css')|}];
[%bs.raw {|require('bootstrap/dist/css/bootstrap.min.css')|}];

type state =
  | Loading
  | Waiting;

type action =
  | Click;

let component = ReasonReact.reducerComponent("Pokedex");

let make = (_children) => {
  ...component,
  initialState: () => Waiting,
  reducer: (action: action, _state: state) =>
    switch action {
    | Click => ReasonReact.Update(Loading)
    },
  render: self =>
    switch self.state {
    | Waiting =>
      <div className={Cn.make(["bootstrap", "pokedex-wrapper"])}>
        <label>(ReasonReact.string("Which pokemon do you want to choose ?"))
          <input className={Cn.make(["input"])} type_="number" />
        </label>
        <button
        className={Cn.make(["btn", "btn-default", "submit-button"])}
        onClick={(_e) => self.send(Click)}
        >
          (ReasonReact.string("Find"))
        </button>
      </div>
    | Loading =>
      (ReasonReact.string("Loading..."))
  },
};
