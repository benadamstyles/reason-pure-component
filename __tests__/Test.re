open Jest;
open Expect;
open ReactTestingLibrary;

module TestComponent = {
  module Config = {
    type retainedProps = {
      view: string,
      subview: option(string),
    };
    let name = "Breadcrumb";
    let equals = (==);
  };

  module Pure = PureComponent.Stateless(Config);

  let make = (~view, ~subview=?, _children) => {
    ...Pure.component,
    retainedProps: Config.{view, subview},
    render: _ =>
      <div>
        <p> view->ReasonReact.string </p>
        <p> {subview->Belt.Option.getWithDefault("")->ReasonReact.string} </p>
      </div>,
  };
};

describe("PureComponent", () =>
  test("renders correctly", () =>
    <div> <TestComponent view="Top" subview="Sub" /> </div>
    |> render
    |> container
    |> expect
    |> toMatchSnapshot
  )
);
