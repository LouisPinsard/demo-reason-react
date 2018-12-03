[%bs.raw {|require('./pokedex.css')|}];
[%bs.raw {|require('bootstrap/dist/css/bootstrap.min.css')|}];

let component = ReasonReact.statelessComponent("Pokedex");

let make = (_children) => {
  ...component,
  render: _self =>
    <div className={Cn.make(["bootstrap", "pokedex-wrapper"])}>
      <label>(ReasonReact.string("Which pokemon do you want to choose ?"))
        <input className={Cn.make(["input"])} type_="number" />
      </label>
      <button className={Cn.make(["btn", "btn-default", "submit-button"])}>(ReasonReact.string("Find"))</button>
    </div>,
};
