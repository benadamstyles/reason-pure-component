open Jest;
open Expect;

module TestComponent = {
  let component = ReasonReact.statelessComponent("Breadcrumb");

  let make = (~view, ~subview=?, ~renderCount, _children) => {
    ...component,
    render: _ => {
      incr(renderCount);
      <div>
        <p> view->ReasonReact.string </p>
        <p> {subview->Belt.Option.getWithDefault("")->ReasonReact.string} </p>
      </div>;
    },
  };
};

module TestComponentPure = {
  module Config = {
    type retainedProps = {
      view: string,
      subview: option(string),
    };
    let name = "Breadcrumb";
    let equals = (==);
  };

  module Pure = PureComponent.Stateless(Config);

  let make = (~view, ~subview=?, ~renderCount, _children) => {
    ...Pure.component,
    retainedProps: Config.{view, subview},
    render: _ => {
      incr(renderCount);
      <div>
        <p> view->ReasonReact.string </p>
        <p> {subview->Belt.Option.getWithDefault("")->ReasonReact.string} </p>
      </div>;
    },
  };
};

[@bs.send]
external update: (ReactTestRenderer.t, ReasonReact.reactElement) => unit = "";

describe("PureComponent", () => {
  open! Expect.Operators;

  let renderCount = ref(0);
  let renderer =
    ReactTestRenderer.create(
      <TestComponentPure view="Top" subview="Sub" renderCount />,
    );

  test("renders correctly", () =>
    renderer |> expect |> toMatchSnapshot
  );

  test("renderCount is incremented", () =>
    renderCount^ |> expect == 1
  );

  describe("updating", () => {
    describe("with PureComponent", () => {
      test("doesn't trigger a render if the props don't change", () => {
        renderer
        ->update(<TestComponentPure view="Top" subview="Sub" renderCount />)
        ->ignore;

        renderCount^ |> expect == 1;
      });

      test("does trigger a render if the props do change", () => {
        renderer
        ->update(
            <TestComponentPure view="Top changed" subview="Sub" renderCount />,
          )
        ->ignore;

        renderCount^ |> expect == 2;
      });
    });

    describe("without PureComponent", () => {
      let renderCount = ref(0);
      let renderer =
        ReactTestRenderer.create(
          <TestComponent view="Top" subview="Sub" renderCount />,
        );

      test("does trigger a render even if the props don't change", () => {
        renderer
        ->update(<TestComponent view="Top" subview="Sub" renderCount />)
        ->ignore;

        renderCount^ |> expect == 2;
      });

      test("does trigger a render if the props do change", () => {
        renderer
        ->update(
            <TestComponentPure view="Top changed" subview="Sub" renderCount />,
          )
        ->ignore;

        renderCount^ |> expect == 3;
      });
    });
  });
});
