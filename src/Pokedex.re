[%bs.raw {|require('./pokedex.css')|}];
[%bs.raw {|require('bootstrap/dist/css/bootstrap.min.css')|}];

open SharedTypes;

type status =
  | Loading
  | Waiting
  | PokemonDisplayed(pokemon)
  | ErrorField;

type state = {
  status: status,
  input: string,
};


type action =
  | Click
  | UpdateInput(string)
  | LoadPokemonSuccess(pokemon)
  | Error;

module Decode = {
  let pokemon = pokemon =>
    Json.Decode.{
      name: field("name",string, pokemon),
      id: field("id", int, pokemon),
      spriteUrl: at(["sprites", "front_default"], string, pokemon),
    };
};

let fetchPokemon = (pokemon: string) =>
 Js.Promise.(
      Fetch.fetch("http://pokeapi.salestock.net/api/v2/pokemon/"++pokemon)
      |> then_(Fetch.Response.json)
      |> then_(json =>
      json |> Decode.pokemon |> resolve)
    );

let component = ReasonReact.reducerComponent("Pokedex");

let make = (_children) => {
  {
    ...component,
    initialState: () => {input: "", status: Waiting},
    reducer: (action: action, state: state) =>
      switch action {
      | Click => ReasonReact.UpdateWithSideEffects({...state, status: Loading}, (self) => Js.Promise.(
        fetchPokemon(self.state.input)
        |> then_((pokemon) => resolve(self.send(LoadPokemonSuccess(pokemon))))
        |> ignore))
      | LoadPokemonSuccess(pokemon) => ReasonReact.Update({...state, status: PokemonDisplayed(pokemon)})
      | UpdateInput(pokemonName) => ReasonReact.Update({...state, input: pokemonName})
      | Error => ReasonReact.Update({...state, status: ErrorField})
      },
    render: self =>
    <div>
      <div className={Cn.make(["bootstrap", "pokedex-wrapper"])}>
        <label>(ReasonReact.string("Which pokemon do you want to choose ?"))
          <input
            className={Cn.make(["input"])}
            type_="string"
            value={self.state.input}
            onChange={event => self.send(UpdateInput(ReactEvent.Form.target(event)##value))}
          />
        </label>
        <button
          className={Cn.make(["btn", "btn-default", "submit-button"])}
          onClick={_event => switch(self.state.input){
            | "" => self.send(Error);
            | _ => self.send(Click)
            }
          }
        >
          (ReasonReact.string("Find"))
        </button>
      </div>
     ( switch self.state.status {
      | Loading => (ReasonReact.string("Loading..."))
      | ErrorField => (ReasonReact.string("ERROR: You should enter a pokemon name !!!"))
      | Waiting => (ReasonReact.null)
      | PokemonDisplayed(pokemon) => <Pokemon pokemon />
    })
    </div>,
}
};
