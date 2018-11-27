let component = ReasonReact.statelessComponent("Pokedex");

let make = (_children) => {
  ...component,
  render: _self =>
    <div>
      <label>(ReasonReact.string("Which pokemon do you want to choose ?"))
        <input type_="number" />
      </label>
    </div>,
};
