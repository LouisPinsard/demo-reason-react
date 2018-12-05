[%bs.raw {|require('./pokedex.css')|}];
[%bs.raw {|require('bootstrap/dist/css/bootstrap.min.css')|}];

type status =
  | Loading
  | Waiting;

type state = {
  status: status,
  input: string,
};

type action =
  | Click;

let fetchPokemon = (pokemon: string) =>
  Js.Promise.(
    Fetch.fetch("http://pokeapi.salestock.net/api/v2/pokemon/"++pokemon)
    |> then_(Fetch.Response.json)
    |> Js.log
  );

let component = ReasonReact.reducerComponent("Pokedex");

let make = (_children) => {
  ...component,
  initialState: () => {input: "", status: Waiting},
  reducer: (action: action, state: state) =>
    switch action {
    | Click => ReasonReact.UpdateWithSideEffects({...state, status: Loading}, (self) =>
     Js.Promise.(fetchPokemon(self.state.input))
     )
    },
  render: self =>
    switch self.state.status {
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
