[%bs.raw {|require('./pokedex.css')|}];
[%bs.raw {|require('bootstrap/dist/css/bootstrap.min.css')|}];

type status =
  | Loading
  | Waiting;

type nullableString =
  | None
  | Some(string);
type state = {
  status: status,
  input: nullableString,
};

type action =
  | Click
  | UpdateInput(string);

let fetchPokemon = (pokemon: nullableString) =>
  switch pokemon {
  | Some(name) => Js.Promise.(
      Fetch.fetch("http://pokeapi.salestock.net/api/v2/pokemon/"++name)
      |> then_(Fetch.Response.json)
      |> Js.log
    );
  | None => ()
  }

let getValue = (input) =>
  switch input {
  | Some(input) => input
  | None => ""
  };

let component = ReasonReact.reducerComponent("Pokedex");

let make = (_children) => {
  ...component,
  initialState: () => {input: None, status: Waiting},
  reducer: (action: action, state: state) =>
    switch action {
    | Click => ReasonReact.UpdateWithSideEffects({...state, status: Loading}, (self) =>
    Js.Promise.(fetchPokemon(self.state.input))
    )
    | UpdateInput(pokemonName) => ReasonReact.Update({...state, input: Some(pokemonName)})
    },
  render: self =>
    switch self.state.status {
    | Waiting =>
      <div className={Cn.make(["bootstrap", "pokedex-wrapper"])}>
        <label>(ReasonReact.string("Which pokemon do you want to choose ?"))
          <input
            className={Cn.make(["input"])}
            type_="string"
            value={getValue(self.state.input)}
            onChange={event => self.send(UpdateInput(ReactEvent.Form.target(event)##value))}
          />
        </label>
        <button
          className={Cn.make(["btn", "btn-default", "submit-button"])}
          onClick={_e => self.send(Click)}
        >
          (ReasonReact.string("Find"))
        </button>
      </div>
    | Loading =>
      (ReasonReact.string("Loading..."))
  },
};
