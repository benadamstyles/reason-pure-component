# Usage

```reason
module Config = {
  type retainedProps = {
    view: string,
    subview: option(string),
  };
  let name = "Breadcrumb";
  let equals = (==);
};

module Pure = ReasonPureComponent.Stateless(Config);

let make = (~view, ~subview=?, _children) => {
  ...Pure.component,
  retainedProps: Config.{view, subview},
  render: _ =>
    <div>
      <p>{ReasonReact.string(view)}</p>
      <p>
        {ReasonReact.string(
          subview->Belt.Option.getWithDefault("")
        )}
      </p>
    </div>,
};
```
