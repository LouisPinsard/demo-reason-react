[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: _self =>
    <div className={Cn.make(["App"])}>
      <h1 className={Cn.make(["App-title"])}>(ReasonReact.string("Pokedex"))</h1>
      <Pokedex/>
    </div>,
};
